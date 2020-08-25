#include <string>
#include <ctime>
#include <sys/stat.h>

using namespace std;

namespace Configurations
{
    static class ConfigurationProvider
    {
        public:
            ConfigurationProvider()
            {
                _configPath = "parameters.config";
                Init();
            }

            int GetSimilarityThreshold()
            {
                return _similarityTh;
            }

            int GetEnthropyThreshold()
            {
                return _enthropyTh;
            }

            string* GetSuspiciousKeywords()
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
            string _configPath;
            int _similarityTh;
            int _enthropyTh;
            string* _suspiciousKeywords;
            char* _logFilePath;
            char* _tmpFilePath;
            int _systemLockDownDuration;
            
            void Init()
            {

            }
    };
}