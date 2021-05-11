#pragma once
#include<XCode/XCode.h>
#include<Manager/Manager.h>
#include<MysqlClient/MysqlDefine.h>
namespace DataBase
{
	class MysqlTaskAction;
	class MysqlManager : public SoEasy::Manager
	{
	public:
		MysqlManager();
		~MysqlManager() { }
	public:
		SayNoMysqlSocket * GetMysqlSocket(long long threadId);
	public:
		XCode QueryData(const std::string db, const std::string & sql);
		XCode QueryData(const std::string db, const std::string & sql, std::shared_ptr<MysqlQueryData> & queryData);
	protected:
		bool OnInit() override;
		void OnTaskFinish(long long id) final;
	private:
		bool StartConnectMysql();
	private:
		XCode QueryTable(long long id, shared_ptr<StringArray> requestData);
	private:
		std::string mMysqlIp;		//ip��ַ
		unsigned short mMysqlPort;	//�˿ں�
		std::string mDataBaseUser;	//�û���
		std::string mDataBasePasswd; //����
		ThreadPool * mThreadPool;		//�̳߳�
		std::unordered_map<long long, SayNoMysqlSocket *> mMysqlSocketMap;	//�߳�id�� socket
	private:
		class CoroutineManager * mCoroutineManager;
		std::unordered_map<long long, shared_ptr<MysqlTaskAction>> mTaskActionMap;
	};
}