#pragma once

#include<XCode/XCode.h>
#include<Object/Object.h>
#include<Script/LuaInclude.h>
#include<Global/ServerConfig.h>
#include<NetWork/NetWorkAction.h>
#include<Other/DoubleBufferQueue.h>
namespace SoEasy
{

	struct NetMessageBuffer
	{
	public:
		NetMessageBuffer(const std::string & address, const std::string & msg)
			: mAddress(address), mCommandMsg(msg) { }
		NetMessageBuffer(const std::string & address, const char * msg, size_t size)
			: mAddress(address), mCommandMsg(msg, size) { }
	public:
		const std::string mAddress;
		const std::string mCommandMsg;
	};
	class LocalActionProxy;
	typedef std::shared_ptr<NetMessageBuffer> SharedNetPacket;

	class Manager : public Object
	{
	public:
		Manager(const int priority = 10);
		virtual ~Manager() { }
	protected:
		friend Applocation;
		bool BindFunction(std::string name, LocalAction1 action);

		template<typename T1>
		bool BindFunction(std::string name, LocalAction2<T1> action);

		template<typename T1, typename T2>
		bool BindFunction(std::string name, LocalAction3<T1, T2> action);

	public:
		void AddFinishTaskId(long long taskId);	//�������̵߳���
		AsioContext & GetAsioContext() { return this->GetApp()->GetAsioContext(); }
	public:
		inline int GetPriority() { return mPriority; }	//���ȼ�(�������ȼ�ȷ������˳��)
	public:
		virtual void PushClassToLua(lua_State * luaEnv) { }
	private:
		bool BindFunction(const std::string & name, shared_ptr<LocalActionProxy> actionBox);
	protected:
		void ForeachManagers(std::function<bool(Manager *)> action);
	protected:
		virtual bool OnInit() = 0;			//��ʼ��������
		virtual void OnInitComplete() { }				//�ڳ�ʼ�����֮��
		virtual void OnSystemUpdate();					//����ϵͳ�¼�
		virtual void OnFrameUpdate(float t) { }			//�߼�֡
		virtual void OnSecondUpdate() { }				//ÿ�����
		virtual void OnFrameUpdateAfter() { }			//���߼�ִ֡�����֮��
		virtual void OnTaskFinish(long long id) { }		//���̳߳��������֮���֪ͨ
	private:
		const int mPriority;
		DoubleBufferQueue<long long> mFinishTaskQueue;  //�������߳���ɵ�����洢
	};
	
	template<typename T1>
	inline bool Manager::BindFunction(std::string name, LocalAction2<T1> action)
	{
		typedef LocalActionProxy2<T1> ActionProxyType;
		const size_t pos = name.find_first_of(".");
		if (pos == std::string::npos)
		{
			SayNoDebugError("register error : " << name);
			return false;
		}
		return this->BindFunction(name, make_shared<ActionProxyType>(action, name));
	}

	template<typename T1, typename T2>
	inline bool Manager::BindFunction(std::string name, LocalAction3<T1, T2> action)
	{
		const size_t pos = name.find_first_of(".");
		if (pos == std::string::npos)
		{
			SayNoDebugError("register error : " << name);
			return false;
		}
		return this->BindFunction(name, make_shared<LocalActionProxy3<T1, T2>>(action, name));
	}

	inline std::string GetFunctionName(std::string func)
	{
		char buf[] = ".";
		size_t pos = func.find("::");
		return func.replace(pos, sizeof(buf), ".");
	}
#define REGISTER_FUNCTION_0(func) this->BindFunction(GetFunctionName(#func), std::bind(&func, this, args1))
#define REGISTER_FUNCTION_1(func,t1) this->BindFunction<t1>(GetFunctionName(#func), std::bind(&func, this, args1, args2))
#define REGISTER_FUNCTION_2(func,t1, t2) this->BindFunction<t1, t2>(GetFunctionName(#func), std::bind(&func, this, args1, args2, args3))

}