#pragma once
#include<functional>
#include<Util/TimeHelper.h>
#include<Util/NumberHelper.h>
namespace SoEasy
{
	class TimerBase
	{
	public:
		TimerBase(long long ms) { mNextInvokeTime = TimeHelper::GetMilTimestamp() + ms; }
		virtual ~TimerBase() { }
	public:
		virtual bool Invoke() = 0; //����֮��ִ�еĲ���(����ֵ��ʾ�Ƿ��Ƴ�, ���Ƴ�����ӵ��б�����ȴ��´�)
		virtual bool IsTrigger(long long nowTime) { return nowTime >= this->mNextInvokeTime; }
	public:
		const long long GetTimerId() { return mTimerId; }
		const long long GetNextInvokeTime() { return mNextInvokeTime; }
		void MoveNextInvokeTime(long long ms) { this->mNextInvokeTime += ms; }
	private:
		long long mTimerId;
		long long mNextInvokeTime;
	};
}