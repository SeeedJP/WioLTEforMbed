#include "seeedplatform.h"
#include "WioLTE.h"

WioLTE Wio;

int main() {
	Seeed::Debug::Println("");
	Seeed::Debug::Println("--- START ---------------------------------------------------");

	Seeed::Debug::Println("### I/O Initialize.");
	Wio.Init();

	Seeed::Debug::Println("### Power supply ON.");
	Wio.PowerSupplyLTE(true);
	wait_ms(5000);

	Seeed::Debug::Println("### Turn on or reset.");
	if (Wio.TurnOnOrReset() != WioLTE::STATUS_OK) {
		Seeed::Debug::Println("ERROR!!!");
		return -1;
	}

	Seeed::Debug::Println("Finish.");

	return 0;
}
