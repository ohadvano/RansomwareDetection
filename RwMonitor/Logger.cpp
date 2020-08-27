#include <string>
#include <ctime>

using namespace std;

namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
                LogPath = logPath;

                // TODO: Create log in path
            }

            void WriteLog(string logInfo)
            {
                // TODO: Write to log with timestamp
            }

            void WriteError(string logError)
            {
                // TODO: Write to log with "Error" before text with timestamp
            }
    };
}