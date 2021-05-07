#pragma once
#include<Manager/Manager.h>
#include<RedisClient/RedisTaskAction.h>
using namespace SoEasy;
namespace DataBase
{
	class RedisManager : public Manager
	{
	public:
		RedisManager();
		~RedisManager() { }
		RedisSocket * GetRedisSocket(long long id);
	protected:
		bool OnInit() final;			//��ʼ��������
		void OnSecondUpdate() override;				//ÿ�����
	private:
		std::string mRedisIp;		//redis ip��ַ
		unsigned short mRedisPort;	//�˿ں�
		ThreadPool * mThreadPool;	//�̳߳�
		class CoroutineManager * mCoroutineScheduler;
		std::unordered_map<long long, redisContext *> mRedisContextMap;
	};
}