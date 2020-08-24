#include <list>
#include "FsAction.cpp"
#include "Logger.cpp"
#include "TempWriter.cpp"

using namespace FileSystemActions;
using namespace Log;
using namespace TempFile;
using namespace std;

namespace Heuristics
{
    class HeuristicBase
    {
        public:
            virtual void CalculateTH(FsAction action) = 0;

            virtual ~HeuristicBase()
            {
            }

            double heuristicTH = 0;

            TempWriter* _tempWriter;
            Logger* _logger;
    };

    class FileTypeChangesHeuristic : public HeuristicBase
    {
        public:
            FileTypeChangesHeuristic(Logger* logger, TempWriter* tempWriter)
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "WriteBufAction")
                {
                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(&action);
                    string filePath = GetFilePathFromWriteAction(writeAction);

                    if (!filePath == _tempWriter->TempFilePath && 
                        !filePath == _logger->LogPath)
                    {
                        _logger->WriteLog("Running file utility on: [" + filePath + "]");
                        string beforeType = RunFileUtility(filePath);
                        _tempWriter->Write();
                        string afterType = RunFileUtility(_tempFilePath);

                        if (beforeType != afterType)
                        {
                            _logger->WriteLog("File type change detected, before type: [" + beforeType + "], after type: [" + afterType + "]");
                            // TODO: Use generics in history to save the real action
                            _writeBufHistory->AddNewAction(writeAction);
                        }
                    }
                }

                RefreshTH();
            }

            ~FileTypeChangesHeuristic()
            {
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;

            string GetFilePathFromWriteAction(WriteBufAction* writeAction)
            {

            }

            string RunFileUtility(string filePath)
            {

            }

            void RefreshTH()
            {

            }
    };

    class SimilarityMeasurementHeuristic : public HeuristicBase
    {
        public:
            SimilarityMeasurementHeuristic(Logger* logger, TempWriter* tempWriter)
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                RefreshTH();
            }

            ~FileTypeChangesHeuristic()
            {
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;

            void RefreshTH()
            {

            }
    };

    class ShannonAnthropyHeuristic : public HeuristicBase
    {
        public:
            ShannonAnthropyHeuristic(Logger* logger, TempWriter* tempWriter)
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                RefreshTH();
            }

            ~FileTypeChangesHeuristic()
            {
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;

            void RefreshTH()
            {

            }
    };
}
