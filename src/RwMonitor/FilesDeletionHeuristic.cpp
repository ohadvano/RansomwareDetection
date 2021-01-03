#ifndef _HHEURISTIC_FD
#define _HHEURISTIC_FD

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
    class FilesDeletionHeuristic : public HeuristicBase
    {
        public:
            FilesDeletionHeuristic(Logger* logger, TempWriter* tempWriter, int lookbackTime)
                : HeuristicBase { lookbackTime }
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _logger->WriteLog("[" + _heuristicName + "][Init]");

                _rmdirHistory = new ActionHistory<RmdirAction*>();
                _forgetHistory = new ActionHistory<ForgetAction*>();
            }

            void CalculateTH(FsAction* action) override
            {
                if (action->ActionName == "ForgetAction")
                {
                    _logger->WriteLog("[" + _heuristicName + "][Forget action detected]");

                    ForgetAction* forgetAction = dynamic_cast<ForgetAction*>(action);
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + forgetAction->FilePath + "]");

                    _forgetHistory->AddNewAction(forgetAction);
                }
                else if (action->ActionName == "RmdirAction")
                {
                    _logger->WriteLog("[" + _heuristicName + "][Rmdir action detected]");

                    RmdirAction* rmdirAction = dynamic_cast<RmdirAction*>(action);
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + rmdirAction->DirectoryPath + "]");

                    _rmdirHistory->AddNewAction(rmdirAction);
                }

                RefreshTH();
                _logger->WriteLog("[" + _heuristicName + "][New threshold: " + GetThAsString() + "]");
            }

            ~FilesDeletionHeuristic()
            {
                _logger->WriteLog("[" + _heuristicName + "][Exit]");
                delete _rmdirHistory;
                delete _forgetHistory;
            }

        private:
            ActionHistory<RmdirAction*>* _rmdirHistory;
            ActionHistory<ForgetAction*>* _forgetHistory;
            string _heuristicName = "Files Deletion";

            void RefreshTH()
            {
                int rmdirResults = _rmdirHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Rmdir results found in history search: " + GetIntAsString(rmdirResults) + "]");

                int forgetResults = _forgetHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Forget results found in history search: " + GetIntAsString(forgetResults) + "]");

                heuristicTH = rmdirResults + forgetResults;
            }
    };
}

#endif