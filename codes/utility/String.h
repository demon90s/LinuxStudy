#ifndef STRING_H
#define STRING_H

#include <cstdlib>
#include <cstring>
#include <iostream>

/*
 * 字符串类型，动态分配
 */

namespace utility
{
extern void Test_String();

class String
{
	friend std::ostream& operator<<(std::ostream&, const String&);
public:
	String();
	String(const char *str);
	~String();
	String(const String&);
	String& operator=(const String&);

	size_t Length() const { return strlen(m_str); }
	char* CStr() { return m_str; }

private:
	char *m_str;
};

inline std::ostream& operator<<(std::ostream &os, const String &s)
{
	os << s.m_str;
	return os;
}
}

#endif // STRING_H
