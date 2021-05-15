#pragma once
#include"RedisDefine.h"
#include<Thread/ThreadTaskAction.h>
#include<QueryResult/InvokeResultData.h>
namespace SoEasy
{
	class CoroutineManager;
	class RedisTaskAction : public ThreadTaskAction
	{
	public:
		RedisTaskAction(RedisManager * mgr, long long taskId, CoroutineManager * corMgr);
	public:
		void InitCommand(const char *format, va_list command);
		
		long long GetCoroutineId() { return mCoreoutineId; }
	public:
		void OnTaskFinish() final;  //ִ�����֮�������̵߳���
		void InvokeInThreadPool(long long threadId) final;	//���̳߳�ִ�е�����
	public:
		std::shared_ptr<InvokeResultData> GetInvokeData();
	private:
		va_list mCommand;
		std::string mFormat;
		long long mCoreoutineId;
		RedisManager * mRedisManager;
		CoroutineManager * mCoroutineManager;
	private:
		XCode mErrorCode;
		std::string mErrorString;
		std::shared_ptr<rapidjson::Document> mDocument;
	};
}