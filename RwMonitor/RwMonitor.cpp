#include "FsAction.cpp"
#include "Heuristics.cpp"
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

                char* tempFilePath = _configurationProvider->GetTempFilePath();
                _tempWriter = new TempWriter(tempFilePath);

                char* tempFilePath2 = _configurationProvider->GetTempFilePath2();
                _tempWriter2 = new TempWriter(tempFilePath2);

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

            Log::Logger* _logger;
            TempFile::TempWriter* _tempWriter;
            TempFile::TempWriter* _tempWriter2;
            std::list<HeuristicBase*>* _heuristics;

            bool IsSystemAtRiskWithNewThresholds()
            {
                double thresholds[6];
                
                int idx = 0;
                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    thresholds[idx] = (*it)->heuristicTH;
                    idx++;
                }

                bool isThreat = CheckCondition1(thresholds) ||
                                CheckCondition2(thresholds) ||
                                CheckCondition3(thresholds);

                string resultAsString = isThreat ? "Risk" : "Safe";
                _logger->WriteLog("Action resolution: " + resultAsString);

                return isThreat;
            }

            bool CheckCondition1(double thresholds[])
            {
                string conditionDescription = "Condition1";
                _logger->WriteLog("Checking action with: " + conditionDescription);

                bool result = false;

                string resultAsString = result ? "Risk" : "Safe";
                _logger->WriteLog("Condition result: " + resultAsString);

                return result;
            }

            bool CheckCondition2(double thresholds[])
            {
                string conditionDescription = "Condition2";
                _logger->WriteLog("Checking action with: " + conditionDescription);

                bool result = false;

                string resultAsString = result ? "Risk" : "Safe";
                _logger->WriteLog("Condition result: " + resultAsString);
                
                return result;
            }

            bool CheckCondition3(double thresholds[])
            {
                string conditionDescription = "Condition3";
                _logger->WriteLog("Checking action with: " + conditionDescription);

                bool result = false;

                string resultAsString = result ? "Risk" : "Safe";
                _logger->WriteLog("Condition result: " + resultAsString);
                
                return result;
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
                vector<string> suspiciousKeywords = cp->GetSuspiciousKeywords();

                monitorToLoad->AddHeuristic(new FileTypeChangesHeuristic(logger, tempWriter));
                monitorToLoad->AddHeuristic(new SimilarityMeasurementHeuristic(logger, tempWriter, tempWriter2, similarityMeasurementHeuristicThreshold));
                monitorToLoad->AddHeuristic(new ShannonEnthropyHeuristic(logger, tempWriter, shannonEnthropyHeuristicThreshold));
                monitorToLoad->AddHeuristic(new FilesDeletionHeuristic(logger, tempWriter));
                monitorToLoad->AddHeuristic(new SuspiciousKeywordsHeuristicThreshold(logger, tempWriter, suspiciousKeywords));
            }
    };
}
