#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadoz/Desktop/oz_test/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t = time (0);
    strftime (buff, DTTMSZ, DTTMFMT, localtime (&t));
    return buff;
}



namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
				if (std::ifstream(LOG_NAME))
				{
					return;
					
				}
				else
				{
					std::ofstream file{ LOG_NAME };
					LogPath = logPath;
				}
            }

            void WriteLog(string logInfo)
            {
				if (!std::ifstream(LOG_NAME))
				{
				return;			
				}
   				char buff[DTTMSZ];
				std::ofstream file;
				file.open(LOG_NAME, std::ios_base::app);
    				file << getDtTm (buff) << logInfo << endl;
				file.close();

			}

            void WriteError(string logError)
            {
				if (!std::ifstream(LOG_NAME))
				{
				return;
				}
   				char buff[DTTMSZ];
				std::ofstream file;
				file.open(LOG_NAME, std::ios_base::app);
    				file << getDtTm (buff) << "ERROR:"<<logError << endl;
				file.close();
			}
    };
}

using namespace Log;
int main()
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
	new_logger->WriteLog("wowwwwwwwwwwwwwwwwwww\n");
	new_logger->WriteLog("1111111111111111111111\n");
new_logger->WriteError("2222222222222222222222\n");
	return 0;
}

