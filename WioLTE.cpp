#include "WioLTE.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(str)			Seeed::Debug::Print(str)
#define DEBUG_PRINTLN(str)			Seeed::Debug::Println(str)
#else
#define DEBUG_PRINT(str)
#define DEBUG_PRINTLN(str)
#endif

#define POLLING_INTERVAL			(100)

////////////////////////////////////////////////////////////////////////////////////////
// WioLTE

bool WioLTE::Reset()
{
	_ResetModulePin = 0;
	wait_ms(200);
	_ResetModulePin = 1;
	wait_ms(300);

	Seeed::Stopwatch sw;
	sw.Restart();
	while (_Module.WaitForResponse("^RDY$", 100, 10) == NULL) {
		DEBUG_PRINT(".");
		if (sw.ElapsedMilliseconds() >= 10000) return false;
	}
	DEBUG_PRINTLN("");

	return true;
}

bool WioLTE::TurnOn()
{
	wait_ms(100);
	_PwrKeyPin = 1;
	wait_ms(200);
	_PwrKeyPin = 0;

	Seeed::Stopwatch sw;
	sw.Restart();
	while (IsBusy()) {
		DEBUG_PRINT(".");
		if (sw.ElapsedMilliseconds() >= 5000) return false;
		wait_ms(100);
	}
	DEBUG_PRINTLN("");

	sw.Restart();
	while (_Module.WaitForResponse("^RDY$", 100, 10) == NULL) {
		DEBUG_PRINT(".");
		if (sw.ElapsedMilliseconds() >= 10000) return false;
	}
	DEBUG_PRINTLN("");

	return true;
}

void WioLTE::Init()
{
	_ModulePwrPin = MODULE_PWR_PIN_INIT;
	_AntPwrPin = ANT_PWR_PIN_INIT;
	_EnableVccbPin = ENABLE_VCCB_PIN_INIT;
	_RgbLedPwrPin = RGB_LED_PWR_PIN_INIT;
	_PwrKeyPin = PWR_KEY_PIN_INIT;
	_ResetModulePin = RESET_MODULE_PIN_INIT;
	_DtrPin = DTR_PIN_INIT;
	_WakeupInPin = WAKEUP_IN_PIN_INIT;
	_WDisablePin = W_DISABLE_PIN_INIT;
}

void WioLTE::PowerSupplyLTE(bool on)
{
	_ModulePwrPin = on ? 1 : 0;
}

void WioLTE::PowerSupplyGrove(bool on)
{
	_EnableVccbPin = on ? 1 : 0;
}

bool WioLTE::IsBusy()
{
	return (int)_StatusPin ? true : false;
}

WioLTE::StatusType WioLTE::TurnOnOrReset()
{
	if (!IsBusy()) {
		if (!Reset()) return STATUS_E_RESET;
	}
	else {
		if (!TurnOn()) return STATUS_E_TURN_ON;
	}

	Seeed::Stopwatch sw;
	sw.Restart();
	while (_Module.WriteCommandAndWaitForResponse("AT", "^OK$", 500, 10) == NULL) {
		DEBUG_PRINT(".");
		if (sw.ElapsedMilliseconds() >= 10000) return STATUS_E_AT;
	}
	DEBUG_PRINTLN("");

	if (_Module.WriteCommandAndWaitForResponse("ATE0", "^OK$", 500, 10) == NULL) return STATUS_E_ATE;
	if (_Module.WriteCommandAndWaitForResponse("AT+QURCCFG=\"urcport\",\"uart1\"", "^OK$", 500, 10) == NULL) return STATUS_E_QURCCFG;
	if (_Module.WriteCommandAndWaitForResponse("AT+QSCLK=1", "^(OK|ERROR)$", 500, 10) == NULL) return STATUS_E_QSCLK;

	sw.Restart();
	while (true) {
		const char* response = _Module.WriteCommandAndWaitForResponse("AT+CPIN?", "^(OK|.CME ERROR: .*)$", 5000, 10);
		if (response == NULL) return STATUS_E_CPIN;
		if (strcmp(response, "OK") == 0) break;
		if (sw.ElapsedMilliseconds() >= 10000) return STATUS_E_CPIN_TIMEOUT;
		wait_ms(POLLING_INTERVAL);
	}

	return STATUS_OK;
}
