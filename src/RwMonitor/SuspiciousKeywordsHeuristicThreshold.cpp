#ifndef _HHEURISTIC_SKW
#define _HHEURISTIC_SKW

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
    class SuspiciousKeywordsHeuristicThreshold : public HeuristicBase
    {
        public:
            SuspiciousKeywordsHeuristicThreshold(Logger* logger, TempWriter* tempWriter, vector<string> suspiciousKeywords)
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _logger->WriteLog("[" + _heuristicName + "][Init]");

                _suspiciousKeywords = suspiciousKeywords;
                _writeHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction* action) override
            {
                if (action->ActionName == "WriteBufAction")
                {
                    _logger->WriteLog("[" + _heuristicName + "][Write action detected]");

                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(action);

                    string filePath = writeAction->FilePath;
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + filePath + "]");

                    string newContent = GetNewContent(filePath, writeAction);

                    bool foundAny = false;
                    for (std::vector<string>::iterator it = _suspiciousKeywords.begin(); it != _suspiciousKeywords.end(); ++it)
                    {
                        if (newContent.find(*it) != string::npos) 
                        {
                            foundAny = true;
                            _logger->WriteLog("[" + _heuristicName + "][Suspicious keyword detected: " + *it + "]");
                            _writeHistory->AddNewAction(writeAction);
                        }
                    }

                    if (!foundAny)
                    {
                        _logger->WriteLog("[" + _heuristicName + "][No suspicious keywords detected]");
                    }
                }

                RefreshTH();
                _logger->WriteLog("[" + _heuristicName + "][New threshold: " + GetThAsString() + "]");
            }

            ~SuspiciousKeywordsHeuristicThreshold()
            {
                _logger->WriteLog("[" + _heuristicName + "][Exit]");
                delete _writeHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeHistory;
            vector<string> _suspiciousKeywords;
            string _heuristicName = "Suspicious Keywords";

            void RefreshTH()
            {
                int results = _writeHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Results found in history search: " + GetIntAsString(results) + "]");
                heuristicTH = results;
            }
    };
}

#endif