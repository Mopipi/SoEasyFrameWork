#pragma once
#include<type_traits>
namespace SoEasy
{
	template<typename T>
	struct TypeReflection
	{
	public:
		static constexpr bool Value = false;
		static constexpr char * Name = nullptr;
	};
//#define TYPE_REFLECTION(type, base) template<> struct TypeReflection<type, base> { static constexpr char * Name = (char*)#type; static constexpr bool Value = true; typedef typename std::enable_if<(std::is_base_of<base, type>::value), type>::type Type;}

	//template<typename T, typename Base>
	
#define TYPE_REFLECTION(T)					\
	template<> struct TypeReflection<T>	\
	{												\
	public:											\
		static constexpr bool Value = true;		\
		static constexpr char * Name = (char*)#T;		\
		static constexpr size_t Size = sizeof(T);	\
	}
#define ChildType(type, base) typename std::enable_if<std::is_base_of<base,type>::value && TypeReflection<type>::Value, type>::type
}