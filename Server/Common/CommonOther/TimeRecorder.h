#pragma once
#include<cstring>
#include<unordered_map>
#include<CommonXCode/XCode.h>
namespace SoEasy
{
	struct CostTimeInfo
	{
	public:
		CostTimeInfo() { this->Clear(); }
	public:
		void Clear() { memset(this, 0, sizeof(*this)); }
	public:
		int mTimeoutCount;	//��ʱ����
		long long mCallCount;	//���ô���
		double mSumLatency;	//���ӳ�
		double mMaxLatency;	//����ӳ�
		double mMinLatency;	//��С�ӳ�
		double mAverageLatency;	//ƽ���ӳ�
	};


	class TimeRecorder
	{
	public:
		TimeRecorder();
	public:
		CostTimeInfo * GetLatencyInfo();
		CostTimeInfo * GetLatencyInfo(std::string & name);
		long long GetLastClearTime() { return this->mLastClearTime; }
	public:
		void Clear();
		bool SaveDataToFile(const std::string path);
		void AddCostTimeInfo(const std::string & func, long long lastTime);
		void AddCostTimeInfo(const std::string & func, XCode code, long long lastTime);
	private:
		long long mLastClearTime;//(����)
		std::unordered_map<std::string, CostTimeInfo> mCallFuncInfoMap;
	};
}