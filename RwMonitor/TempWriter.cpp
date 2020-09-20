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
                string path = "Run//";
                path += tempFilePath;

                char* finalTempFilePath = (char*)malloc(path.length() + 1);
                strcpy(finalTempFilePath, path.c_str()); 

                TempFilePath = finalTempFilePath;

                if (std::ifstream(TempFilePath))
                {
                    return;
                }
                else
                {
                    std::ofstream file { TempFilePath };
                }
            }

            void Write(string fileContent)
            {
                if (!std::ifstream(TempFilePath))
                {
                    return;
                }

                std::ofstream file;
                file.open(TempFilePath, std::ios_base::app);
                file << fileContent << endl;
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