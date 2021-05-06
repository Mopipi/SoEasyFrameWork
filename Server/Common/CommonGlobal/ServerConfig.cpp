#include<fstream>
#include"ServerConfig.h"
#include<CommonDefine/CommonDef.h>
#include<CommonUtil/FileHelper.h>
namespace SoEasy
{
	ServerConfig::ServerConfig(const std::string path)
		:mConfigPath(path)
	{
		this->mFps = 10;
		this->mServerID = 0;	
		this->mServerPort = 0;
		this->mServerAreaId = 0;
		this->mCenterSrvPort = 0;
		this->mRecvBufferCount = 1024;
		this->mSendBufferCount = 1024;
	}

	bool ServerConfig::InitConfig()
	{
		if (!FileHelper::ReadJsonFile(mConfigPath, this->mConfigDocument))
		{
			SayNoDebugError("not find config " << mConfigPath);
			return false;
		}
		auto iter = this->mConfigDocument.MemberBegin();
		for (; iter != this->mConfigDocument.MemberEnd(); iter++)
		{
			const std::string key = iter->name.GetString();
			rapidjson::Value * value = &iter->value;
			this->mMapConfigData.emplace(key, value);
		}
		return true;
	}

	bool ServerConfig::HasValue(const std::string k2)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		return value != nullptr && value->IsNull() == false;
	}

	bool ServerConfig::GetValue(const std::string k2, int & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsInt())
		{
			data = value->GetInt();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, bool & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsBool())
		{
			data = value->GetBool();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, float & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsFloat())
		{
			data = value->GetFloat();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, double & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsDouble())
		{
			data = value->GetDouble();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, long long & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsInt64())
		{
			data = value->GetInt64();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, std::string & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsString())
		{
			data.clear();
			const char * str = value->GetString();
			const size_t size = value->GetStringLength();
			data.append(str, size);
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, unsigned int & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsUint())
		{
			data = value->GetUint();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, unsigned short & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsUint())
		{
			data = (unsigned short)value->GetUint();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, unsigned long long & data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsUint64())
		{
			data = value->GetUint64();
			return true;
		}
		return false;
	}

	bool ServerConfig::GetValue(const std::string k2, std::vector<std::string>& data)
	{
		rapidjson::Value * value = this->GetJsonValue(k2);
		if (value && value->IsArray())
		{
			for (auto iter = value->Begin(); iter != value->End(); iter++)
			{
				if (iter->IsString())
				{
					std::string str(iter->GetString(), iter->GetStringLength());
					data.push_back(str);
				}
			}
			return true;
		}
		return false;
	}

	bool ServerConfig::FindIpFromWhiteList(const std::string & ip)
	{
		if (this->mWhiteListVec.empty())
		{
			return true;
		}
		auto iter = this->mWhiteListVec.find(ip);
		return iter != this->mWhiteListVec.end();
	}

	rapidjson::Value * ServerConfig::GetJsonValue(const std::string & k2)
	{
		auto iter = this->mMapConfigData.find(k2);
		return iter != this->mMapConfigData.end() ? iter->second : nullptr;
	}
}
