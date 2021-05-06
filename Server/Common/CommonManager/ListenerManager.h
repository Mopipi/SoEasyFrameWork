#pragma once
#include"SessionManager.h"

#include<CommonOther/ServerRegisterInfo.h>
#include<CommonProtocol/ServerCommon.pb.h>

using namespace PB;
namespace SoEasy
{
	// �����ⲿ���ӽ�����session
	class ListenerManager : public SessionManager
	{
	public:
		ListenerManager() { }
		~ListenerManager() { }
	public:
		const std::string & GetAddress() { return mListenAddress; }
	protected:
		bool OnInit() override;
		void OnInitComplete() override;
	protected:
		void OnSessionErrorAfter(shared_ptr<TcpClientSession> tcpSession) override;
		void OnSessionConnectAfter(shared_ptr<TcpClientSession> tcpSession) override;
	private:
		std::string mListenerIp;	//������ip
		std::string mListenAddress;	//��ַ
		unsigned short mListenerPort; //�����Ķ˿ں�
		shared_ptr<class TcpSessionListener> mTcpSessionListener;
		std::unordered_map<std::string, ServerRegisterInfo> mRegisterServerMap;
	};
}