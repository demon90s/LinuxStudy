#include "core.h"
#include <stdio.h>
#include <stdarg.h>

extern void print(const char* prefix, const char* format, ...)
{
	va_list ap;

	printf("%s ", prefix);

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	printf("\n");
}
