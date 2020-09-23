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
            virtual void CalculateTH(FsAction* action) = 0;

            virtual ~HeuristicBase()
            {
            }

            int _lookBackTime = 30;
            double heuristicTH = 0;

            TempWriter* _tempWriter;
            TempWriter* _tempWriter2;

            Logger* _logger;

            string GetNewContent(string filePath, WriteBufAction* writeAction)
            {
                char* mem1 = writeAction->InputData1;
                string str(mem1);
                return str;
            }

            string GetOldContent(WriteBufAction* writeAction)
            {
				return writeAction->OldContent;
            }

			uint8* ReadFile(string filePath)
			{
				string res;
				string full_res;
				ifstream file(filePath);
				while (getline(file, res))
				{
					full_res = full_res + res;
				}
				file.close();
				uint8 *full_res_conv = new unsigned char[full_res.length() + 1];
				strcpy((char *)full_res_conv, full_res.c_str());
				return full_res_conv;
			}

            string ReadFileToString(string filePath)
			{
				string res;
				string full_res;
				ifstream file(filePath);

				while (getline(file, res))
				{
					full_res = full_res + res;
				}

				file.close();

                return full_res;
			}

			int GetLength(uint8* byteStream)
			{
				return strlen((char*)byteStream);
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
                int s_num = -1;
                stringstream geek(s);
                geek >> s_num;
                return s_num;
            }

            string GetThAsString()
            {
                return GetDoubleAsString(heuristicTH);
            }

            string GetIntAsString(int val)
            {
                ostringstream strs;
                strs << val;
                string str = strs.str();
                return str;
            }

            string GetDoubleAsString(double val)
            {
                ostringstream strs;
                strs << val;
                string str = strs.str();
                return str;
            }
        private:
            char const* _tmpFile = "Run//temp_file_res.txt";
            string execute_program(string prog_name, string arg1, string arg2)
            {
                int pid = fork();
                if (pid==0)
                {
                    string command;
                    if (prog_name == "EXE_FILE")
                    {
                        command = "file " + arg1 + " | cut -d\":\" -f2 | cut -c2-  > " + _tmpFile;
                    }
                    else
                    {
                        command = "sdhash -g " + arg1 + " " + arg2 + " | cut -d\"|\" -f3 > " + _tmpFile;
                    }


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

                    int similarityMeasurementScore = RunSdHash(_tempWriter2->TempFilePath, _tempWriter->TempFilePath);
                    _logger->WriteLog("[" + _heuristicName + "][Similarity score: " + GetIntAsString(similarityMeasurementScore) + "]");

                    if (similarityMeasurementScore == -1)
                    {
                        // TODO
                    }
                    else if (similarityMeasurementScore < _threshold)
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

    class ShannonEnthropyHeuristic : public HeuristicBase
    {
        public:
            ShannonEnthropyHeuristic(Logger* logger, TempWriter* tempWriter, int threshold)
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
                    _logger->WriteLog("[" + _heuristicName + "][Enthropy after: " + GetDoubleAsString(enthropyBefore) + "]");

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

    class FilesDeletionHeuristic : public HeuristicBase
    {
        public:
            FilesDeletionHeuristic(Logger* logger, TempWriter* tempWriter)
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
            }
    };

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

                    for (std::vector<string>::iterator it = _suspiciousKeywords.begin(); it != _suspiciousKeywords.end(); ++it)
                    {
                        if (newContent.find(*it) != string::npos) 
                        {
                            _logger->WriteLog("[" + _heuristicName + "][Suspicious keyword detected: " + *it + "]");
                            _writeHistory->AddNewAction(writeAction);
                        }
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