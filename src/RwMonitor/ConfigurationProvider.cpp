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

            bool IsDebugMode()
            {
                return _isDebugMode;
            }

            char* GetLogFilePath()
            {
                return _logFilePath;
            }

            char* GetTempFilePath()
            {
                return _tmpFilePath;
            }

            char* GetTempFilePath2()
            {
                return _tmpFilePath2;
            }

            int GetSystemLockDownDuration()
            {
                return _systemLockDownDuration;
            }
            
            double GetMinAccumulatedThreshold()
            {
                return _minAccumulatedThreshold;
            }

            double* GetHeuristicsWeights()
            {
                return _heuristicsWeights;
            }

            double* GetIndividualThresholds()
            {
                return _individualThresholds;
            }

            int GetLookbackTime()
            {
                return _lookbackTime;
            }

        private:
            bool _isDebugMode;
            int _similarityTh;
            int _enthropyTh;
            int _systemLockDownDuration;
            vector<string> _suspiciousKeywords;
            char* _logFilePath;
            char* _tmpFilePath;
            char* _tmpFilePath2;
            double _minAccumulatedThreshold;
            double* _heuristicsWeights;
            double* _individualThresholds;
            int _lookbackTime;

            regex _runningModeRegex = regex("Debug: (.*);");
            regex _logFilePathRegex = regex("LogFilePath: (.*);");
            regex _tmpFilePathRegex = regex("TempFilePath: (.*);");
            regex _tmpFilePath2Regex = regex("TempFilePath2: (.*);");
            regex _systemLockDownDurationRegex = regex("SystemLockDownDuration: (.*);");
            regex _similarityThRegex = regex("SimilarityMeasurement: (.*);");
            regex _enthropyThRegex = regex("ShannonEnthropy: (.*);");
            regex _suspiciousKeywordsRegex = regex("SuspiciousKeywords: (.*);");
            regex _minAccumulatedThresholdRegex = regex("MinAccumulatedThreshold: (.*);");
            regex _heuristicsWeightsRegex = regex("HeuristicsWeights: (.*);");
            regex _individualThresholdRegex = regex("IndividualThresholdRegex: (.*);");
            regex _lookbackTimeRegex = regex("LookbackTime: (.*);");

            void Init(char const* configPath)
            {
                ifstream inFile;
                inFile.open(configPath);

                stringstream strStream;
                strStream << inFile.rdbuf();
                inFile.close();
                string str = strStream.str();

                char* runningModeStr = Parse(str, _runningModeRegex);
                char* similarityString = Parse(str, _similarityThRegex);
                char* enthropyString = Parse(str, _enthropyThRegex);
                char* systemLockDownDurationString = Parse(str, _systemLockDownDurationRegex);
                char* suspiciousKeywordsString = Parse(str, _suspiciousKeywordsRegex);
                char* logFilePathString = Parse(str, _logFilePathRegex);
                char* tmpFilePathString = Parse(str, _tmpFilePathRegex);
                char* tmpFilePath2String = Parse(str, _tmpFilePath2Regex);
                char* minAccumulatedThreshold = Parse(str, _minAccumulatedThresholdRegex);
                char* heuristicsWeights = Parse(str, _heuristicsWeightsRegex);
                char* individualThreshold = Parse(str, _individualThresholdRegex);
                char* lookbackTime = Parse(str, _lookbackTimeRegex);

                _isDebugMode = IsDebugMode(runningModeStr);
                _similarityTh = ConvertToInt(similarityString);
                _enthropyTh = ConvertToInt(enthropyString);
                _systemLockDownDuration = ConvertToInt(systemLockDownDurationString);
                _suspiciousKeywords = SplitToWords(suspiciousKeywordsString, ',');
                _logFilePath = logFilePathString;
                _tmpFilePath = tmpFilePathString;
                _tmpFilePath2 = tmpFilePath2String;
                _minAccumulatedThreshold = ConvertToDouble(minAccumulatedThreshold);
                _heuristicsWeights = ParseDoubleArray(heuristicsWeights);
                _individualThresholds = ParseDoubleArray(individualThreshold);
                _lookbackTime = ConvertToInt(lookbackTime);
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

            bool IsDebugMode(char* str)
            {
                string strAsString(str);
                if (strAsString == "true")
                {
                    return true;
                }
                
                return false;
            }

            int ConvertToInt(char* str)
            {
                string strAsString(str);
                stringstream stream1(strAsString); 
                int val = 0;
                stream1 >> val;
                return val;
            }

            double ConvertToDouble(char* str)
            {
                string strAsString(str);
                stringstream stream1(strAsString); 
                double val = 0;
                stream1 >> val;
                return val;
            }

            double* ParseDoubleArray(char* str)
            {
                int idx = 0;
                int numHeuristics = 5;
                double* res = (double*)malloc(sizeof(double) * numHeuristics);
                vector<string> splitted = SplitToWords(str, ',');
                for (std::vector<string>::iterator it = splitted.begin(); it != splitted.end(); ++it)
                {
                    string individualRes = *it;
                    char* char_array = (char*)malloc(individualRes.length() + 1);
                    strcpy(char_array, individualRes.c_str()); 
                    res[idx] = ConvertToDouble(char_array);
                    delete[] char_array;
                    idx++;
                }

                return res;
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