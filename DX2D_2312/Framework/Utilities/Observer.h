#pragma once

class Observer : public Singleton<Observer>
{
private:
    friend class Singleton;

    Observer() = default;
    ~Observer() = default;

public:
    void AddEvent(string key, Event event);
    void AddIntEvent(string key, IntParamEvent event);
    void AddObjectEvent(string key, ObjectParamEvent event);

    void ExcuteEvent(string key);
    void ExcuteIntEvent(string key, int param);
    void ExcuteObjectEvent(string key, void* param);

private:
    unordered_map<string, vector<Event>> totalEvent;
    unordered_map<string, vector<IntParamEvent>> totalIntEvent;
    unordered_map<string, vector<ObjectParamEvent>> totalObjectEvent;
};