#pragma once
#include<list>
#include<thread>
#include<memory>
#include"Manager.h"
#include<condition_variable>
#include<CommonTimer/TimerBase.h>
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
		void OnTaskFinish(long long id) final;
	private:
		void RefreshTimer();
	private:
		bool mIsStop;
		long long mWheelInterval;		//��ѯ���
		std::thread * mTimerThread;
		std::mutex mTimerThreadLock;
		std::condition_variable mWheelVariable;		//�Ƿ���ѯ����������
		std::queue<shared_ptr<TimerBase>> mWheelQueue;	//������ѯ����
		std::queue<shared_ptr<TimerBase>> mNextWheelQueue;	//�´���ѯ����
		std::unordered_map<long long, shared_ptr<TimerBase>> mTimerMap;	//����timer���б�
	};
	template<typename T, typename ...Args>
	inline shared_ptr<T> TimerManager::CreateTimer(Args && ...args)
	{
		std::shared_ptr<T> timer = std::make_shared<T>(std::forward<Args>(args)...);
		return this->AddTimer(timer) ? timer : nullptr;
		
	}

}