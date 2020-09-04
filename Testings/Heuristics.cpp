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
                if (input < 0)
                {
                    return input * -1;
                }

                return input;
            }

            string RunFileUtility(string filePath)
            {
                return execute_program("EXE_FILE", filePath, "DONT_CARE");
            }
            
            int RunSdHash(string fileBeforePath, string fileAfterPath)
            {
                string s = execute_program("EXE_SDHASH", fileBeforePath, fileAfterPath);
                int s_num = 0;
                stringstream geek(s);
                geek >> s_num;
                return s_num;
            }
        private:
            char* _tmpFile = "temp_file_res.txt";
            string execute_program(string prog_name, string arg1, string arg2)
            { 
                int pid = fork();
                if (pid==0)
                {
                    string command = "bash ./helper.sh " + prog_name + " " + _tmpFile + " " + arg1 + " " + arg2;
                    const char* c_command = command.c_str();
                    system(c_command);
                    exit(0);
                }
                else
                {
                    wait(NULL);
                    string res;
                    string full_res;
                    ifstream file(_tmpFile);

                    while(getline(file,res))
                    {
                        full_res=full_res+res;
                    }

                    remove(_tmpFile);	
                    return full_res;	
                }
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

                    string beforeType = RunFileUtility(filePath);
                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    string afterType = RunFileUtility(_tempWriter->TempFilePath);

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

            ~SimilarityMeasurementHeuristic()
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

    class ShannonEnthropyHeuristic : public HeuristicBase
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
                    int lengthBefore = GetLength(inputBefore);
                    double enthropyBefore = CalculateEntropy(inputBefore, lengthBefore);

                    // After
                    _tempWriter->Write(GetNewContent(filePath, writeAction));
                    uint8* inputAfter = ReadFile(_tempWriter->TempFilePath);
                    int lengthAfter = GetLength(inputAfter);
                    double enthropyAfter = CalculateEntropy(inputBefore, lengthBefore);

                    if (Abs(enthropyBefore - enthropyAfter) < _threshold)
                    {
                        _writeBufHistory->AddNewAction(writeAction);
                    }
                }

                RefreshTH();
            }

            ~ShannonEnthropyHeuristic()
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

    class FilesDeletionHeuristic : public HeuristicBase
    {
        public:
            FilesDeletionHeuristic(Logger* logger, TempWriter* tempWriter)
            {
                _tempWriter = tempWriter;
                _logger = logger;

                _rmdirHistory = new ActionHistory<RmdirAction*>();
                _forgetHistory = new ActionHistory<ForgetAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "ForgetAction")
                {
                    ForgetAction* forgetAction = dynamic_cast<ForgetAction*>(&action);
                    _forgetHistory->AddNewAction(forgetAction);
                }
                else if (action.ActionName == "RmdirAction")
                {
                    RmdirAction* rmdirAction = dynamic_cast<RmdirAction*>(&action);
                    _rmdirHistory->AddNewAction(rmdirAction);
                }

                RefreshTH();
            }

            ~FilesDeletionHeuristic()
            {
                delete _rmdirHistory;
                delete _forgetHistory;
            }

        private:
            ActionHistory<RmdirAction*>* _rmdirHistory;
            ActionHistory<ForgetAction*>* _forgetHistory;

            void RefreshTH()
            {

            }
    };

    class SuspiciousKeywordsHeuristicThreshold : public HeuristicBase
    {
        public:
            SuspiciousKeywordsHeuristicThreshold(Logger* logger, TempWriter* tempWriter, vector<string> suspiciousKeywords)
            {
                _tempWriter = tempWriter;
                _logger = logger;
                _suspiciousKeywords = suspiciousKeywords;
                _writeHistory = new ActionHistory<WriteBufAction*>();
            }

            void CalculateTH(FsAction action) override
            {
                if (action.ActionName == "WriteBufAction")
                {
                    WriteBufAction* writeAction = dynamic_cast<WriteBufAction*>(&action);
                    string filePath = GetFilePathFromWriteAction(writeAction);
                    string newContent = GetNewContent(filePath, writeAction);
                }

                RefreshTH();
            }

            ~SuspiciousKeywordsHeuristicThreshold()
            {
                delete _writeHistory;
            }

        private:
            ActionHistory<WriteBufAction*>* _writeHistory;
            vector<string> _suspiciousKeywords;

            void RefreshTH()
            {

            }
    };
}

#endif