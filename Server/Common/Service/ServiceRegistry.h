
#pragma once
#include"ServiceBase.h"
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

	class TcpSessionListener;
	// ���з�����ע�ᵽ����(ȫ��Ψһ)
	class ServiceRegistry : public ServiceBase
	{
	public:
		ServiceRegistry() { }
		~ServiceRegistry() { }
	protected:
		bool OnInit() override;
		void OnInitComplete() override;
	private:
		XCode RegisterActions(long long id, shared_ptr<ActionUpdateInfo> actionInfo);
		XCode QueryActions(long long id, shared_ptr<Int32Data> areaId, shared_ptr<ActionInfoList> returnData);
	private:
		void AddActionInfo(ActionProxyInfo & actionInfo);
	private:
		class NetWorkManager * mNetWorkManager;
		std::vector<ActionProxyInfo> mActionRegisterList;
		shared_ptr<TcpSessionListener> mTcpSessionListener;
	};
}