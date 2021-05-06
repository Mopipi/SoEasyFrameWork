#pragma once
#include"NetLuaRetAction.h"
#include<CommonXCode/XCode.h>
#include<CommonUtil/NumberBuilder.h>
#include<CommonProtocol/Common.pb.h>
#include<CommonNetWork/TcpClientSession.h>

using namespace PB;
namespace SoEasy
{

	using NetWorkRetAction1 = std::function<void(shared_ptr<TcpClientSession>,XCode)>;

	template<typename T>
	using NetWorkRetAction2 = std::function<void(shared_ptr<TcpClientSession>, XCode, const T &)>;

	class NetWorkRetActionBox
	{
	public:
		NetWorkRetActionBox(std::string & name);
		virtual ~NetWorkRetActionBox() { }
	public:
		long long GetCreateTime() { return this->mCreateTime; }
		std::string & GetFunctionName() { return this->mFunctionName; }
	public:
		virtual void Invoke(shared_ptr<TcpClientSession>, const NetWorkPacket & backData) = 0;
	private:
		long long mActionKey;
		long long mCreateTime;
		std::string mFunctionName;
	protected:
		
	};

}

namespace SoEasy
{
	class NetWorkRetActionBox1 : public NetWorkRetActionBox
	{
	public:
		NetWorkRetActionBox1(NetWorkRetAction1 action, std::string & name)
			: NetWorkRetActionBox(name), mBindAction(action),mBindLuaAction(nullptr) {}

		NetWorkRetActionBox1(NetLuaRetAction * action, std::string & name)
			:NetWorkRetActionBox(name), mBindAction(nullptr), mBindLuaAction(action) { }

		~NetWorkRetActionBox1() { if (mBindLuaAction) { delete mBindLuaAction; } }

	public:
		void Invoke(shared_ptr<TcpClientSession> session, const NetWorkPacket & backData) override;
	private:
		NetWorkRetAction1 mBindAction;
		NetLuaRetAction * mBindLuaAction;
	};

	template<typename T>
	class NetWorkRetActionBox2 : public NetWorkRetActionBox
	{
	public:
		NetWorkRetActionBox2(NetWorkRetAction2<T> action, std::string & name)
			:NetWorkRetActionBox(name), mBindAction(action) { }

		~NetWorkRetActionBox2() { }

	public:
		void Invoke(shared_ptr<TcpClientSession> session, const NetWorkPacket & backData) override
		{
			mReturnData.Clear();
			XCode code = (XCode)backData.error_code();
			if (code != XCode::TimeoutAutoCall)
			{
				const std::string & message = backData.message_data();			
				if (!mReturnData.ParseFromArray(message.c_str(), message.size()))
				{
					this->mBindAction(session, XCode::ParseMessageError, mReturnData);
					SayNoDebugError("parse " << typeid(T).name() << " error code:" << code);
					return;
				}
			}
			this->mBindAction(session, code, mReturnData);
		}
	private:
		T mReturnData;
		NetWorkRetAction2<T> mBindAction;
	};


	class NetWorkRetActionBoxLua : public NetWorkRetActionBox
	{
	public:
		NetWorkRetActionBoxLua(NetLuaRetAction * action, std::string name);

		~NetWorkRetActionBoxLua() { if (mBindLuaAction) { delete mBindLuaAction; } }

	public:
		void Invoke(shared_ptr<TcpClientSession> session, const NetWorkPacket & backData);
	private:
		NetLuaRetAction * mBindLuaAction;
	};

	class NetWorkWaitActionBoxLua : public NetWorkRetActionBox
	{
	public:
		NetWorkWaitActionBoxLua(NetLuaWaitAction * action, std::string name);

		~NetWorkWaitActionBoxLua() { if (mBindLuaAction) { delete mBindLuaAction; } }

	public:
		void Invoke(shared_ptr<TcpClientSession> session, const NetWorkPacket & backData) override;
	private:
		NetLuaWaitAction * mBindLuaAction;
	};

	class CoroutineManager;

	class NetWorkWaitCorAction : public NetWorkRetActionBox
	{
	public:
		NetWorkWaitCorAction(std::string name, CoroutineManager *);
	public:
		void Invoke(shared_ptr<TcpClientSession> session, const NetWorkPacket & backData) override;
	public:
		XCode GetCode() { return this->mCode; }
		const std::string & GetMsgData() { return this->mMessage; }
	private:
		XCode mCode;
		std::string mMessage;
		long long mCoroutineId;
		CoroutineManager * mScheduler;
	};
}