#include "Framework.h"

void Observer::AddEvent(string key, Event event)
{
    totalEvent[key].push_back(event);
}

void Observer::AddIntEvent(string key, IntParamEvent event)
{
    totalIntEvent[key].push_back(event);
}

void Observer::AddObjectEvent(string key, ObjectParamEvent event)
{
    totalObjectEvent[key].push_back(event);
}

void Observer::ExcuteEvent(string key)
{
    for (Event event : totalEvent[key])
        event();
}

void Observer::ExcuteIntEvent(string key, int param)
{
    for (IntParamEvent event : totalIntEvent[key])
        event(param);
}

void Observer::ExcuteObjectEvent(string key, void* param)
{
    for (ObjectParamEvent event : totalObjectEvent[key])
        event(param);
}
