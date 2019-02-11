#include "String.h"

namespace utility
{
void Test_String()
{
	String str("Hello world");
	std::cout << str << std::endl;

	str = "Hi there";
	std::cout << str << std::endl;

	str = str;
	std::cout << str << std::endl;
}

String::String() : m_str(new char[1]())
{
}

String::String(const char *str) : m_str(new char[1 + strlen(str)]())
{
	strncpy(m_str, str, 1 + strlen(str));
}

String::~String()
{
	delete []m_str;
}

String::String(const String &s) : m_str(new char[1 + s.Length()]())
{
	strncpy(m_str, s.m_str, 1 + s.Length());
}

String& String::operator=(const String &s)
{
	char *tmp = new char[1 + s.Length()]();
	strncpy(tmp, s.m_str, 1 + s.Length());

	delete m_str;
	m_str = tmp;

	return *this;
}

}
