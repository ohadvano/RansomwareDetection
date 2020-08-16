#include <list>
#include "FsAction.cpp"

using namespace FileSystemActions;
using namespace std;

namespace Heuristics
{
    class ActionRecord
    {
        public:
            ActionRecord(FsAction action)
            {
                _action = action;
                _actionTime = time(0);
            }

        private:
            FsAction _action;
            time_t _actionTime;
    }

    class ActionsHistory
    {
        public:
            ActionsHistory()
            {
                _actionRecords = new list<ActionRecord>();
            }

            void AddNewAction(FsAction newAction)
            {
                _actionRecords->push_front(ActionRecord(newAction));
            }

            ~ActionsHistory()
            {
                delete _actionRecords;
            }
            
        private:
            std::list<ActionRecord>* _actionRecords;
    }

    class HeuristicBase
    {
        public:
            virtual void CalculateTH(FsAction action) = 0;

            virtual ~HeuristicBase()
            {
            }

            double heuristicTH = 0;
    };

    class FileTypeChangesHeuristic : public HeuristicBase
    {
        public:
            FileTypeChangesHeuristic()
            {
                _renameHistory = new ActionsHistory();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "RenameAction")
                {
                    _renameHistory->AddNewAction(action);
                }
            }

            ~FileTypeChangesHeuristic()
            {
                delete _renameHistory;
            }

        private:
            ActionsHistory* _renameHistory;

            bool ScanHistory()
            {
                time_t currentTime = time(0);

                // TODO Check for false cases
                return true;
            }
    };

    class SimilarityMeasurementHeuristic : public HeuristicBase
    {
        public:
            SimilarityMeasurementHeuristic()
            {

            }

            void CalculateTH(FsAction action) override
            {
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

            void CalculateTH(FsAction action) override
            {
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

            void CalculateTH(FsAction action) override
            {
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

            void CalculateTH(FsAction action) override
            {
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

            void CalculateTH(FsAction action) override
            {
            }

            ~IndicatorEvationHeuristic()
            {

            }
        
        private:
            // Add histories
            // ActionsHistory<MakeDirAction> _makeDirHistory;
    };
}
