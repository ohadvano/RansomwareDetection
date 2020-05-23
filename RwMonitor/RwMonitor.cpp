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

                for (std::list<HeuristicBase*>::iterator it = _heuristics->begin(); it != _heuristics->end(); ++it)
                {
                    if ((*it)->IsValidAction(action) == false)
                    {
                        pthread_mutex_unlock(&_actionLock);
                        return Risky;
                    }
                }

                pthread_mutex_unlock(&_actionLock);

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
    };
}
