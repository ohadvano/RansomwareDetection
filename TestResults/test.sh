
echo "starting"



#FileTypeChangesHeuristic - same type

echo "#ifndef _HLOGGER\n\
#define _HLOGGER\n\
\n\
#include <string>\n\
#include <ctime>\n\
#include <fstream>\n\
#include <iostream>\n\
#include <time.h>\n\
\n\
using namespace std;\n\
\n\
#define DTTMFMTasdasdjuandiuansodiuasodiunad\n\
#define DTTMSZ 21\n\
\n\
namespace Log\n\
{\n\
    class Logger\n\
    {\n\
        public:\n\
            char* LogPath;\n\
\n\
            Logger(char* logPath)\n\
            {\n\
                string path = asdasdjuandiuansodiuasodiunad;\n\
                path += logPath;\n\
\n\
                time_t rawtime;\n\
                struct tm * timeinfo;\n\
                char buffer[80];\n\
\n\
                time (&rawtime);\n\
                timeinfo = localtime(&rawtime);\n\
\n\
                strftime(buffer,sizeof(buffer),asdasdjuandiuansodiuasodiunad,timeinfo);\n\
                std::string date(buffer);\n\
  \n\
                path += date;\n\
\n\
                char* finalLogPath = (char*)malloc(path.length() + 1);\n\
                strcpy(finalLogPath, path.c_str()); \n\
\n\
                LogPath = finalLogPath;\n\
\n\
                if (std::ifstream(LogPath))\n\
                {\n\
                    return;\n\
                }\n\
                else\n\
                {\n\
                    std::ofstream file { LogPath };\n\
                }\n\
\n\
                WriteLog(asdasdjuandiuansodiuasodiunad);\n\
            }\n\
\n\
            void WriteLog(string logInfo)\n\
            {\n\
                if (!std::ifstream(LogPath))\n\
                {\n\
                    return;			\n\
                }\n\
\n\
                char buff[DTTMSZ];\n\
                std::ofstream file;\n\
                file.open(LogPath, std::ios_base::app);\n\
                file << asdasdjuandiuansodiuasodiunad << logInfo << endl;\n\
                file.close();            \n\
            }\n\
\n\
            void WriteError(string logError)\n\
            {\n\
                if (!std::ifstream(LogPath))\n\
                {\n\
                    return;\n\
                }\n\
\n\
                char buff[DTTMSZ];\n\
                std::ofstream file;\n\
                file.open(LogPath, std::ios_base::app);\n\
                file << asdasdjuandiuansodiuasodiunad << logError << endl;\n\
                file.close();\n\
            }\n\
\n\
        private:\n\
            char* getDtTm (char *buff) \n\
            {\n\
                time_t t = time (0);\n\
                strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));\n\
                buff[strlen(buff) - 1] = 0;\n\
                return buff;\n\
            }\n\
    };\n\
}\n\
\n\
#endif\n\
" > oz1.txt    # TH=4

echo "done"







