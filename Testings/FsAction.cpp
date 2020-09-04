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

        protected:
            time_t ActionDate;
            pid_t CallingProccessId;

            FsAction(string actionName, int callingProccessId) 
                : ActionName(actionName), ActionDate(time(0)), CallingProccessId(callingProccessId) 
            {

            }
    };

    class FileInfoContract
    {
        public: 
            int Flags;
            unsigned int WritePage;
            unsigned int DirectIo;
            unsigned int KeepCache;
            unsigned int Flush;
            unsigned int NonSeekable;
            unsigned int FlockRelease;
            unsigned int CacheReaddir;
            unsigned int Padding;
            unsigned int Padding2;
            uint64_t Fh;
            uint64_t LockOwner;
            uint32_t PollEvents;

            FileInfoContract(int flags, unsigned int writePage, unsigned int directIo, unsigned int keepCache, unsigned int flush,
                                unsigned int nonSeekable, unsigned int flockRelease, unsigned int cacheReaddir, unsigned int padding, 
                                unsigned int padding2, uint64_t fh, uint64_t lockOwner, uint32_t pollEvents)
                : Flags(flags), WritePage(writePage), DirectIo(directIo), KeepCache(keepCache), Flush(flush), 
                    NonSeekable(nonSeekable), FlockRelease(flockRelease), CacheReaddir(cacheReaddir), Padding(padding), Padding2(padding2),
                    Fh(fh), LockOwner(lockOwner), PollEvents(pollEvents) { }

            FileInfoContract() { }
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
            FileInfoContract FileInfo;

            WriteBufAction(uint64_t inode, size_t size, void* mem, int fd, off_t pos, off_t offset, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("WriteBufAction", callingProccessId), 
                    Inode(inode),
                    Size(size),
                    Mem(mem),
                    Fd(fd),
                    Pos(pos),
                    Offset(offset),
                    FileInfo(fileInfo)
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
