#pragma once
#include<list>
#include<queue>
#include<thread>
#include<memory>
#include"Manager.h"
#include<condition_variable>
#include<Timer/TimerBase.h>
#define TimerPrecision 20 //����  ����
#define MaxMinute 1		//һȦ��ѯʱ�� ����
namespace SoEasy
{
	class TimerManager : public Manager
	{
	public:
		TimerManager();
		~TimerManager() { }
	public:
		void Stop();
		bool RemoveTimer(long long id);
		bool AddTimer(shared_ptr<TimerBase> timer);
		shared_ptr<TimerBase> GetTimer(long long id);
	public:
		template<typename T, typename ... Args>
		shared_ptr<T> CreateTimer(Args && ...args);
 	protected:
		bool OnInit() { return true; }
		void OnInitComplete() final;
		void OnSystemUpdate() final;					//����ϵͳ�¼�
	private:
		void RefreshTimer();
		bool AddNextTimer(shared_ptr<TimerBase> timer);
		void AddTimerToWheel(shared_ptr<TimerBase> timer);
	private:
		bool mIsStop;
		std::thread * mTimerThread;
		std::mutex mTimerThreadLock;
		std::condition_variable mWheelVariable;		//�Ƿ���ѯ����������		
		DoubleBufferQueue<long long> mFinishTimerQueue;	//���һ�εĶ���
		DoubleBufferQueue<shared_ptr<TimerBase>> mWheelQueue;	//��Ҫ��ѯ�Ķ���
		std::unordered_map<long long, shared_ptr<TimerBase>> mTimerMap;	//����timer���б�
	private:
		int mTickCount;
		int mTimerCount;
		int mMaxTimeCount;
		long long mStartTime;
		std::list<shared_ptr<TimerBase>> mNextWheelTimer;	// ���β���ע�Ķ�ʱ��
		std::queue<shared_ptr<TimerBase>> mTimers[MaxMinute * 60 * (1000 / TimerPrecision)];
	};
	template<typename T, typename ...Args>
	inline shared_ptr<T> TimerManager::CreateTimer(Args && ...args)
	{
		std::shared_ptr<T> timer = std::make_shared<T>(std::forward<Args>(args)...);
		return this->AddTimer(timer) ? timer : nullptr;
		
	}

}