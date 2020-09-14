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
            char* InputData1;
            char* InputData2;

            WriteBufAction(string filePath, char* inputData1, char* inputData2, uint64_t fd, int callingProccessId) 
                : FsAction("WriteBufAction", callingProccessId), 
                    FilePath(filePath),
                    InputData1(inputData1),
                    InputData2(inputData2)
            {
            }
    };

    class RmdirAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;

            RmdirAction(uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("RmdirAction", callingProccessId), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    class ForgetAction : public FsAction
    {
        public:
            uint64_t Parent;
            uint64_t Nlookup;

            ForgetAction(uint64_t parent, uint64_t nlookup, int callingProccessId) 
                : FsAction("ForgetAction", callingProccessId), 
                    Parent(parent), 
                    Nlookup(nlookup)
            {
            }
    };
}

#endif
