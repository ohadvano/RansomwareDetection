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

    template <typename T>
    class ActionHistory
    {
        public:
            ActionHistory()
            {
                _actionRecords = new list<ActionRecord<T>>();
            }

            void AddNewAction<T>(T newAction)
            {
                _actionRecords->push_front(ActionRecord(newAction));
            }

            ~ActionsHistory()
            {
                delete _actionRecords;
            }
            
        private:
            std::list<ActionRecord<T>>* _actionRecords;
    };
}

#endif