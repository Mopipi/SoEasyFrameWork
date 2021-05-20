#pragma once
#include<NetWork/RemoteActionProxy.h>
#include<Protocol/ServerCommon.pb.h>
#include<Manager/SessionManager.h>
namespace SoEasy
{
	// ������actionע�ᵽԶ�� �������пɵ���action�б�

	class ServiceQuery : public SessionManager
	{
	public:
		ServiceQuery();
		~ServiceQuery() { }
	protected:
		bool OnInit() final;
		void OnInitComplete() final;
		void OnSessionErrorAfter(SharedTcpSession tcpSession) final;
		void OnSessionConnectAfter(SharedTcpSession tcpSession) final;
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
		class ActionManager * mActionManager;
		class ListenerManager * mListenerManager;
		class CoroutineManager * mCoroutineManager;
		shared_ptr<TcpClientSession> mActionQuerySession;
		std::unordered_map<std::string, shared_ptr<TcpClientSession>> mActionSessionMap;
		std::unordered_map<std::string, std::vector<shared_ptr<RemoteActionProxy>>> mActionProxyMap;//action��ַ
	};
}