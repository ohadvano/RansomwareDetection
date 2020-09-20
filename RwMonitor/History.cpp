#ifndef _HHISTORY
#define _HHISTORY

#include <string>
#include <ctime>
#include <sys/stat.h>
#include <list>

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

            void AddNewAction(T newAction)
            {
                _actionRecords->push_front(ActionRecord<T>(newAction));
            }

            int LookBack(int lookBackTime)
            {
                int count = 0;
                time_t time_now = time(0);

                for (std::list<ActionRecord<T>>::iterator it = _actionRecords->begin(); it != _actionRecords->end(); ++it)
                {
                    ActionRecord<T> record = *it;
                    time_t recordTime = record._actionTime;
                    if (time_now - lookBackTime < recordTime)
                    {
                        count += 1;
                    }
                }

                return count;
            }
            
            ~ActionHistory()
            {
                delete _actionRecords;
            }
            
        private:
            std::list<ActionRecord<T>>* _actionRecords;
    };
}

#endif