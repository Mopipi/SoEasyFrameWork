#pragma once
#include<Manager/Manager.h>
#include<Other/TimeRecorder.h>

namespace SoEasy
{
	// ע�᱾��Lua���񣬹���Զ�̻����Ļص�
	class NetLuaAction;
	class LocalActionProxy;
	class LocalRetActionProxy;

	class ActionManager : public Manager
	{
	public:
		ActionManager();
		virtual ~ActionManager() { }
	public:
		void AddActionArgv(shared_ptr<NetWorkPacket> messageData);	
		bool AddCallback(shared_ptr<LocalRetActionProxy> actionBox, long long & callbackId);
	protected:
		bool OnInit() override;
		void OnSystemUpdate() final;					//����ϵͳ�¼�
	private:
		int mMessageTimeout;
		std::string mMessageBuffer;
		TimeRecorder mLogicTimeRecorder;
		TimeRecorder mNetLatencyRecorder;
		class TimerManager * mTimerManager;
	private:
		DoubleBufferQueue<SharedPacket> mCallbackMessageQueue;
		std::unordered_map<long long, shared_ptr<LocalRetActionProxy>> mRetActionMap;
	};
}