#pragma once

#include<CommonXCode/XCode.h>
#include<CommonScript/LuaInclude.h>
#include<CommonObject/Object.h>
#include<CommonGlobal/ServerConfig.h>
#include<CommonNetWork/NetWorkAction.h>
#include<CommonOther/DoubleBufferQueue.h>
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
	typedef std::shared_ptr<NetMessageBuffer> SharedNetPacket;

	class Manager : public Object
	{
	public:
		Manager(const int priority = 10);
		virtual ~Manager() { }
	protected:
		friend Applocation;
		bool BindFunction(std::string name, NetWorkAction1 action);

		template<typename T1>
		bool BindFunction(std::string name, NetWorkAction2<T1> action);

		template<typename T1, typename T2>
		bool BindFunction(std::string name, NetWorkAction3<T1, T2> action);

		template<typename T1>
		bool BindFunction(std::string name, NetWorkAction4<T1> action);
	public:
		void AddFinishTaskId(long long taskId);	//���̳߳ص���
		AsioContext & GetAsioContext() { return this->GetApp()->GetAsioContext(); }
	public:
		inline int GetPriority() { return mPriority; }	//���ȼ�(�������ȼ�ȷ������˳��)
	public:
		virtual void PushClassToLua(lua_State * luaEnv) { }
		virtual void OnLoadLuaComplete(lua_State * luaEnv) { }
	private:
		bool BindFunction(const std::string & name, class NetWorkActionBox * actionBox);
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
	inline bool Manager::BindFunction(std::string name, NetWorkAction2<T1> action)
	{
		const size_t pos = name.find_first_of(".");
		if (pos == std::string::npos)
		{
			SayNoDebugError("register error : " << name);
			return false;
		}
		NetWorkActionBox * actionBox = new NetWorkActionBox2<T1>(action, name);
		return this->BindFunction(name, actionBox);
	}

	template<typename T1, typename T2>
	inline bool Manager::BindFunction(std::string name, NetWorkAction3<T1, T2> action)
	{
		const size_t pos = name.find_first_of(".");
		if (pos == std::string::npos)
		{
			SayNoDebugError("register error : " << name);
			return false;
		}
		NetWorkActionBox * actionBox = new NetWorkActionBox3<T1, T2>(action, name);
		return this->BindFunction(name, actionBox);
	}

	template<typename T1>
	inline bool Manager::BindFunction(std::string name, NetWorkAction4<T1> action)
	{
		const size_t pos = name.find_first_of(".");
		if (pos == std::string::npos)
		{
			SayNoDebugError("register error : " << name);
			return false;
		}
		NetWorkActionBox * actionBox = new NetWorkActionBox4<T1>(action, name);
		return this->BindFunction(name, actionBox);
	}
	inline std::string GetFunctionName(std::string func)
	{
		char buf[] = ".";
		size_t pos = func.find("::");
		return func.replace(pos, sizeof(buf), ".");
	}
#define REGISTER_FUNCTION_0(func) this->BindFunction(GetFunctionName(#func), std::bind(&func, this, args1, args2))
#define REGISTER_FUNCTION_1(func,t1) this->BindFunction<t1>(GetFunctionName(#func), std::bind(&func, this, args1, args2, args3))
#define REGISTER_FUNCTION_2(func,t1, t2) this->BindFunction<t1, t2>(GetFunctionName(#func), std::bind(&func, this, args1, args2, args3, args4))

}