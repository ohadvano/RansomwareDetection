#ifndef _HHEURISTIC_SE
#define _HHEURISTIC_SE

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "FsAction.cpp"
#include "Logger.cpp"
#include "TempWriter.cpp"
#include "History.cpp"
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sstream>
#include "HeuristicBase.cpp"

using namespace FileSystemActions;
using namespace Log;
using namespace TempFile;
using namespace std;
using namespace ActionsHistory;

typedef unsigned char uint8;

namespace Heuristics
{
    class ShannonEnthropyHeuristic : public HeuristicBase
    {
        public:
            ShannonEnthropyHeuristic(Logger* logger, TempWriter* tempWriter, int threshold, int lookbackTime)
                : HeuristicBase { lookbackTime }
            {
                _tempWriter = tempWriter;
                _logger = logger;
                _threshold = threshold;

                _logger->WriteLog("[" + _heuristicName + "][Init]");

                _writeBufHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction* action) override
            {
                if (action->ActionName == "WriteBufAction")
                {
                    _logger->WriteLog("[" + _heuristicName + "][Write action detected]");

                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(action);

                    string filePath = writeAction->FilePath;
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + filePath + "]");

                    // Before
                    _tempWriter->Write(GetOldContent(writeAction));
                    uint8* inputBefore = ReadFile(_tempWriter->TempFilePath);
                    int lengthBefore = GetLength(inputBefore);
                    double enthropyBefore = CalculateEntropy(inputBefore, lengthBefore);
					delete[] inputBefore;
                    _logger->WriteLog("[" + _heuristicName + "][Enthropy before: " + GetDoubleAsString(enthropyBefore) + "]");

                    // After
                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    uint8* inputAfter = ReadFile(_tempWriter->TempFilePath);
                    int lengthAfter = GetLength(inputAfter);
                    double enthropyAfter = CalculateEntropy(inputAfter, lengthAfter);
					delete[] inputAfter;
                    _logger->WriteLog("[" + _heuristicName + "][Enthropy after: " + GetDoubleAsString(enthropyAfter) + "]");

                    if (Abs(enthropyBefore - enthropyAfter) < _threshold)
                    {
                        _logger->WriteLog("[" + _heuristicName + "][High enthropy detected]");
                        _writeBufHistory->AddNewAction(writeAction);
                    }
                }

                RefreshTH();
                _logger->WriteLog("[" + _heuristicName + "][New threshold: " + GetThAsString() + "]");
            }

            ~ShannonEnthropyHeuristic()
            {
                _logger->WriteLog("[" + _heuristicName + "][Exit]");
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;
            double _threshold;
            string _heuristicName = "Shannon Enthropy";

            void RefreshTH()
            {
                int results = _writeBufHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Results found in history search: " + GetIntAsString(results) + "]");

                heuristicTH = results;
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

#endif