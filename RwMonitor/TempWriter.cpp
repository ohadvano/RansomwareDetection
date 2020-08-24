#include <string>

using namespace std;

namespace TempFile
{
    class TempWriter
    {
        public:
            TempWriter(string tempFilePath)
            {
                TempFilePath = tempFilePath;
                // TODO: Create temp file in path
            }

            void Write(string fileContent)
            {
                // TODO: Clean temp file
            }

            ~TempWriter()
            {
                // Delete file
            }

            string TempFilePath;

        private:
            pthread_mutex_t* _tempFileMutex;
    };
}