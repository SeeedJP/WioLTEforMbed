#include "AtSerial.h"
#include <slre.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(...)			Seeed::Debug::Print(__VA_ARGS__)
#define DEBUG_PRINTLN(...)			Seeed::Debug::Println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

#define CHAR_CR	(0x0d)
#define CHAR_LF	(0x0a)

bool AtSerial::WaitForAvailable(Seeed::Stopwatch* sw, int timeout) const
{
	while (!SerialAvailable()) {
		if (sw->ElapsedMilliseconds() >= timeout) return false;
	}
	return true;
}

const char* AtSerial::ReadResponse(int timeout)
{
	_LastResponse.clear();

	Seeed::Stopwatch sw;
	while (true) {
		// Wait for available.
		sw.Restart();
		if (!WaitForAvailable(&sw, timeout)) return NULL;

		// Read byte.
		uint8_t b = SerialRead();
		_LastResponse.push_back(b);
		int responseSize = _LastResponse.size();

		// Is received delimiter?
		if (responseSize >= 2 && _LastResponse[responseSize - 2] == CHAR_CR && _LastResponse[responseSize - 1] == CHAR_LF) {
			_LastResponse.pop_back();
			*_LastResponse.rbegin() = '\0';
			return &_LastResponse[0];
		}
	}
}

void AtSerial::WriteCommand(const char* command)
{
	DEBUG_PRINT("<- ");
	DEBUG_PRINTLN(command);

	SerialWrite((const uint8_t*)command, strlen(command));
	SerialWrite(CHAR_CR);
}

const char* AtSerial::WaitForResponse(const char* responsePattern, int firstTimeout, int nextTimeout)
{
	Seeed::Stopwatch sw;
	sw.Restart();
	while (true) {
		if (!WaitForAvailable(&sw, firstTimeout)) return NULL;

		const char* response = ReadResponse(nextTimeout);

		// responsePattern?
		if (responsePattern != NULL) {
			slre_cap capture;
			if (slre_match(responsePattern, response, strlen(response), &capture, 1, 0) >= 0) {
				DEBUG_PRINT("-> ");
				DEBUG_PRINTLN(response);
				return response;
			}
		}

		DEBUG_PRINT("-> (");
		DEBUG_PRINT(response);
		DEBUG_PRINTLN(")");
	}
}

const char* AtSerial::WriteCommandAndWaitForResponse(const char* command, const char* responsePattern, int firstTimeout, int nextTimeout)
{
	WriteCommand(command);
	return WaitForResponse(responsePattern, firstTimeout, nextTimeout);
}
