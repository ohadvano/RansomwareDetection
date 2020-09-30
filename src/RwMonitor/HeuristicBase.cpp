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
}

#endif