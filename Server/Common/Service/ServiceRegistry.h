
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
		XCode Register(long long id, shared_ptr<ServiceDataList> actionInfo, shared_ptr<ServiceDataList> returnData);
		XCode QueryService(long long id, shared_ptr<Int32Data> areaId, shared_ptr<ServiceDataList> returnData);
	private:
		void AddActionInfo(ActionProxyInfo & actionInfo);
	private:
		unsigned short mServiceIndex;
		class NetWorkManager * mNetWorkManager;
		std::vector<ProxyService *> mActionRegisterList;
		shared_ptr<TcpSessionListener> mTcpSessionListener;
	};
}