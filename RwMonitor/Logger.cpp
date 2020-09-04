#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21

namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
                LogPath = logPath;

                if (std::ifstream(LogPath))
                {
                    return;
                }
                else
                {
                    std::ofstream file { LogPath };
                }            
            }

            void WriteLog(string logInfo)
            {
                if (!std::ifstream(LogPath))
                {
                    return;			
                }

                char buff[DTTMSZ];
                std::ofstream file;
                file.open(LogPath, std::ios_base::app);
                file << getDtTm (buff) << logInfo << endl;
                file.close();            
            }

            void WriteError(string logError)
            {
                if (!std::ifstream(LogPath))
                {
                    return;
                }

                char buff[DTTMSZ];
                std::ofstream file;
                file.open(LogPath, std::ios_base::app);
                file << getDtTm (buff) << "ERROR: " << logError << endl;
                file.close();
            }

        private:
            char* getDtTm (char *buff) 
            {
                time_t t = time (0);
                strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
                return buff;
            }
    };
}
