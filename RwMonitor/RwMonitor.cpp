#include "FsAction.cpp"
#include "Heuristics.cpp"

using namespace Heuristics;
using namespace FileSystemActions;

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
                _heuristics = new list<HeuristicBase*>();
                if (pthread_mutex_init(&_actionLock, nullptr) != 0)
                {
                    fprintf(stderr, "error: _actionLock mutex init has failed");
                    exit(1);
                }
            }

            RiskStatus CanPerform(FsAction action)
            {
                pthread_mutex_lock(&_actionLock);

                // Calculate the new threshold after the action came to the system
                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    (*it)->CalculateTH(action);
                }

                // Now new thresholds are updated
                
                // Decide if the system is in risk state
                bool isRisky = IsSystemAtRiskWithNewThresholds();

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

            ~RwThreatDetector()
            {
                pthread_mutex_unlock(&_actionLock);
                pthread_mutex_destroy(&_actionLock);

                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    delete *it;
                }

                delete _heuristics;
            }

        private:
            pthread_mutex_t _actionLock;
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
                monitorToLoad->AddHeuristic(new FileTypeChangesHeuristic());
                monitorToLoad->AddHeuristic(new SimilarityMeasurementHeuristic());
                monitorToLoad->AddHeuristic(new ShannonAnthropyHeuristic());
                monitorToLoad->AddHeuristic(new SecondaryIndicatorsHeuristic());
                monitorToLoad->AddHeuristic(new UnionIndicationHeuristic());
                monitorToLoad->AddHeuristic(new IndicatorEvationHeuristic());
            }
    };
}
