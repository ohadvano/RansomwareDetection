#include <list>
#include "FsAction.cpp"

using namespace FileSystemActions;
using namespace std;

namespace Heuristics
{
    template <class T>
    class ActionsHistory : std::list<T> { };

    class HeuristicBase
    {
        public:
            virtual bool IsValidAction(FsAction action) = 0;
    };

    class FileTypeChangesHeuristic : public HeuristicBase
    {
        public:
            FileTypeChangesHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~FileTypeChangesHeuristic()
            {

            }

        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };

    class SimilarityMeasurementHeuristic : public HeuristicBase
    {
        public:
            SimilarityMeasurementHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~SimilarityMeasurementHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };

    class ShannonAnthropyHeuristic : public HeuristicBase
    {
        public:
            ShannonAnthropyHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~ShannonAnthropyHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };

    class SecondaryIndicatorsHeuristic : public HeuristicBase
    {
        public:
            SecondaryIndicatorsHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~SecondaryIndicatorsHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };

    class UnionIndicationHeuristic : public HeuristicBase
    {
        public:
            UnionIndicationHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~UnionIndicationHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };

    class IndicatorEvationHeuristic : public HeuristicBase
    {
        public:
            IndicatorEvationHeuristic()
            {

            }

            bool IsValidAction(FsAction action) override
            {
                return true;
            }

            ~IndicatorEvationHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };
}
