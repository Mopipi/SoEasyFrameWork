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
		XMysqlCode QueryData(const std::string db, const std::string & sql);
		XMysqlCode QueryData(const std::string db, const std::string & sql, std::shared_ptr<MysqlQueryData> & queryData);
	protected:
		bool OnInit() override;
		void OnTaskFinish(long long id) final;
	private:
		bool StartConnectMysql();
	private:
		XCode QueryTable(shared_ptr<TcpClientSession> session, long long id, const StringArray & requestData);
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