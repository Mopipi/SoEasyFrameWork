#pragma once
#include<thread>
#include"TaskThread.h"
#include"ThreadTaskAction.h"
namespace SoEasy
{
	class ThreadPool
	{
	public:	
		static void InitPool(unsigned int count = 0);	//�����̳߳�����
		static TaskThread * GetTaskThread(long long id);
		static void GetAllTaskThread(std::vector<TaskThread *> & threads);
		static bool StartTaskAction(std::shared_ptr<ThreadTaskAction> taskAction);
	public:
		static unsigned int GetThreadCount() { return mThreadCount; }
	private:
		static unsigned int mThreadCount;
		static std::vector<TaskThread *> mTaskThreadList;
	};
}