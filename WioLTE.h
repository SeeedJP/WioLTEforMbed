#pragma once

#include "seeedplatform.h"
#include "AtSerial.h"
#include <BufferedSerial.h> // https://os.mbed.com/users/sam_grove/code/BufferedSerial/

class WioLTE {

private:
	// Power supply
	static const PinName MODULE_PWR_PIN		= PB_5;
	static const int MODULE_PWR_PIN_INIT	= 0;
	static const PinName ANT_PWR_PIN		= PB_12;
	static const int ANT_PWR_PIN_INIT		= 0;
	static const PinName ENABLE_VCCB_PIN	= PB_10;
	static const int ENABLE_VCCB_PIN_INIT	= 0;
	static const PinName RGB_LED_PWR_PIN	= PA_8;
	static const int RGB_LED_PWR_PIN_INIT	= 1;

	// Turn on/off Pins
	static const PinName PWR_KEY_PIN		= PC_4;
	static const int PWR_KEY_PIN_INIT		= 0;
	static const PinName RESET_MODULE_PIN	= PC_3;
	static const int RESET_MODULE_PIN_INIT	= 1;

	// Status Indication Pins
	static const PinName STATUS_PIN			= PB_15;

	// UART Interface
	static const PinName DTR_PIN			= PA_1;
	static const int DTR_PIN_INIT			= 0;

	// GPIO Pins
	static const PinName WAKEUP_IN_PIN		= PC_0;
	static const int WAKEUP_IN_PIN_INIT		= 0;
	static const PinName W_DISABLE_PIN		= PC_2;
	static const int W_DISABLE_PIN_INIT		= 1;

private:
	// Power supply
	DigitalOut _ModulePwrPin;
	DigitalOut _AntPwrPin;
	DigitalOut _EnableVccbPin;
	DigitalOut _RgbLedPwrPin;

	// Turn on/off Pins
	DigitalOut _PwrKeyPin;
	DigitalOut _ResetModulePin;

	// Status Indication Pins
	DigitalIn _StatusPin;

	// UART Interface
	DigitalOut _DtrPin;

	// GPIO Pins
	DigitalOut _WakeupInPin;
	DigitalOut _WDisablePin;

	BufferedSerial _Serial;
	AtSerial _Module;

public:
	enum StatusType {
		STATUS_OK,
		STATUS_E_RESET,
		STATUS_E_TURN_ON,
		STATUS_E_AT,
		STATUS_E_ATE,
		STATUS_E_QURCCFG,
		STATUS_E_QSCLK,
		STATUS_E_CPIN,
		STATUS_E_CPIN_TIMEOUT,
	};

public:
	bool Reset();
	bool TurnOn();

public:
	WioLTE() :
		_ModulePwrPin(MODULE_PWR_PIN, MODULE_PWR_PIN_INIT),
		_AntPwrPin(ANT_PWR_PIN, ANT_PWR_PIN_INIT),
		_EnableVccbPin(ENABLE_VCCB_PIN, ENABLE_VCCB_PIN_INIT),
		_RgbLedPwrPin(RGB_LED_PWR_PIN, RGB_LED_PWR_PIN_INIT),
		_PwrKeyPin(PWR_KEY_PIN, PWR_KEY_PIN_INIT),
		_ResetModulePin(RESET_MODULE_PIN, RESET_MODULE_PIN_INIT),
		_StatusPin(STATUS_PIN),
		_DtrPin(DTR_PIN, DTR_PIN_INIT),
		_WakeupInPin(WAKEUP_IN_PIN, WAKEUP_IN_PIN_INIT),
		_WDisablePin(W_DISABLE_PIN, W_DISABLE_PIN_INIT),
		_Serial(PA_2, PA_3),
		_Module(&_Serial)
	{
		_Serial.baud(115200);
	}

	void Init();

	void PowerSupplyLTE(bool on);
	void PowerSupplyGrove(bool on);
	bool IsBusy();
	StatusType TurnOnOrReset();

};
