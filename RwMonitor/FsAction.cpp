#ifndef _HFSACTION
#define _HFSACTION

#include <string>
#include <ctime>
#include <sys/stat.h>

using namespace std;

namespace FileSystemActions
{
    class FsAction 
    {
        public:
            string ActionName;
            virtual ~FsAction() = default;

        protected:
            time_t ActionDate;
            pid_t CallingProccessId;

            FsAction(string actionName, int callingProccessId) 
                : ActionName(actionName), ActionDate(time(0)), CallingProccessId(callingProccessId) 
            {
            }
    };

    class WriteBufAction : public FsAction
    {
        public:
            string FilePath;
            string OldContent;
            char* InputData1;
            char* InputData2;

            WriteBufAction(string filePath, string oldContent, char* inputData1, char* inputData2, uint64_t fd, int callingProccessId) 
                : FsAction("WriteBufAction", callingProccessId), 
                    OldContent(oldContent),
                    FilePath(filePath),
                    InputData1(inputData1),
                    InputData2(inputData2)
            {
            }
    };

    class RmdirAction : public FsAction
    {
        public:
            string DirectoryPath;

            RmdirAction(string directoryPath, int callingProccessId) 
                : FsAction("RmdirAction", callingProccessId),
                    DirectoryPath(directoryPath)
            {
            }
    };

    class ForgetAction : public FsAction
    {
        public:
            string FilePath;

            ForgetAction(string filePath, int callingProccessId) 
                : FsAction("ForgetAction", callingProccessId), 
                    FilePath(filePath)
            {
            }
    };
}

#endif
