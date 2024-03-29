// Task.cpp : 定义控制台应用程序的入口点。
//


// 最好实现一个智能指针的task
#include "stdafx.h"

#include "Task.h"

CTask::~CTask()
{
}

CTask::CTask()
{
    status = TASK_PROGRESS_NONE;
    m_ID = 0;

}

void CTask::setTaskData(shared_ptr<CTaskData> tdata)
{
    this->status = TASK_PROGRESS_ACCEPT;
    this->data = tdata;
    this->status = TASK_PROGRESS_PROCESSING;

}

//查询任务是否完成不改变任务状态 
bool CTask::hasFinished()
{
    bool ret = false;
    if (TASK_PROGRESS_PROCESSING != this->status && 
        TASK_PROGRESS_FINISHED != this->status){
        //任务状态不对 
        return ret;
    }

    if (TASK_PROGRESS_FINISHED == this->status){
        ret = true;
        return ret;
    }

    if (nullptr == this->data.get())
    {
        // 任务出错
        return ret;
    }

    ret = this->data.get()->hasFinished();

    return ret;

}

void CTask::addProgress(int32_t count)
{
    if ( TASK_PROGRESS_PROCESSING != this->status ){
        //任务状态不对
        return; 
    }
    auto tdata = data.get();
    if ( nullptr == tdata ) {
        //处理错误, 当前任务数据没有 
    }
    tdata->addProgress( count );

    if ( this->hasFinished() ){
        this->status = TASK_PROGRESS_FINISHED;
    }
}

int32_t CTask::getTaskID()
{
    return m_ID;

}

