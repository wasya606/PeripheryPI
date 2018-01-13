#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <pthread.h>
#include "peripherial_types.h"
#include <list>
#include <vector>

using namespace PeripheralTypes;

namespace TaskManagerErrors {
enum Errors
{
    NO_ERRORS = 0x0,
    CANNOT_CREATE_PTHREAD = 0xFFFE
};
}

class TaskManager
{
public:
    static const constexpr uint32_t INVALID_TASK_ID = 0xFFFFFFFF;

public:
    TaskManager();
    ~TaskManager();

    TaskId addTask(TaskDelegate taskDelegate, void* taskParameters = nullptr);
    TaskId addDelayedTask(TaskDelegate taskDelegate, void* taskParameters = nullptr);
    void executeDelayedTasks();

private:
    struct TaskData
    {
        TaskData(const TaskId id, TaskDelegate delegate, void* parameters = nullptr) : id(id), delegate(delegate), parameters(parameters) {}
        TaskId id = -1;
        TaskDelegate delegate = nullptr;
        void* parameters = nullptr;
    };

    using TaskList = std::list<TaskData*>;

private:
    bool createThread();
    void tasksLoop();
    bool isNoTasksToExecute();
    void wakeUpThread();


private:
    bool isExecutingDelayedTasks;

    pthread_t threadId;
    pthread_mutex_t taskLock;
    pthread_cond_t sleepCondition;

    TaskList pendingTasks;
    TaskList delayedTasks;
};

#endif // TASKMANAGER_H
