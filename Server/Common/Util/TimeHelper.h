#pragma once
#include<string>
#include<Define/CommonTypeDef.h>
namespace TimeHelper
{
	extern std::string GetDateStr(long long time = 0);

	// ��ȡ����ʱ���
	extern long long GetMilTimestamp();

	// ��ȡ�뼶ʱ���
	extern long long GetSecTimeStamp();

	// ��ȡ΢�ʱ���
	extern long long GetMicTimeStamp();

	// ��ȡʱ���ַ��� ��ȷ����
	extern std::string GetDateString(long long t = time(NULL));

	// ��ȡʱ���ַ�����ȷ����
	extern std::string GetYearMonthDayString();

	
}