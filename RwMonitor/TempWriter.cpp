#ifndef _HTMPWRITER
#define _HTMPWRITER

#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21

namespace TempFile
{
    class TempWriter
    {
        public:
            char* TempFilePath;

            TempWriter(char* tempFilePath)
            {
                TempFilePath = tempFilePath;

                if (std::ifstream(TempFilePath))
                {
                    return;
                }
                else
                {
                    std::ofstream file { "Run/" + TempFilePath };
                }
            }

            void Write(string fileContent)
            {
                if (!std::ifstream(TempFilePath))
                {
                    return;
                }

                char buff[DTTMSZ];
                std::ofstream file;
                file.open(TempFilePath, std::ios_base::app);
                file << getDtTm(buff) << fileContent << endl;
                file.close();
            }

            ~TempWriter()
            {
                remove(TempFilePath);
            }
        private:
            char* getDtTm (char *buff) 
            {
                time_t t = time(0);
                strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
                return buff;
            }
    };
}

#endif