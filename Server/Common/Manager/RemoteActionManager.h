#pragma once
#include"SessionManager.h"
#include<NetWork/RemoteActionProxy.h>
#include<Protocol/ServerCommon.pb.h>

namespace SoEasy
{
	// ������actionע�ᵽԶ�� �������пɵ���action�б�

	class RemoteActionManager : public SessionManager
	{
	public:
		RemoteActionManager();
		~RemoteActionManager() { }
	protected:
		bool OnInit() override;
		void OnSessionErrorAfter(shared_ptr<TcpClientSession> tcpSession) override;
		void OnSessionConnectAfter(shared_ptr<TcpClientSession> tcpSession) override;
	public:
		bool GetActionProxy(const std::string & action, shared_ptr<RemoteActionProxy> & actionProxy);
		bool GetActionProxy(const std::string & action, std::vector<shared_ptr<RemoteActionProxy>> & actionProxys);
		bool GetActionProxy(const std::string & action, long long operId, shared_ptr<RemoteActionProxy> & actionProxy);
		void GetActionProxyByAddress(const std::string & address, std::vector<shared_ptr<RemoteActionProxy>> & actionProxys);
	private:
		void StartRegisterAction();
		void StartPullActionList();  //��ʼ��ȡaction�б�
		bool StartConnectToAction(shared_ptr<RemoteActionProxy> actionProxy);
		void AddNewActionProxy(int argaId, const std::string & name, const std::string & address);
	private:	
		int mAreaId;	//����id
		std::string mQueryIp;	//��ѯ��ַ��ip
		unsigned short mQueryPort;  // ��ѯ��ַ��port
		std::string mQueryAddress;
		class LocalActionManager * mActionManager;
		class ListenerManager * mListenerManager;
		class CoroutineManager * mCoroutineManager;
		shared_ptr<TcpClientSession> mActionQuerySession;
		std::unordered_map<std::string, shared_ptr<TcpClientSession>> mActionSessionMap;
		std::unordered_map<std::string, std::vector<shared_ptr<RemoteActionProxy>>> mActionProxyMap;//action��ַ
	};
}