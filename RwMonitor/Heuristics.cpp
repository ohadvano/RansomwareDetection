#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include "FsAction.cpp"
#include "Logger.cpp"
#include "TempWriter.cpp"
#include "History.cpp"

using namespace FileSystemActions;
using namespace Log;
using namespace TempFile;
using namespace std;
using namespace ActionsHistory;

typedef unsigned char uint8;

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

            string GetFilePathFromWriteAction(WriteBufAction* writeAction)
            {
                return "x";
            }

            string GetNewContent(string filePath, WriteBufAction* writeAction)
            {
                return "x";
            }

            uint8* ReadFile(string filePath)
            {
                return 0;
            }

            int GetLength(uint8* byteStream)
            {
                return 0;
            }

            double Abs(double input)
            {
                if (input < 0)
                {
                    return input * -1;
                }

                return input;
            }

            int Abs(int input)
            {

            }

            string RunFileUtility(string filePath)
            {

            }
            
            int RunSdHash(string fileBeforePath, string fileAfterPath)
            {

            }
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

                    // Example log
                    // _logger->WriteLog("Running file utility on: [" + filePath + "]");

                    string beforeType = RunFileUtility(filePath);
                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    string afterType = RunFileUtility(_tempFilePath);

                    if (beforeType != afterType)
                    {
                        _writeBufHistory->AddNewAction(writeAction);
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

            void RefreshTH()
            {

            }
    };

    class SimilarityMeasurementHeuristic : public HeuristicBase
    {
        public:
            SimilarityMeasurementHeuristic(Logger* logger, TempWriter* tempWriter, int threshold)
            {
                _tempWriter = tempWriter;
                _logger = logger;
                _threshold = threshold;

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "WriteBufAction")
                {
                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(&action);
                    string filePath = GetFilePathFromWriteAction(writeAction);
                    _tempWriter->Write(GetNewContent(filePath, writeAction));

                    int similarityMeasurementScore = RunSdHash(filePath, _tempWriter->TempFilePath);
                    if (similarityMeasurementScore < _threshold)
                    {
                        _writeBufHistory->AddNewAction(writeAction);
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
            int _threshold;

            void RefreshTH()
            {

            }
    };

    class ShannonAnthropyHeuristic : public HeuristicBase
    {
        public:
            ShannonAnthropyHeuristic(Logger* logger, TempWriter* tempWriter, int threshold)
            {
                _tempWriter = tempWriter;
                _logger = logger;
                _threshold = threshold;

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "WriteBufAction")
                {
                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(&action);
                    string filePath = GetFilePathFromWriteAction(writeAction);

                    // Before
                    uint8* inputBefore = ReadFile(filePath);
                    int lengthBefore = GetLength(byteStream);
                    double enthropyBefore = CalculateEntropy(inputBefore, lengthBefore);

                    // After
                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    uint8* inputAfter = ReadFile(_tempWriter->TempFilePath);
                    int lengthAfter = GetLength(byteStream);
                    double enthropyAfter = CalculateEntropy(inputBefore, lengthBefore);

                    if (Abs(enthropyBefore - enthropyAfter) < _threshold)
                    {
                        _writeBufHistory->AddNewAction(writeAction);
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
            double _threshold;

            void RefreshTH()
            {

            }

            double CalculateEntropy(uint8* input, int length)
			{
				std::map<char, int> frequencies;

				for (int i = 0; i < length; ++i)
                {
					frequencies[input[i]] ++;
                }

				double infocontent = 0;

				for (std::pair<char, int> p : frequencies)
				{
					double freq = static_cast<double>(p.second) / length;
					infocontent += freq * log2(freq);
				}

				infocontent *= -1;

				return infocontent;
			}
    };
}
