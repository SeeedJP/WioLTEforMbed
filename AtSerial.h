#pragma once

#include "seeedplatform.h"
#include <BufferedSerial.h> // https://os.mbed.com/users/sam_grove/code/BufferedSerial/
#include <vector>

class AtSerial {

private:
	BufferedSerial* _Serial;
	bool SerialAvailable() const { return _Serial->readable() != 0 ? true : false; }
	uint8_t SerialRead() { return _Serial->getc(); }
	void SerialWrite(uint8_t data) { _Serial->putc(data); }
	void SerialWrite(const uint8_t* data, int dataSize) { _Serial->write(data, dataSize); }

	std::vector<char> _LastResponse;
	bool WaitForAvailable(Seeed::Stopwatch* sw, int timeout) const;
	const char* ReadResponse(int timeout);

public:
	AtSerial(BufferedSerial* serial) :
		_Serial(serial)
	{
	}

	void WriteCommand(const char* command);
	const char* WaitForResponse(const char* responsePattern, int firstTimeout, int nextTimeout);
	const char* WriteCommandAndWaitForResponse(const char* command, const char* responsePattern, int firstTimeout, int nextTimeout);

};
