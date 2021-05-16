#pragma once
#include<XCode/XCode.h>
#include<Manager/Manager.h>
#include<MysqlClient/MysqlDefine.h>
#include<QueryResult/InvokeResultData.h>
namespace SoEasy
{
	class MysqlTaskAction;
	class MysqlManager : public Manager
	{
	public:
		MysqlManager();
		~MysqlManager() { }
	public:
		SayNoMysqlSocket * GetMysqlSocket(long long threadId);
	public:
		shared_ptr<InvokeResultData> InvokeCommand(const std::string db, const std::string & sql);
	protected:
		bool OnInit() final;
		void OnInitComplete() final;
		void PushClassToLua(lua_State * luaEnv) final;		//������������lua

	private:
		bool StartConnectMysql();
	private:
		std::string mMysqlIp;		//ip��ַ
		unsigned short mMysqlPort;	//�˿ں�
		std::string mDataBaseUser;	//�û���
		std::string mDataBasePasswd; //����
		ThreadPool * mThreadPool;		//�̳߳�
		std::unordered_map<long long, SayNoMysqlSocket *> mMysqlSocketMap;	//�߳�id�� socket
	private:
		class CoroutineManager * mCoroutineManager;
	};
}