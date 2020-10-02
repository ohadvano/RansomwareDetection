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
            string NewContent;

            WriteBufAction(string filePath, string oldContent, string newContent, int callingProccessId) 
                : FsAction("WriteBufAction", callingProccessId), 
                    FilePath(filePath),
                    OldContent(oldContent),
                    NewContent(newContent)
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
