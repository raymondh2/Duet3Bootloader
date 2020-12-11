/*
 * Devices.cpp
 *
 *  Created on: 28 Jul 2020
 *      Author: David
 */

#include <Hardware/Devices.h>

#if SAMC21

#include <RepRapFirmware.h>
#include <AnalogIn.h>
#include <Version.h>

// The interrupt vector table points to this
extern const char VersionText[] =
#ifdef SAMMYC21
	"SAMMY-C21 bootloader version " VERSION_TEXT;
#else
	"SAMC21 bootloader version " VERSION_TEXT;
#endif

#ifdef DEBUG

// UART support for debugging

# ifdef SAMMYC21

void SerialPortInit(AsyncSerial*) noexcept
{
	SetPinFunction(PortBPin(2), GpioPinFunction::D);		// TxD
}

void SerialPortDeinit(AsyncSerial*) noexcept
{
	pinMode(PortBPin(2), INPUT_PULLUP);
}

AsyncSerial uart0(5, 3, 512, 512, SerialPortInit, SerialPortDeinit);

extern "C" void SERCOM5_Handler()
{
	uart0.Interrupt();
}

# else

void SerialPortInit(AsyncSerial*) noexcept
{
	SetPinFunction(PortAPin(12), GpioPinFunction::D);		// TxD
}

void SerialPortDeinit(AsyncSerial*) noexcept
{
	pinMode(PortAPin(12), INPUT_PULLUP);
}

AsyncSerial uart0(4, 3, 512, 512, SerialPortInit, SerialPortDeinit);

extern "C" void SERCOM4_Handler()
{
	uart0.Interrupt();
}

# endif

#endif

void DeviceInit() noexcept
{
#ifndef SAMMYC21
	AnalogIn::Init(CommonAdcDevice);
#endif
}

#endif

// End
