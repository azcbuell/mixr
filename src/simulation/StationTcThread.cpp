
#include "mixr/simulation/StationTcThread.hpp"

#include "mixr/simulation/Station.hpp"

namespace mixr {
namespace simulation {

IMPLEMENT_SUBCLASS(TcThread, "TcThread")
EMPTY_SLOTTABLE(TcThread)
EMPTY_COPYDATA(TcThread)
EMPTY_DELETEDATA(TcThread)

TcThread::TcThread(base::Component* const parent, const double priority, const double rate): base::PeriodicTask(parent, priority, rate)
{
   STANDARD_CONSTRUCTOR()
}

unsigned long TcThread::userFunc(const double dt)
{
   Station* station = static_cast<Station*>(getParent());
   station->processTimeCriticalTasks(dt);
   return 0;
}

}
}
