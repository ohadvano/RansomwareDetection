#ifndef _HCP
#define _HCP

#include <string>
#include <ctime>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>

using namespace std;

namespace Configurations
{
    class ConfigurationProvider
    {
        public:
            ConfigurationProvider(char const* configPath)
            {           
                Init(configPath);
            }

            int GetSimilarityThreshold()
            {
                return _similarityTh;
            }

            int GetEnthropyThreshold()
            {
                return _enthropyTh;
            }

            vector<string> GetSuspiciousKeywords()
            {
                return _suspiciousKeywords;
            }

            char* GetLogFilePath()
            {
                return _logFilePath;
            }

            char* GetTempFilePath()
            {
                return _tmpFilePath;
            }

            int GetSystemLockDownDuration()
            {
                return _systemLockDownDuration;
            }
            
        private:
            int _similarityTh;
            int _enthropyTh;
            int _systemLockDownDuration;
            vector<string> _suspiciousKeywords;
            char* _logFilePath;
            char* _tmpFilePath;

            regex _logFilePathRegex = regex("LogFilePath: #(.*)#;");
            regex _tmpFilePathRegex = regex("TempFilePath: #(.*)#;");
            regex _systemLockDownDurationRegex = regex("SystemLockDownDuration: #(.*)#;");
            regex _similarityThRegex = regex("SimilarityMeasurement: #(.*)#;");
            regex _enthropyThRegex = regex("ShannonEnthropy: #(.*)#;");
            regex _suspiciousKeywordsRegex = regex("SuspiciousKeywords: #(.*)#;");
            
            void Init(char const* configPath)
            {
                ifstream inFile;
                inFile.open(configPath);

                stringstream strStream;
                strStream << inFile.rdbuf();
                string str = strStream.str();

                char* similarityString = Parse(str, _similarityThRegex);
                char* enthropyString = Parse(str, _enthropyThRegex);
                char* systemLockDownDurationString = Parse(str, _systemLockDownDurationRegex);
                char* suspiciousKeywordsString = Parse(str, _suspiciousKeywordsRegex);
                char* logFilePathString = Parse(str, _logFilePathRegex);
                char* tmpFilePathString = Parse(str, _tmpFilePathRegex);

                // Open file and write, Till Logger
                ofstream myfile;
                myfile.open ("example1.txt");
                myfile << "Writing this to a file.\n";
                myfile.close();

                _similarityTh = ConvertToInt(similarityString);
                _enthropyTh = ConvertToInt(enthropyString);
                _systemLockDownDuration = ConvertToInt(systemLockDownDurationString);
                _suspiciousKeywords = SplitToWords(suspiciousKeywordsString, ',');
                _logFilePath = logFilePathString;
                _tmpFilePath = tmpFilePathString;
                
                                // Open file and write, Till Logger
                myfile.open ("example2.txt");
                myfile << "Writing this to a file.\n";
                myfile.close();
            }

            char* Parse(string str, regex reg)
            {
                std::smatch m;
                vector<string> lines = SplitToWords(str, '\n');
                for (std::vector<string>::iterator it = lines.begin() ; it != lines.end(); ++it)
                {
                    string current = *it;
                    if (std::regex_match(current, m, reg))
                    {
                        string res = m[1];
                        stringstream buffer;
                        char* char_array = (char*)malloc(res.length() + 1);
                        strcpy(char_array, res.c_str()); 
                        return char_array;
                    }
                }

                return nullptr;
            }

            int ConvertToInt(char* str)
            {
                string strAsString(str);
                stringstream stream1(strAsString); 
                int val = 0;
                stream1 >> val;
                return val;
            }

            vector<string> SplitToWords (char* str, char delim) 
            {
                string strAsString(str);
                vector<string> result;
                stringstream ss (strAsString);
                string item;

                while (getline (ss, item, delim)) 
                {
                    result.push_back (item);
                }

                return result;
            }

            vector<string> SplitToWords (string str, char delim) 
            {
                vector<string> result;
                stringstream ss (str);
                string item;

                while (getline (ss, item, delim)) 
                {
                    result.push_back (item);
                }

                return result;
            }
    };
}

#endif