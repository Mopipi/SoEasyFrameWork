#pragma once
#include<Manager/Manager.h>
#include<QueryResult/InvokeResultData.h>
#include<RedisClient/RedisTaskAction.h>
using namespace SoEasy;
namespace SoEasy
{
	class RedisManager : public Manager
	{
	public:
		RedisManager();
		~RedisManager() { }
		RedisSocket * GetRedisSocket(long long id);
	protected:
		bool OnInit() final;			//��ʼ��������
		void OnInitComplete() override;				//��ʼ�����֮��
		void OnTaskFinish(long long id) final;		//���̳߳��������֮���֪ͨ
	public:
		shared_ptr<InvokeResultData> InvokeCommand(const char * format, ...);
	private:
		std::string mRedisIp;		//redis ip��ַ
		unsigned short mRedisPort;	//�˿ں�
		ThreadPool * mThreadPool;	//�̳߳�
		class CoroutineManager * mCoroutineScheduler;
		std::unordered_map<long long, redisContext *> mRedisContextMap;
		std::unordered_map<long long, shared_ptr<RedisTaskAction>> mTaskActionMap;
	};
}