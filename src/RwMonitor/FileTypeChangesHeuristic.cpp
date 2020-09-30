#ifndef _HHEURISTIC
#define _HHEURISTIC

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

using namespace FileSystemActions;
using namespace Log;
using namespace TempFile;
using namespace std;
using namespace ActionsHistory;

typedef unsigned char uint8;

namespace Heuristics
{
    class FileTypeChangesHeuristic : public HeuristicBase
    {
        public:
            FileTypeChangesHeuristic(Logger* logger, TempWriter* tempWriter)
            {
                _tempWriter = tempWriter;
                _logger = logger;

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
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + writeAction->FilePath + "]");

                    _tempWriter->Write(GetOldContent(writeAction));
                    string beforeType = RunFileUtility(_tempWriter->TempFilePath);
                    _logger->WriteLog("[" + _heuristicName + "][Type before: " + beforeType + "]");

                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    string afterType = RunFileUtility(_tempWriter->TempFilePath);
                    _logger->WriteLog("[" + _heuristicName + "][Type after: " + afterType + "]");

                    if (beforeType != afterType)
                    {
                        _logger->WriteLog("[" + _heuristicName + "][File type change detected from: " + beforeType + " to: " + afterType + "]");
                        _writeBufHistory->AddNewAction(writeAction);
                    }
                }

                RefreshTH();
                _logger->WriteLog("[" + _heuristicName + "][New threshold: " + GetThAsString() + "]");
            }

            ~FileTypeChangesHeuristic()
            {
                _logger->WriteLog("[" + _heuristicName + "][Exit]");
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;
            string _heuristicName = "File Type Changes";

            void RefreshTH()
            {
                int results = _writeBufHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Results found in history search: " + GetIntAsString(results) + "]");

                heuristicTH = results;
            }
    };
}

#endif