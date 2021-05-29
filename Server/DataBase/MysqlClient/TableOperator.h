#pragma once
#include<string>
#include<Manager/MysqlManager.h>
namespace SoEasy
{

	/*
	����protobuf�ļ�����sql��
	����ֶ�û�л�����ֶ�
	*/

	class TableOperator
	{
	public:
		TableOperator(SayNoMysqlSocket * socket, const std::string db, const std::string & path);
	public:
		bool InitMysqlTable();
	private:
		bool CreateMysqlTable(const std::string table, const std::string name, const std::string key);
		bool UpdateMysqlTable(const std::string table, const std::string name, const std::string key);
	private:
		bool AddNewField(const std::string table, const FieldDescriptor * fieldDesc);
	private:
		std::string mDataBase;
		std::string mConfigPath;
		rapidjson::Document mDocument;
		SayNoMysqlSocket * mMysqlSocket;
		
	};
}