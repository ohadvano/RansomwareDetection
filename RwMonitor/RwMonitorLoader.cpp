#include "RwMonitor.cpp"

using namespace Heuristics;

namespace RwMonitor
{
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
