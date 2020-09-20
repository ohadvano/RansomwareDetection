
echo "starting"



#FileTypeChangesHeuristic - same type

echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME asdinhasdunhasudnhais
# define LOG_PATH asdoasdoiandoasdasdoasodasd
#define DTTMFMT aspdmiasidmaosidaoisdo
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
    				file << getDtTm (buff) << <<logError << endl;
				file.close();
			}
    };
}

using namespace Log;
int main()
{

	cout << asdasd<< endl;
        Logger*  new_logger= new Logger(LOG_PATH);
	new_logger->WriteLog(asdasdasdasdasdasdasdasdasdasdasd);
	new_logger->WriteLog(asdasdasdasdasdasdasdavda;sdimapsvid);
new_logger->WriteError(asdasjdnoasdnhiuashdniuashdiuashdi);
	return 0;
}
" > oz1.txt    # TH=4

echo "done"







