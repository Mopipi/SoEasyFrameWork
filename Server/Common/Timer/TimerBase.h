#pragma once
#include<functional>
#include<Util/TimeHelper.h>
#include<Util/NumberHelper.h>
namespace SoEasy
{
	class TimerBase
	{
	public:
		TimerBase(long long ms);
		virtual ~TimerBase() { }
	public:
		friend class TimerManager;
		virtual bool Invoke() = 0; //����֮��ִ�еĲ���(����ֵ��ʾ�Ƿ��Ƴ�, ���Ƴ�����ӵ��б�����ȴ��´�)
	public:
		const int GetTickCount() { return mTickCount; }
		const long long GetTimerId() { return mTimerId; }
	protected:
		int mTickCount;	//���ٴ�֮��ִ��
		long long mTimerId;
		long long mDelayTime;
	};
}