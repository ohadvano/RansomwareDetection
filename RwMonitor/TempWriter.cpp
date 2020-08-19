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

                if (pthread_mutex_init(_tempFileMutex, nullptr) != 0)
                {
                    fprintf(stderr, "error: _tempFileMutex mutex init has failed");
                    exit(1);
                }

                // TODO: Create temp file in path
            }

            void Lock()
            {
                // TODO: Lock temp
            }

            void Write(string fileContent)
            {
                // TODO: Clean temp file
                // TODO: Unlock log
            }

            void Unlock()
            {
                // TODO: Write file content
            }

            ~TempWriter()
            {
                pthread_mutex_unlock(_tempFileMutex);
                pthread_mutex_destroy(_tempFileMutex);

                // Delete file
            }

            string TempFilePath;

        private:
            pthread_mutex_t* _tempFileMutex;
    };
}