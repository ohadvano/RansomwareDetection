#ifndef _HHEURISTIC_SM
#define _HHEURISTIC_SM

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
    class SimilarityMeasurementHeuristic : public HeuristicBase
    {
        public:
            SimilarityMeasurementHeuristic(Logger* logger, TempWriter* tempWriter, TempWriter* tempWriter2, int threshold)
            {
                
                _tempWriter = tempWriter;
                _tempWriter2 = tempWriter2;

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
                    _logger->WriteLog("[" + _heuristicName + "][File path: " + writeAction->FilePath + "]");

                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    _tempWriter2->Write(GetOldContent(writeAction));

                    _logger->WriteLog("new: " + GetNewContent(filePath, writeAction));
                    
                    int similarityMeasurementScore = RunSdHash(_tempWriter2->TempFilePath, _tempWriter->TempFilePath);
                    _logger->WriteLog("[" + _heuristicName + "][Similarity score: " + GetIntAsString(similarityMeasurementScore) + "]");

                    if (similarityMeasurementScore != -1 && similarityMeasurementScore < _threshold)
                    {
                        _logger->WriteLog("[" + _heuristicName + "][Similarity measurement anormaliy detected]");
                        _writeBufHistory->AddNewAction(writeAction);
                    }
                }

                RefreshTH();
                _logger->WriteLog("[" + _heuristicName + "][New threshold: " + GetThAsString() + "]");
            }

            ~SimilarityMeasurementHeuristic()
            {
                _logger->WriteLog("[" + _heuristicName + "][Exit]");
                delete _writeBufHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeBufHistory;
            int _threshold;
            string _heuristicName = "Similarity Measurement";

            void RefreshTH()
            {
                int results = _writeBufHistory->LookBack(_lookBackTime);
                _logger->WriteLog("[" + _heuristicName + "][Results found in history search: " + GetIntAsString(results) + "]");

                heuristicTH = results;
            }
    };
}

#endif