#include <iostream>
struct ConstructorCounter
{
    ConstructorCounter()
    {
        ++defaultCounter;
    }
    ConstructorCounter(const ConstructorCounter&)
    {
        ++copyCounter;
    }
    ConstructorCounter & operator= (const ConstructorCounter&)
    {
        ++assignmentCounter;
        return *this;
    }
    #if __cplusplus >= 201103L
    ConstructorCounter(ConstructorCounter &&)
    {
        ++rvaluerefCounter;
    }
    ConstructorCounter& operator= (ConstructorCounter&&)
    {
        ++assignmentCounter;
        return *this;
    }
    #endif    
     
    ~ConstructorCounter()
    {
        ++destructCounter;
    }
    static void printStats()
    {
        std::cerr << "Default constructors         \t" << defaultCounter   << std::endl
             << "Copy constructors            \t" << copyCounter      << std::endl
            #if __cplusplus >= 201103L
                << "Rvalue reference constructors\t" << rvaluerefCounter << std::endl
            #endif
            << "Assignments                   \t" << assignmentCounter << std::endl;
    }
    static void checkIfAllDestroyed()
    {
        printStats();
        assert(defaultCounter + copyCounter + rvaluerefCounter + 
                assignmentCounter - destructCounter == 0 
                && "Not every Object has been destroyed!");
    }
    typedef long long counterType;
    static counterType defaultCounter, copyCounter, 
            rvaluerefCounter, destructCounter, assignmentCounter;
    
};

ConstructorCounter::counterType ConstructorCounter::defaultCounter = 0;
ConstructorCounter::counterType ConstructorCounter::copyCounter = 0;
ConstructorCounter::counterType ConstructorCounter::rvaluerefCounter = 0;
ConstructorCounter::counterType ConstructorCounter::destructCounter = 0;
ConstructorCounter::counterType ConstructorCounter::assignmentCounter = 0;

namespace 
{
#include <stdlib.h>

struct ConstructorCounterHolder
{
    ConstructorCounterHolder()
    {
        atexit(ConstructorCounter::checkIfAllDestroyed);
    }
};

ConstructorCounterHolder holder;

}
