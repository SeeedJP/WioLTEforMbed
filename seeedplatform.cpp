#include "seeedplatform.h"

namespace Seeed {

/////////////////////////////////////////////////////////////////////
// Debug

void Debug::Print(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);

	fflush(stdout);
}

void Debug::Println(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);

	fputs("\r\n", stdout);

	fflush(stdout);
}

/////////////////////////////////////////////////////////////////////

} // namespace seeed
