#pragma once
#include"MysqlDefine.h"
#include<Thread/ThreadTaskAction.h>
namespace SoEasy
{
	class QuertJsonWritre;
	class CoroutineManager;
	class MysqlTaskBase : public ThreadTaskAction
	{
	public:
		MysqlTaskBase(MysqlManager * mgr, long long id, const std::string & db, const std::string & sql);
		~MysqlTaskBase() { }
	protected:
		void InvokeInThreadPool(long long threadId) final;	//�������̲߳�ѯ
		virtual void OnQueryFinish(QuertJsonWritre & jsonWriter); //��ѯ���֮�����
	public:
		const std::string & GetSqlCommand() { return this->mSqlCommand; }
		const std::string & GetDataBaseName() { return this->mDataBaseName; }
	public:
		XCode GetErrorCode() { return this->mErrorCode; }
		const std::string & GetErrorStr() { return this->mErrorString; }
	private:
		std::string mSqlCommand;
		std::string mDataBaseName;
		MysqlManager * mMysqlManager;
	private:
		XCode mErrorCode;
		std::string mErrorString;
	};
}