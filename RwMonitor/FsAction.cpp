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
            uint64_t Inode;
            size_t Size;
            void* Mem;
            int Fd;
            off_t Pos;
            off_t Offset;

            WriteBufAction(uint64_t inode, size_t size, void* mem, int fd, off_t pos, off_t offset, int callingProccessId) 
                : FsAction("WriteBufAction", callingProccessId), 
                    Inode(inode),
                    Size(size),
                    Mem(mem),
                    Fd(fd),
                    Pos(pos),
                    Offset(offset)
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
