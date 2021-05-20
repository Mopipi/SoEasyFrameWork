#pragma once

#include<XCode/XCode.h>
#include<Object/Object.h>
#include<Script/LuaInclude.h>
#include<Global/ServerConfig.h>
#include<Other/DoubleBufferQueue.h>
#include<NetWork/TcpClientSession.h>
#include<Protocol/Common.pb.h>
using namespace PB;
namespace SoEasy
{
	typedef shared_ptr<NetWorkPacket> SharedPacket;
	struct NetMessageBuffer
	{
	public:
		NetMessageBuffer(const std::string & address, const SharedPacket packet);
	public:
		const std::string mAddress;
		const SharedPacket mMessagePacket;
	};
	
	typedef shared_ptr<NetMessageBuffer> SharedNetPacket;

	class ThreadTaskAction;
	class LocalActionProxy;
	
	class Manager : public Object
	{
	public:
		Manager(const int priority = 10);
		virtual ~Manager() { }
	protected:
		friend Applocation;
	public:
		void AddFinishTask(long long id);	//��Ҫ�ֶ�����
	public:
		bool StartTaskAction(shared_ptr<ThreadTaskAction> taskAction);
		AsioContext & GetAsioContext() { return this->GetApp()->GetAsioContext(); }
	public:
		inline int GetPriority() { return mPriority; }	//���ȼ�(�������ȼ�ȷ������˳��)
		virtual void PushClassToLua(lua_State * luaEnv) { }		//������������lua
	protected:
		void ForeachManagers(std::function<bool(Manager *)> action);
	protected:
		virtual bool OnInit() = 0;						//��ʼ��������
		virtual void OnHitfix() { }						//�ȸ�����֮�����
		virtual void OnInitComplete() { }				//�ڳ�ʼ�����֮�� �ķ�������Э���е���
		virtual void OnSystemUpdate();					//����ϵͳ�¼�
		virtual void OnFrameUpdate(float t) { }			//�߼�֡
		virtual void OnSecondUpdate() { }				//ÿ�����
		virtual void OnFrameUpdateAfter() { }			//���߼�ִ֡�����֮��
		virtual void OnTaskFinish(shared_ptr<ThreadTaskAction> taskAction) { }		//���̳߳��������֮���֪ͨ	
	private:
		const int mPriority;
		DoubleBufferQueue<long long> mFinishTaskQueue;  //�������߳���ɵ�����洢
		std::unordered_map<long long, shared_ptr<ThreadTaskAction>> mThreadTaskMap;
	};
	
	

	inline std::string GetFunctionName(std::string func)
	{
		return func.substr(func.find("::") + 2);
	}

}