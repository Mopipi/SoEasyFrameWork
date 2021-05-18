
#pragma once
#include"SessionManager.h"
#include<NetWork/TcpClientSession.h>
#include<Protocol/ServerCommon.pb.h>
using namespace PB;



namespace SoEasy
{
	struct ActionProxyInfo
	{
	public:
		int mAreaId;			//��������id
		std::string mQueryAddress;	//ͨ�ŵ�ַ
		std::string mActionName;	//action����
		std::string mListenerAddress;	//������ַ
	public:
		bool operator == (ActionProxyInfo & actionInfo)
		{
			return this->mAreaId == actionInfo.mAreaId
				&& this->mActionName == actionInfo.mActionName
				&& this->mQueryAddress == actionInfo.mQueryAddress
				&& this->mListenerAddress == actionInfo.mListenerAddress;
				
		}
	};

	class TcpSessionListener;
	// ���з�����ע�ᵽ����(ȫ��Ψһ)
	class ActionRegisterManager : public SessionManager
	{
	public:
		ActionRegisterManager() { }
		~ActionRegisterManager() { }
	protected:
		bool OnInit() override;
		void OnInitComplete() override;
		void OnSessionErrorAfter(shared_ptr<TcpClientSession> tcpSession) override;
		void OnSessionConnectAfter(shared_ptr<TcpClientSession> tcpSession) override;
	private:
		XCode RegisterActions(long long id, shared_ptr<ActionUpdateInfo> actionInfo);
		XCode QueryActions(long long id, shared_ptr<Int32Data> areaId, shared_ptr<ActionInfoList> returnData);
	private:
		void BroadCastActionList(int areaId);
	private:
		void AddActionInfo(ActionProxyInfo & actionInfo);
	private:
		std::string mListenIp;
		unsigned short mListenPort;
		std::mutex mConnectSessionLock;
		class NetWorkManager * mNetWorkManager;
		std::vector<ActionProxyInfo> mActionRegisterList;
		shared_ptr<TcpSessionListener> mTcpSessionListener;
		std::unordered_map<std::string, int> mAreaSessionMap;
	};
}