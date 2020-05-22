#include <iostream>
#include "RwMonitor.cpp"

using namespace RwMonitor;

class TestAction1 : public FsAction
{
        public:
            string Path;

        TestAction1(string path, int callingProccessId) 
            : FsAction("Action1", callingProccessId), Path(path) { }
};

class TestAction2 : public FsAction
{
        public:
            string Path;

        TestAction2(string path, int callingProccessId) 
            : FsAction("Action2", callingProccessId), Path(path) { }
};

class TestAction3 : public FsAction
{
        public:
            string Path;

        TestAction3(string path, int callingProccessId) 
            : FsAction("Action3", callingProccessId), Path(path) { }
};

class TestAction4 : public FsAction
{
        public:
            string Path;

        TestAction4(string path, int callingProccessId) 
            : FsAction("Action4", callingProccessId), Path(path) { }
};

class TestAction5 : public FsAction
{
        public:
            string Path;

        TestAction5(string path, int callingProccessId) 
            : FsAction("UnknownAction", callingProccessId), Path(path) { }
};

class TestHeuristic1 : public HeuristicBase
{
    public:
        bool IsValidAction(FsAction action) override
        {
            return false;
        }
};

class TestHeuristic2 : public HeuristicBase
{
    public:
        // This heuristic does not accept "Action1" and "Action3"
        bool IsValidAction(FsAction action) override
        {
            string actionName = action.ActionName;
            if (actionName == "Action1" || actionName == "Action3")
            {
                return false;
            }

            return true;
        }
};

class TestHeuristic3 : public HeuristicBase
{
    public:
        // This heuristic does not accept "Action2" and "Action4"
        bool IsValidAction(FsAction action) override
        {
            string actionName = action.ActionName;
            if (actionName == "Action2" || actionName == "Action4")
            {
                return false;
            }

            return true;
        }
};

class TestHeuristic4 : public HeuristicBase
{
    public:
        // This heuristic does not accept "Action2" and "Action3" and "Action4"
        bool IsValidAction(FsAction action) override
        {
            string actionName = action.ActionName;
            if (actionName == "Action2" || actionName == "Action3" || actionName == "Action4")
            {
                return false;
            }

            return true;
        }
};

class TestHeuristic5 : public HeuristicBase
{
    public:
        // This heuristic does not accept "Action4"
        bool IsValidAction(FsAction action) override
        {
            string actionName = action.ActionName;
            if (actionName == "Action4")
            {
                return false;
            }

            return true;
        }
};

class TestHeuristic6 : public HeuristicBase
{
    public:
        // This heuristic does not accept "Action3"
        bool IsValidAction(FsAction action) override
        {
            string actionName = action.ActionName;
            if (actionName == "Action3")
            {
                return false;
            }

            return true;
        }
};

class TestHeuristic7 : public HeuristicBase
{
    public:
        // This heuristic accepts all actions
        bool IsValidAction(FsAction action) override
        {
            return true;
        }
};

void TestActionsInternal(RwThreatDetector* monitor, list<FsAction>* badActions, list<FsAction>* legalActions)
{
    cout << "\t" << "Testing heuristic with bad actions" << endl;
    if (badActions != nullptr)
    {
        for (std::list<FsAction>::iterator it = badActions->begin(); it != badActions->end(); ++it)
        {
            if (monitor->CanPerform(*it) == true)
            {
                throw "Failed at test 2, shouldn't be able to perform action with TestHeuristic2";
            }
        }
    }

    cout << "\t" << "Testing heuristic with legal actions" << endl;
    if (legalActions != nullptr)
    {
        for (std::list<FsAction>::iterator it = legalActions->begin(); it != legalActions->end(); ++it)
        {
            if (monitor->CanPerform(*it) == false)
            {
                throw "Failed at test 2, should be able to perform action with TestHeuristic2";
            }
        }
    }
}

void TestCase1()
{
    cout << "__Test case 1__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic1, this heuristic should return invalid for every given FsAction" << endl;
    monitor->AddHeuristic(new TestHeuristic1());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction1("SomePathForAction1", 0));
    badActions->push_back(TestAction2("SomePathForAction2", 0));
    badActions ->push_back(TestAction3("SomePathForAction3", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));
    badActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, nullptr);
}

void TestCase2()
{
    cout << "__Test case 2__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic2" << endl;
    monitor->AddHeuristic(new TestHeuristic2());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction1("SomePathForAction1", 0));
    badActions->push_back(TestAction3("SomePathForAction3", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction2("SomePathForAction2", 0));
    legalActions->push_back(TestAction4("SomePathForAction4", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCase3()
{
    cout << "__Test case 3__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic3" << endl;
    monitor->AddHeuristic(new TestHeuristic3());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction2("SomePathForAction2", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction3("SomePathForAction3", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCase4()
{
    cout << "__Test case 4__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic4" << endl;
    monitor->AddHeuristic(new TestHeuristic4());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction2("SomePathForAction2", 0));
    badActions->push_back(TestAction3("SomePathForAction3", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCase5()
{
    cout << "__Test case 5__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic5" << endl;
    monitor->AddHeuristic(new TestHeuristic5());

    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction2("SomePathForAction2", 0));
    legalActions->push_back(TestAction3("SomePathForAction3", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCase6()
{
    cout << "__Test case 6__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic7" << endl;
    monitor->AddHeuristic(new TestHeuristic7());

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction2("SomePathForAction2", 0));
    legalActions->push_back(TestAction3("SomePathForAction3", 0));
    legalActions->push_back(TestAction4("SomePathForAction4", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, nullptr, legalActions);
}

void TestCaseMix1()
{
    cout << "__Test case Mix1__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic5 and heuristic6. With this combination, action3 and action4 are illegal" << endl;
    monitor->AddHeuristic(new TestHeuristic5());
    monitor->AddHeuristic(new TestHeuristic6());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction3("SomePathForAction3", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction2("SomePathForAction2", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCaseMix2()
{
    cout << "__Test case Mix2__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with test heuristic3 and heuristic6. With this combination, action2/3/4 are illegal" << endl;
    monitor->AddHeuristic(new TestHeuristic3());
    monitor->AddHeuristic(new TestHeuristic6());

    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction3("SomePathForAction3", 0));
    badActions->push_back(TestAction2("SomePathForAction2", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestCaseMix3()
{
    cout << "__Test case Mix3__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Initializing monitor with all heuristics but heuristic1. With this combination, all known actions are illegal" << endl;
    monitor->AddHeuristic(new TestHeuristic2());
    monitor->AddHeuristic(new TestHeuristic3());
    monitor->AddHeuristic(new TestHeuristic4());
    monitor->AddHeuristic(new TestHeuristic5());
    monitor->AddHeuristic(new TestHeuristic6());
    
    std::list<FsAction>* badActions = new list<FsAction>();
    badActions->push_back(TestAction1("SomePathForAction1", 0));
    badActions->push_back(TestAction3("SomePathForAction3", 0));
    badActions->push_back(TestAction2("SomePathForAction2", 0));
    badActions->push_back(TestAction4("SomePathForAction4", 0));

    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, badActions, legalActions);
}

void TestEdgeCase1()
{
    cout << "__Test edge case 1__" << endl;
    
    cout << "\t" << "Creating monitor" << endl;
    RwThreatDetector* monitor = new RwThreatDetector();

    cout << "\t" << "Monitor has no heuristics" << endl;
    
    std::list<FsAction>* legalActions = new list<FsAction>();
    legalActions->push_back(TestAction1("SomePathForAction1", 0));
    legalActions->push_back(TestAction3("SomePathForAction3", 0));
    legalActions->push_back(TestAction2("SomePathForAction2", 0));
    legalActions->push_back(TestAction4("SomePathForAction4", 0));
    legalActions->push_back(TestAction5("SomePathForAction5", 0));

    TestActionsInternal(monitor, nullptr, legalActions);
}

int main (int argc, char *argv[])
{
    cout << "Starting monitor unit tests" << endl << endl;
    
    try
    {        
        TestCase1();
        cout << "Test case 1 passed" << endl << endl;

        TestCase2();
        cout << "Test case 2 passed" << endl << endl;

        TestCase3();
        cout << "Test case 3 passed" << endl << endl;

        TestCase4();
        cout << "Test case 4 passed" << endl << endl;
        
        TestCase5();
        cout << "Test case 5 passed" << endl << endl;

        TestCase6();
        cout << "Test case 6 passed" << endl << endl;

        TestCaseMix1();
        cout << "Test case mix 1 passed" << endl << endl;

        TestCaseMix2();
        cout << "Test case mix 2 passed" << endl << endl;

        TestCaseMix3();
        cout << "Test case mix 3 passed" << endl << endl;

        TestEdgeCase1();
        cout << "Test edge case 1 passed" << endl << endl;
    }
    catch(char const* ex)
    {
        cout << "Monitor tests failed: " << ex << endl;
    }

    return 0;
}