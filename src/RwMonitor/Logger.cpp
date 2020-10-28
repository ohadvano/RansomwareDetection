#ifndef _HLOGGER
#define _HLOGGER

#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

#define DTTMFMT "%Y-%m-%d %H:%M:%S"
#define DTTMSZ 21

namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
                string path = "//home//ohadoz//Desktop//RansomwareDetection//src//Run//";
                path += logPath;

                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];

                time (&rawtime);
                timeinfo = localtime(&rawtime);

                strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H-%M-%S",timeinfo);
                std::string date(buffer);
  
                path += date;

                char* finalLogPath = (char*)malloc(path.length() + 1);
                strcpy(finalLogPath, path.c_str()); 

                LogPath = finalLogPath;

                if (std::ifstream(LogPath))
                {
                    return;
                }
                else
                {
                    std::ofstream file { LogPath };
                }

                if (pthread_mutex_init(&_logLock, nullptr) != 0)
                {
                    fprintf(stderr, "error: _logLock mutex init has failed");
                    exit(1);
                }

                WriteLog("[Log started]");
            }

            void WriteLog(string logInfo)
            {
                if (!std::ifstream(LogPath))
                {
                    return;			
                }

                char buff[DTTMSZ];
                std::ofstream file;
                pthread_mutex_lock(&_logLock);
                file.open(LogPath, std::ios_base::app);
                file << "[" << getDtTm (buff) << "]" << logInfo << endl;
                file.close();
                pthread_mutex_unlock(&_logLock);

            }

            void WriteError(string logError)
            {
                if (!std::ifstream(LogPath))
                {
                    return;
                }

                char buff[DTTMSZ];
                std::ofstream file;
                pthread_mutex_lock(&_logLock);
                file.open(LogPath, std::ios_base::app);
                file << "[" << getDtTm (buff) << "]" << "[ERROR]" << logError << endl;
                file.close();
                pthread_mutex_unlock(&_logLock);

            }

            ~Logger()
            {
                pthread_mutex_unlock(&_logLock);
                pthread_mutex_destroy(&_logLock);
            }

        private:
            pthread_mutex_t _logLock;

            char* getDtTm (char *buff) 
            {
                time_t t = time (0);
                strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
                return buff;
            }
    };
}

#endif