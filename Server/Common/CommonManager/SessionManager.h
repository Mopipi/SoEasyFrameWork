#pragma once
#include"Manager.h"
namespace SoEasy
{
	class SessionManager : public Manager
	{
	public:
		SessionManager() : Manager(1) { }
		virtual ~SessionManager() { }
	public:
		friend TcpClientSession;
		shared_ptr<TcpClientSession> CreateTcpSession(SharedTcpSocket socket);
		shared_ptr<TcpClientSession> CreateTcpSession(std::string name, std::string ip, unsigned short port);
	private:	//不要手动调用
		bool AddNewSession(shared_ptr<TcpClientSession> tcpSession);
		bool AddErrorSession(shared_ptr<TcpClientSession> tcpSession);
		void AddRecvMessage(shared_ptr<TcpClientSession> tcpSession, const char * message, size_t size);
	protected:
		bool OnInit() override;
		virtual void OnSessionErrorAfter(shared_ptr<TcpClientSession> tcpSession) = 0;
		virtual void OnSessionConnectAfter(shared_ptr<TcpClientSession> tcpSession) = 0;
		virtual void OnRecvNewMessageAfter(const std::string & address, const char * msg, size_t size);
	protected:
		void OnSystemUpdate() final;
	protected:
		class NetWorkManager * mNetWorkManager;
	private:
		NetWorkPacket mNetWorkPacket;	
		class ActionManager * mFunctionManager;
		DoubleBufferQueue<SharedNetPacket> mRecvMessageQueue;
		DoubleBufferQueue<shared_ptr<TcpClientSession>> mNewSessionQueue;
		DoubleBufferQueue<shared_ptr<TcpClientSession>> mErrorSessionQueue;
	};
}