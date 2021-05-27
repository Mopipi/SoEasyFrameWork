#pragma once
#include<XCode/XCode.h>
#include<Manager/Manager.h>
#include<MysqlClient/MysqlDefine.h>
#include<QueryResult/InvokeResultData.h>
#pragma execution_character_set("utf-8")
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
	public:
		bool CreateMysqlDb();
		bool CreateMysqlTable();
		bool CreateMysqlTable(const char * tab, rapidjson::Value * jsonValue);
		bool CreateNewMysqlTable(const char * tab, rapidjson::Value * jsonValue);

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
		std::string mDataBaseName;	//���ݿ�����
		ThreadPool * mThreadPool;		//�̳߳�
		std::string mSqlTablePath;
		SayNoMysqlSocket * mMysqlSockt;
		std::unordered_map<long long, SayNoMysqlSocket *> mMysqlSocketMap;	//�߳�id�� socket
	private:
		class CoroutineManager * mCoroutineManager;
	};
}