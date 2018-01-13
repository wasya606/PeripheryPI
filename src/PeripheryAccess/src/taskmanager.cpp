#include "taskmanager.h"
#include <iostream>

TaskManager::TaskManager() : isExecutingDelayedTasks(false), threadId(0),
                             taskLock(PTHREAD_MUTEX_INITIALIZER), sleepCondition(PTHREAD_COND_INITIALIZER)
{

}

TaskManager::~TaskManager()
{

}

TaskId TaskManager::addTask(TaskDelegate taskDelegate, void *taskParameters)
{
    pthread_mutex_lock(&taskLock);
    TaskId taskId = pendingTasks.size();
    pendingTasks.push_back(new TaskData(taskId, taskDelegate, taskParameters));
    wakeUpThread();
    return taskId;
}

TaskId TaskManager::addDelayedTask(TaskDelegate taskDelegate, void *taskParameters)
{
    pthread_mutex_lock(&taskLock);
    TaskId taskId = delayedTasks.size();
    delayedTasks.push_back(new TaskData(taskId, taskDelegate, taskParameters));
    pthread_mutex_unlock(&taskLock);
    return taskId;
}

void TaskManager::executeDelayedTasks()
{
    pthread_mutex_lock(&taskLock);
    isExecutingDelayedTasks = true;
    wakeUpThread();
    pthread_mutex_unlock(&taskLock);
}

void TaskManager::wakeUpThread()
{
    if (threadId != 0)
    {
        pthread_mutex_unlock(&taskLock);
        pthread_cond_signal(&sleepCondition);
    }
    else
    {
        createThread();
        pthread_mutex_unlock(&taskLock);
    }
}

bool TaskManager::createThread()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    auto clb = [](void* thisPtr)->void*
    {
        ((TaskManager*)thisPtr)->tasksLoop();
        return nullptr;
    };

    return pthread_create(&threadId, &attr, clb, this) == 0;
}

void TaskManager::tasksLoop()
{
    for(;;)
    {
        pthread_mutex_lock(&taskLock);
        //Sleep thread if no tasks
        while (isNoTasksToExecute())
        {
            std::cout << "Sleep!!!\n";
            pthread_cond_wait(&sleepCondition, &taskLock);
        }

        //Complete pending tasks
        if (!pendingTasks.empty())
        {
            TaskData* currentTask = pendingTasks.front();
            pendingTasks.pop_front();
            if (currentTask->delegate != nullptr)
                currentTask->delegate(currentTask->id, currentTask->parameters);

            delete currentTask;
        }

        //Complete delayed tasks
        if (!delayedTasks.empty() && isExecutingDelayedTasks)
        {
            TaskData* currentTask = delayedTasks.front();
            delayedTasks.pop_front();
            if (currentTask->delegate != nullptr)
                currentTask->delegate(currentTask->id, currentTask->parameters);

            delete currentTask;
        }
        else if (delayedTasks.empty() && isExecutingDelayedTasks)
        {
            isExecutingDelayedTasks = false;
        }
        pthread_mutex_unlock(&taskLock);
    }
}

bool TaskManager::isNoTasksToExecute()
{
    return pendingTasks.empty() && !(!delayedTasks.empty() && isExecutingDelayedTasks);
}
