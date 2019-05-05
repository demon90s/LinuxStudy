#include "StringTrans.h"
#include <cstring>
#include <iostream>

namespace utility
{
extern void Test_StringTrans()
{
	StringTrans str_trans = "Hello There";
	std::cout << "To upper: " << str_trans.ToUpper() << std::endl;
	std::cout << "To lower: " << str_trans.ToLower() << std::endl;
}

std::string StringTrans::ToUpper()
{
	std::string str_tmp;
	for (auto c : m_str)
		str_tmp += toupper(c);
	return str_tmp;
}

std::string StringTrans::ToLower()
{
	std::string str_tmp;
	for (auto c : m_str)
		str_tmp += tolower(c);
	return str_tmp;
}

}
