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

                _heuristics = new list<HeuristicBase*>();

                _isInternal = false;

                if (pthread_mutex_init(&_actionLock, nullptr) != 0)
                {
                    fprintf(stderr, "error: _actionLock mutex init has failed");
                    exit(1);
                }
            }

            RiskStatus CanPerform(FsAction action)
            {
                if (_isInternal)
                {
                    return Safe;
                }

                // TODO: Consider remove the lock
                pthread_mutex_lock(&_actionLock);
                _isInternal = true;

                // Calculate the new threshold after the action came to the system
                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    (*it)->CalculateTH(action);
                }

                // Now new thresholds are updated
                
                // Decide if the system is in risk state
                bool isRisky = IsSystemAtRiskWithNewThresholds();

                _isInternal = false;
                pthread_mutex_unlock(&_actionLock);

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

            Logger* GetLogger()
            {
                return _logger;
            }

            ~RwThreatDetector()
            {
                pthread_mutex_unlock(&_actionLock);
                pthread_mutex_destroy(&_actionLock);

                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    delete *it;
                }

                delete _heuristics;
                delete _tempWriter;
                delete _logger;
            }

            Configurations::ConfigurationProvider* _configurationProvider;

        private:
            pthread_mutex_t _actionLock;
            bool _isInternal;

            Log::Logger* _logger;
            TempFile::TempWriter* _tempWriter;
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

                return CheckCondition1(thresholds) ||
                       CheckCondition2(thresholds) ||
                       CheckCondition3(thresholds);
            }

            bool CheckCondition1(double thresholds[])
            {
                return false;
            }

            bool CheckCondition2(double thresholds[])
            {
                return false;
            }

            bool CheckCondition3(double thresholds[])
            {
                return false;
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

                int similarityMeasurementHeuristicThreshold = cp->GetSimilarityThreshold();
                int shannonEnthropyHeuristicThreshold = cp->GetEnthropyThreshold();
                vector<string> suspiciousKeywords = cp->GetSuspiciousKeywords();

                monitorToLoad->AddHeuristic(new FileTypeChangesHeuristic(logger, tempWriter));
                monitorToLoad->AddHeuristic(new SimilarityMeasurementHeuristic(logger, tempWriter, similarityMeasurementHeuristicThreshold));
                monitorToLoad->AddHeuristic(new ShannonEnthropyHeuristic(logger, tempWriter, shannonEnthropyHeuristicThreshold));
                monitorToLoad->AddHeuristic(new FilesDeletionHeuristic(logger, tempWriter));
                monitorToLoad->AddHeuristic(new SuspiciousKeywordsHeuristicThreshold(logger, tempWriter, suspiciousKeywords));
            }
    };
}
