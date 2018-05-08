#ifndef STRING_TRANS_H
#define STRING_TRANS_H

#include <string>

namespace utility
{
class StringTrans
{
public:
	StringTrans(const char *str) : m_str(str) {}

	std::string ToUpper();
	std::string ToLower();

private:
	std::string m_str;
};

extern void Test_StringTrans();
}

#endif
