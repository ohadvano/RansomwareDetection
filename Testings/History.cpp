#ifndef _HHISTORY
#define _HHISTORY

#include <string>
#include <ctime>
#include <sys/stat.h>

using namespace std;

namespace ActionsHistory
{
    template <typename R>
    class ActionRecord
    {
        public:
            ActionRecord()
            {
                _action = nullptr;
                _actionTime = time(0);
            }

            ActionRecord(R action)
            {
                _action = action;
                _actionTime = time(0);
            }

        private:
            R _action;
            time_t _actionTime;
    };
}

#endif