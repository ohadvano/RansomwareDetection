#include "FsAction.cpp"
#include "HeuristicBase.cpp"
#include "ShannonEnthropyHeuristic.cpp"
#include "SimilarityMeasurementHeuristic.cpp"
#include "SuspiciousKeywordsHeuristicThreshold.cpp"
#include "FileTypeChangesHeuristic.cpp"
#include "FilesDeletionHeuristic.cpp"
#include "Logger.cpp"
#include "TempWriter.cpp"
#include "ConfigurationProvider.cpp"
#include <vector>

using namespace Log;
using namespace TempFile;
using namespace Heuristics;
using namespace FileSystemActions;
using namespace Configurations;

namespace RwMonitor
{
    enum RiskStatus
    {
        Risky,
        Safe
    };

    class RwThreatDetector
    {
        public:
            RwThreatDetector()
            {
                char const* configFileName = "parameters.config";
                _configurationProvider = new ConfigurationProvider(configFileName);

                char* logFilePath = _configurationProvider->GetLogFilePath();
                _logger = new Logger(logFilePath);

                _isDebug = _configurationProvider->IsDebugMode();
                string debugString = _isDebug ? "Yes" : "No";
                _logger->WriteLog("[Debug: " + debugString + "]");

                char* tempFilePath = _configurationProvider->GetTempFilePath();
                _tempWriter = new TempWriter(tempFilePath);

                char* tempFilePath2 = _configurationProvider->GetTempFilePath2();
                _tempWriter2 = new TempWriter(tempFilePath2);

                _minAccumulatedThreshold = _configurationProvider->GetMinAccumulatedThreshold();
                _heuristicsWeights = _configurationProvider->GetHeuristicsWeights();
                _individualThresholds = _configurationProvider->GetIndividualThresholds();

                _heuristics = new list<HeuristicBase*>();

                _isInternal = false;

                if (pthread_mutex_init(&_actionLock, nullptr) != 0)
                {
                    fprintf(stderr, "error: _actionLock mutex init has failed");
                    exit(1);
                }

                _logger->WriteLog("[Ransomware monitor started]");
            }

            RiskStatus CanPerform(FsAction* action)
            {
                _logger->WriteLog("####################################################");

                if (_isInternal)
                {
                    return Safe;
                }

                // TODO: Consider remove the lock
                pthread_mutex_lock(&_actionLock);
                _isInternal = true;

                string actionName = action->ActionName;
                _logger->WriteLog("[New action detected in monitor: " + actionName + "]");

                // Calculate the new threshold after the action came to the system
                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    (*it)->CalculateTH(action);
                }
               
                // Decide if the system is in risk state
                bool isRisky = IsSystemAtRiskWithNewThresholds();

                _isInternal = false;
                pthread_mutex_unlock(&_actionLock);

                _logger->WriteLog("####################################################");

                if (_isDebug)
                {
                    return Safe;
                }

                if (isRisky)
                {
                    return Risky;
                }

                return Safe;
            }

            void AddHeuristic(HeuristicBase* heuristic)
            {
                if (heuristic == nullptr)
                {
                    throw new exception;
                }

                _heuristics->push_back(heuristic);
            }

            TempWriter* GetTempWriter()
            {
                return _tempWriter;
            }

            TempWriter* GetTempWriter2()
            {
                return _tempWriter2;
            }

            Logger* GetLogger()
            {
                return _logger;
            }

            ~RwThreatDetector()
            {
                _logger->WriteLog("Ransomware monitor exiting");

                pthread_mutex_unlock(&_actionLock);
                pthread_mutex_destroy(&_actionLock);

                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    delete *it;
                }

                delete _heuristics;
                delete _tempWriter;
                delete _tempWriter2;
                delete _logger;
            }

            Configurations::ConfigurationProvider* _configurationProvider;

        private:
            pthread_mutex_t _actionLock;
            bool _isInternal;
            bool _isDebug;

            Log::Logger* _logger;
            TempFile::TempWriter* _tempWriter;
            TempFile::TempWriter* _tempWriter2;
            std::list<HeuristicBase*>* _heuristics;

            double _minAccumulatedThreshold;
            double* _heuristicsWeights;
            double* _individualThresholds;

            bool IsSystemAtRiskWithNewThresholds()
            {
                double thresholds[6];
                
                int idx = 0;
                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    thresholds[idx] = (*it)->heuristicTH;
                    idx++;
                }

                bool accumulated = AccumulatedThreshold(thresholds, idx, _minAccumulatedThreshold, _heuristicsWeights);
                bool individual = IndividualThresholds(thresholds, _individualThresholds, idx);
                bool isThreat = accumulated || individual;

                string resultAsString = isThreat ? "Risk" : "Safe";
                _logger->WriteLog("[Action resolution: " + resultAsString + "]");

                return isThreat;
            }

            bool AccumulatedThreshold(double thresholds[], int length, double minThreshold, double* heuristicsWeights)
            {
                string conditionDescription = "AccumulatedThreshold";

                double sum = 0;
                for (int idx = 0; idx < length; idx++)
                {
                    sum += heuristicsWeights[idx] * thresholds[idx];
                }

                bool result = sum > minThreshold;

                _logger->WriteLog("[Accumulated thresholds: " + Convert(sum) + "]");
                string resultAsString = result ? "Risk" : "Safe";
                _logger->WriteLog("[Checking action with: " + conditionDescription + "][Condition result: " + resultAsString + "]");

                return result;
            }

            bool IndividualThresholds(double thresholds[], double* individualMinThresholds, int length)
            {
                string conditionDescription = "IndividualThresholds";

                bool result = false;
                for (int idx = 0; idx < length; idx++)
                {
                    if (thresholds[idx] > individualMinThresholds[idx])
                    {
                        result = true;
                        break;
                    }
                }

                string resultAsString = result ? "Risk" : "Safe";
                _logger->WriteLog("[Checking action with: " + conditionDescription + "][Condition result: " + resultAsString + "]");
                
                return result;
            }

            string Convert(double d)
            {
                std::ostringstream strs;
                strs << d;
                std::string str = strs.str();
                return str;
            }
    };
    
    class RwMonitorLoader
    {
        public:
            RwMonitorLoader(RwThreatDetector* monitorToLoad)
            {
                Configurations::ConfigurationProvider* cp = monitorToLoad->_configurationProvider;

                Log::Logger* logger = monitorToLoad->GetLogger();
                TempFile::TempWriter* tempWriter = monitorToLoad->GetTempWriter();
                TempFile::TempWriter* tempWriter2 = monitorToLoad->GetTempWriter2();

                int similarityMeasurementHeuristicThreshold = cp->GetSimilarityThreshold();
                int shannonEnthropyHeuristicThreshold = cp->GetEnthropyThreshold();
                double suspectedEncryptionEnthropyThreshold = cp->GetSuspectedEncryptionEnthropyThreshold();
                vector<string> suspiciousKeywords = cp->GetSuspiciousKeywords();
                int lookbackTime = cp->GetLookbackTime();

                monitorToLoad->AddHeuristic(new FileTypeChangesHeuristic(logger, tempWriter, lookbackTime));
                monitorToLoad->AddHeuristic(new SimilarityMeasurementHeuristic(logger, tempWriter, tempWriter2, similarityMeasurementHeuristicThreshold, lookbackTime));
                monitorToLoad->AddHeuristic(new ShannonEnthropyHeuristic(logger, tempWriter, shannonEnthropyHeuristicThreshold, suspectedEncryptionEnthropyThreshold, lookbackTime));
                monitorToLoad->AddHeuristic(new FilesDeletionHeuristic(logger, tempWriter, lookbackTime));
                monitorToLoad->AddHeuristic(new SuspiciousKeywordsHeuristicThreshold(logger, tempWriter, suspiciousKeywords, lookbackTime));
            }
    };
}
