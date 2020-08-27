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

            regex _logFilePathRegex = regex("LogFilePath: #(.*)#;");
            regex _tmpFilePathRegex = regex("TempFilePath: #(.*)#;");
            regex _systemLockDownDurationRegex = regex("SystemLockDownDuration: #(.*)#;");
            regex _similarityThRegex = regex("SimilarityMeasurement: #(.*)#;");
            regex _enthropyThRegex = regex("ShannonEnthropy: #(.*)#;");
            regex _suspiciousKeywordsRegex = regex("SuspiciousKeywords: #(.*)#;");
            
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

                // cout << "Similarity " << similarityString << endl;
                // cout << "Enthropy " << enthropyString << endl;
                // cout << "SuspiciousKeywordsString " << suspiciousKeywordsString << endl;
                // cout << "logFilePathString " << logFilePathString << endl;
                // cout << "tmpFilePathString " << tmpFilePathString << endl;
                // cout << "systemLockDownDurationString " << systemLockDownDurationString << endl;

                _similarityTh = ConvertToInt(similarityString);
                _enthropyTh = ConvertToInt(enthropyString);
                _systemLockDownDuration = ConvertToInt(systemLockDownDurationString);
                _suspiciousKeywords = SplitToWords(suspiciousKeywordsString, ',');
                _logFilePath = logFilePathString;
                _tmpFilePath = tmpFilePathString;

                cout << endl << endl;

                // cout << "Similarity final " << _similarityTh << endl;
                // cout << "Enthropy final " << _enthropyTh << endl;
                // cout << "systemLockDownDurationString final " << _systemLockDownDuration << endl;
                // cout << "logFilePathString final " << _logFilePath << endl;
                // cout << "tmpFilePathString final " << _tmpFilePath << endl;

                cout << endl;
                for (std::vector<string>::iterator it = _suspiciousKeywords.begin() ; it != _suspiciousKeywords.end(); ++it)
                {
                    std::cout << ' ' << *it;
                }
            }

            char* Parse(string str, regex reg)
            {
                vector<string> lines = SplitToWords(str, '\n');
                for (std::vector<string>::iterator it = _suspiciousKeywords.begin() ; it != _suspiciousKeywords.end(); ++it)
                {
                    std::cout << ' ' << *it;
                }

                cout << endl << endl;
                
                std::smatch m;
                cout << str << endl;
                cout << std::regex_match(str, m, reg) << std::endl;
                for (auto result : m) 
                {
                    stringstream buffer;
                    buffer << result;
                    string str1 = buffer.str();
                    int n = str1.length(); 
                    char* char_array = (char*)malloc(sizeof(char) * (n+1));
                    strcpy(char_array, str1.c_str()); 
                    return char_array;
                }
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