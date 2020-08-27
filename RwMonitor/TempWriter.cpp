#include <string>

using namespace std;

namespace TempFile
{
    class TempWriter
    {
        public:
            char* TempFilePath;

            TempWriter(char* tempFilePath)
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
    };
}