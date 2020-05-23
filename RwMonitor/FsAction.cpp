#ifndef _FS_ACTION_H_
#define _FS_ACTION_H_

#include <string>
#include <ctime>
#include <sys/stat.h>

using namespace std;

namespace FileSystemActions
{
    // Abstract class that represents a general file system action
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
    };

    // Lookup
    class LookupAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;

            LookupAction(uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    // Mkdir
    class MakedirAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;
            mode_t Mode;

            MakedirAction(uint64_t parent, const char* name, mode_t mode, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name), 
                    Mode(mode)
            {
            }
    };

    // Mknod
    class MakeNodeAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;
            mode_t Mode;
            dev_t Rdev;

            MakeNodeAction(uint64_t parent, const char* name, mode_t mode, dev_t rdev, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name), 
                    Mode(mode), 
                    Rdev(rdev)
            {
            }
    };

    // Symlink
    class SymLinkAction : public FsAction
    {
        public:
            const char* Link;
            uint64_t Parent;
            const char* Name;

            SymLinkAction(const char* link, uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Link(link), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    // Link
    class LinkAction : public FsAction
    {
        public:
            uint64_t Inode;
            uint64_t Parent;
            const char* Name;

            LinkAction(uint64_t inode, uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    // Link
    class UnLinkAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;

            UnLinkAction(uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    // Rmdir
    class RmdirAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;

            RmdirAction(uint64_t parent, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name)
            {
            }
    };

    // Rename
    class RenameAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;
            uint64_t NewParent;
            const char* NewName;
            unsigned int Flags;

            RenameAction(uint64_t parent, const char* name, uint64_t newParent, const char* newName, unsigned int flags, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name),
                    NewParent(newParent), 
                    NewName(newName),
                    Flags(flags)
            {
            }
    };

    // Forget
    class ForgetAction : public FsAction
    {
        public:
            uint64_t Parent;
            uint64_t Nlookup;

            ForgetAction(uint64_t parent, uint64_t nlookup, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Nlookup(nlookup)
            {
            }
    };

    // ForgetMulti : TODO

    // GetAttr
    class GetAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            GetAttrAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    FileInfo(fileInfo)
            {
            }
    };

    // SetAttr
    class SetAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            struct stat Attr;
            FileInfoContract FileInfo;
            int Valid;

            SetAttrAction(uint64_t inode, struct stat attr, FileInfoContract fileInfo, int valid, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    Attr(attr),
                    FileInfo(fileInfo),
                    Valid(valid)
            {
            }
    };

    // ReadLink
    class ReadLinkAction : public FsAction
    {
        public:
            uint64_t Inode;

            ReadLinkAction(uint64_t inode, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode)
            {
            }
    };

    // OpenDir
    class OpenDirAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            OpenDirAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    FileInfo(fileInfo)
            {
            }
    };

    // ReadDir
    class ReadDirAction : public FsAction
    {
        public:
            uint64_t Inode;
            size_t Size;
            off_t Offset;
            FileInfoContract FileInfo;

            ReadDirAction(uint64_t inode, size_t size, off_t offset, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    Size(size),
                    Offset(offset),
                    FileInfo(fileInfo)
            {
            }
    };

    // ReadDirPlus
    class ReadDirPlusAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            ReadDirPlusAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    Size(size),
                    Offset(offset),
                    FileInfo(fileInfo)
            {
            }
    };

    // ReleaseDir
    class ReleaseDirAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            ReleaseDirAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    FileInfo(fileInfo)
            {
            }
    };

    // FsyncDir
    class FsyncDirAction : public FsAction
    {
        public:
            uint64_t Inode;
            int DataSync;
            FileInfoContract FileInfo;

            FsyncDirAction(uint64_t inode, int dataSync, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode), 
                    DataSync(dataSync),
                    FileInfo(fileInfo)
            {
            }
    };

    // Create
    class CreateAction : public FsAction
    {
        public:
            uint64_t Parent;
            const char* Name;
            mode_t Mode;
            FileInfoContract FileInfo;

            CreateAction(uint64_t parent, const char* name, mode_t mode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Parent(parent), 
                    Name(name),
                    Mode(mode),
                    FileInfo(fileInfo)
            {
            }
    };

    // Open
    class OpenAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            OpenAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    FileInfo(fileInfo)
            {
            }
    };

    // Release
    class ReleaseAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;

            ReleaseAction(uint64_t inode, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    FileInfo(fileInfo)
            {
            }
    };

    // Flush
    class FlushAction : public FsAction
    {
        public:
            uint64_t Inode;
            int DataSync;
            FileInfoContract FileInfo;

            FlushAction(uint64_t inode, int dataSync, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    DataSync(dataSync),
                    FileInfo(fileInfo)
            {
            }
    };

    // Read
    class ReadAction : public FsAction
    {
        public:
            uint64_t Inode;
            size_t Size;
            off_t Offset;
            FileInfoContract FileInfo;

            ReadAction(uint64_t inode, size_t size, off_t offset, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Size(size),
                    Offset(offset),
                    FileInfo(fileInfo)
            {
            }
    };

    // WriteBuf
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
                : FsAction("LookupAction", callingProccessId), 
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

    // StatFs
    class StatFsAction : public FsAction
    {
        public:
            uint64_t Inode;

            StatFsAction(uint64_t inode, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode)
            {
            }
    };

    // Fallocate
    class FallocateAction : public FsAction
    {
        public:
            uint64_t Inode;
            mode_t Mode;
            off_t Offset;
            off_t Length;
            FileInfoContract FileInfo;

            FallocateAction(uint64_t inode, int mode, off_t offset, off_t length, FileInfoContract fileInfo, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Mode(mode),
                    Offset(offset),
                    Length(length),
                    FileInfo(fileInfo)
            {
            }
    };

    // Flock
    class FlockAction : public FsAction
    {
        public:
            uint64_t Inode;
            FileInfoContract FileInfo;
            int Op;

            FlockAction(uint64_t inode, FileInfoContract fileInfo, int op, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    FileInfo(fileInfo),
                    Op(op)
            {
            }
    };

    // Getxattr
    class GetxAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            const char* Name;
            size_t Size;

            GetxAttrAction(uint64_t inode, const char* name, size_t size, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Name(name),
                    Size(size)
            {
            }
    };

    // ListxAttr
    class ListxAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            size_t Size;

            ListxAttrAction(uint64_t inode, size_t size, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Size(size)
            {
            }
    };

    // SetxAttr
    class SetxAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            const char* Name;
            const char* Value;
            size_t Size;
            int Flags;

            SetxAttrAction(uint64_t inode, const char* name, const char* value, size_t size, int flags, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Name(name),
                    Value(value),
                    Size(size),
                    Flags(flags)
            {
            }
    };

    // RemovexAttr
    class RemovexAttrAction : public FsAction
    {
        public:
            uint64_t Inode;
            const char* Name;

            RemovexAttrAction(uint64_t inode, const char* name, int callingProccessId) 
                : FsAction("LookupAction", callingProccessId), 
                    Inode(inode),
                    Name(name)
            {
            }
    };
}

#endif