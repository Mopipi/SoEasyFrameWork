
#pragma once
#include"LocalService.h"
#include<NetWork/TcpClientSession.h>
#include<Protocol/ServerCommon.pb.h>
using namespace PB;



namespace SoEasy
{
	struct ActionProxyInfo
	{
	public:
		int mAreaId;			//��������id
		std::string mActionName;	//action����
		std::string mListenerAddress;	//������ַ
	public:
		bool operator == (ActionProxyInfo & actionInfo)
		{
			return this->mAreaId == actionInfo.mAreaId
				&& this->mActionName == actionInfo.mActionName
				&& this->mListenerAddress == actionInfo.mListenerAddress;
				
		}
	};
	class ProxyService;
	class TcpSessionListener;
	// ���з�����ע�ᵽ����(ȫ��Ψһ)
	class ServiceRegistry : public LocalService
	{
	public:
		ServiceRegistry();
		~ServiceRegistry() { }
	protected:
		bool OnInit() override;
		void OnInitComplete() override;
	private:
		XCode Register(long long id, shared_ptr<ServiceRegister_Request> actionInfo, shared_ptr<ServiceRegister_Respond> returnData);
	private:
		void RefreshServices(int areaId);
		int AddService(int areaId, const std::string & name, const std::string & address);
	private:
		int mServiceIndex;
		class NetWorkManager * mNetWorkManager;
		shared_ptr<TcpSessionListener> mTcpSessionListener;
		std::unordered_map<int, ProxyService *> mServiceMap;
		std::unordered_map<int, std::set<std::string>> mQuerySessionMap;
	};
}