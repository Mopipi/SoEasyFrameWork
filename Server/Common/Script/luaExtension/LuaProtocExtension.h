#pragma once
#include<Script/LuaInclude.h>
extern "C"
{
	namespace LuaProtocExtension
	{
		//��һ��lua�����л���һ��protoc���󣬷������л���Ķ�����
		extern int Serialization(lua_State * lua);
		extern int CreateByTable(lua_State * lua);

	}
}