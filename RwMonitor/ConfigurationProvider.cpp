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
            ConfigurationProvider(char* configPath)
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

            const char* _logFilePathRegex = "LogFilePath: #(.*)#;";
            const char* _tmpFilePathRegex = "TempFilePath: #(.*)#;";
            const char* _systemLockDownDurationRegex = "SystemLockDownDuration: #(.*)#;";
            const char* _similarityThRegex = "SimilarityMeasurement: #(.*)#;";
            const char* _enthropyThRegex = "ShannonEnthropy: #(.*)#;";
            const char* _suspiciousKeywordsRegex = "SuspiciousKeywords: #(.*)#;";

            
            void Init(char* configPath)
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

                _similarityTh = ConvertToInt(similarityString);
                _enthropyTh = ConvertToInt(enthropyString);
                _systemLockDownDuration = ConvertToInt(systemLockDownDurationString);
                _suspiciousKeywords = SplitToWords(suspiciousKeywordsString, ',');
                _logFilePath = logFilePathString;
                _tmpFilePath = tmpFilePathString;
            }

            char* Parse(string str, regex reg)
            {
                std::smatch m;
                std::cout << std::regex_match(str, m, regex) << std::endl;
                for (auto result : m) 
                {
                    stringstream buffer;
                    buffer << result;
                    string str1 = buffer.str();
                    int n = str1.length(); 
                    char char_array[n + 1];
                    strcpy(char_array, str1.c_str()); 
                    return char_array;
                }
            }

            int ConvertToInt(char* str)
            {
                string strAsString(str);
                int val = 0;
                str >> val;
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
    };
}