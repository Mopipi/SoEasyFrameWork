#pragma once
#include"SessionManager.h"
#include<Protocol/ServerCommon.pb.h>
namespace SoEasy
{
	// ������actionע�ᵽԶ�� �������пɵ���action�б�
	class ActionQueryManager : public SessionManager
	{
	public:
		ActionQueryManager();
		~ActionQueryManager() { }
	protected:
		bool OnInit() override;
		void OnSessionErrorAfter(shared_ptr<TcpClientSession> tcpSession) override;
		void OnSessionConnectAfter(shared_ptr<TcpClientSession> tcpSession) override;
	public:
		bool GetActionAddress(const std::string & action, long long id, std::string & address);
	private:
		XCode UpdateActions(shared_ptr<TcpClientSession> session, long long id, const PB::AreaActionInfo & actionInfos);
	private:	
		int mAreaId;	//����id
		std::string mQueryIp;	//��ѯ��ַ��ip
		unsigned short mQueryPort;  // ��ѯ��ַ��port
		class ActionManager * mActionManager;
		class ListenerManager * mListenerManager;
		class CoroutineManager * mCoroutineManager;
		shared_ptr<TcpClientSession> mActionQuerySession;
		std::unordered_map<std::string, std::vector<std::string>> mActionAddressMap;	//action��ַ
	};
}