#pragma once
#include<string>
namespace SoEasy
{
	struct NetworkLatencyInfo
	{
	public:
		NetworkLatencyInfo() { memset(this, 0, sizeof(*this)); }
	public:
		int mTimeoutCount;	//��ʱ����
		long long mMaxLatency;	//����ӳ�
		long long mMinLatency;	//��С�ӳ�
	};
}