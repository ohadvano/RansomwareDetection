#include <string>
#include <ctime>

using namespace std;

namespace Log
{
    class Logger
    {
        public:
            string LogPath;

            Logger(string logPath)
            {
                LogPath = logPath;

                if (pthread_mutex_init(_logMutex, nullptr) != 0)
                {
                    fprintf(stderr, "error: _logMutex mutex init has failed");
                    exit(1);
                }

                // TODO: Create log in path
            }

            void WriteLog(string logInfo)
            {
                // TODO: Lock log
                // TODO: Write to log with timestamp
                // TODO: Unlock log
            }

            void WriteError(string logError)
            {
                // TODO: Lock log
                // TODO: Write to log with "Error" before text with timestamp
                // TODO: Unlock log
            }

            ~Logger()
            {
                pthread_mutex_unlock(_logMutex);
                pthread_mutex_destroy(_logMutex);
            }

        private:
            pthread_mutex_t* _logMutex;
    };
}