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
                    string oldContent = GetOldContent(writeAction);
                    double enthropyBefore = CalculateEntropy(oldContent);
                    size_t sizeBefore = oldContent.size();
                    string s1 = std::to_string(sizeBefore);
                    _logger->WriteLog("[" + _heuristicName + "][Enthropy before: " + GetDoubleAsString(enthropyBefore) + "]");

                    // After
                    string newContent = GetNewContent(filePath, writeAction);
                    double enthropyAfter = CalculateEntropy(newContent);
                    size_t sizeAfter = newContent.size();
                    string s2 = std::to_string(sizeAfter);
                    _logger->WriteLog("[" + _heuristicName + "][Enthropy after: " + GetDoubleAsString(enthropyAfter) + "]");

                    if ((enthropyBefore > 0 && Abs(enthropyBefore - enthropyAfter) > _threshold) ||
                        (enthropyAfter > 7.5))
                    {
                        _logger->WriteLog("[" + _heuristicName + "][High enthropy change detected]");
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

            double CalculateEntropy(string input)
			{
                int length = input.size();
				std::map<char, int> frequencies;

				for (int i = 0; i < length; ++i)
                {
                    char inputAt = input.at(i);
					frequencies[inputAt] ++;
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