#pragma once
#include"Manager.h"
namespace SoEasy
{
	// ���ط��ʹ���  ��������Է��ʱ���action
	class CoroutineManager;
	class LocalActionManager;
	
	class LocalAccessManager : public Manager
	{
	public:
		LocalAccessManager() { }
		~LocalAccessManager() { }
	protected:
		bool OnInit() final;						//��ʼ��������
		void OnSystemUpdate() final;					//����ϵͳ�¼�
	public:
		bool CallAction(const std::string & func, shared_ptr<NetWorkPacket> returnPackage);
	private:
		void HandleLocationRetAction(shared_ptr<NetWorkPacket> returnPackage);	//�����ص���
		void HandleLocationCallAction(shared_ptr<NetWorkPacket> returnPackage);	//�����ص���
	private:
		CoroutineManager * mCoroutineManager;
		LocalActionManager * mLocalActionManager;
		std::queue<shared_ptr<NetWorkPacket>> mLocalRetActionMessage; //���ط�����Ϣ����
		std::queue<shared_ptr<NetWorkPacket>> mLocalCallActionMessage; //���ص�����Ϣ����
	};
}