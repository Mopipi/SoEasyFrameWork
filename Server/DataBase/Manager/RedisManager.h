#pragma once
#include<Manager/Manager.h>
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
		void OnInitComplete() override;				//ÿ�����

	private:
		std::string mRedisIp;		//redis ip��ַ
		unsigned short mRedisPort;	//�˿ں�
		ThreadPool * mThreadPool;	//�̳߳�
		class CoroutineManager * mCoroutineScheduler;
		std::unordered_map<long long, redisContext *> mRedisContextMap;
	};
}