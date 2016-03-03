#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

typedef union button32{
	uint32_t bitfield;
	struct{
		uint8_t data1;
		uint8_t data2;
		uint8_t data3;
		uint8_t data4;
	};
	struct{
		uint8_t b00:1;	uint8_t b01:1;	uint8_t b02:1;	uint8_t b03:1;
		uint8_t b04:1;	uint8_t b05:1;	uint8_t b06:1;	uint8_t b07:1;
		uint8_t b08:1;	uint8_t b09:1;	uint8_t b10:1;	uint8_t b11:1;
		uint8_t b12:1;	uint8_t b13:1;	uint8_t b14:1;	uint8_t b15:1;
		uint8_t b16:1;	uint8_t b17:1;	uint8_t b18:1;	uint8_t b19:1;
		uint8_t b20:1;	uint8_t b21:1;	uint8_t b22:1;	uint8_t b23:1;
		uint8_t b24:1;	uint8_t b25:1;	uint8_t b26:1;	uint8_t b27:1;
		uint8_t b28:1;	uint8_t b29:1;	uint8_t b30:1;	uint8_t b31:1;
	};
}button32_t;

#define HAT_UP			0
#define HAT_UPRIGHT		1
#define HAT_RIGHT		2
#define HAT_DOWNRIGHT	3
#define HAT_DOWN		4
#define HAT_DOWNLEFT	5
#define HAT_LEFT		6
#define HAT_UPLEFT		7
#define HAT_CENTER		8

typedef union hats8{
	uint8_t data;
	struct{
		uint8_t switch1:4;
		uint8_t switch2:4;
	};
}hats8_t;

#define AXIS_CENTER	0
#define AXIS_MIN	-32768
#define AXIS_MAX	32767

typedef union axis16{
	int16_t axis;
	struct{
		uint8_t dataHi;
		uint8_t dataLo;
	};
}axis16_t;

typedef struct JoyState{ 		// Pretty self explanitory. Simple state to store all the joystick parameters
	//8 signed 16-bit axes
	axis16_t	x;
	axis16_t	y;
	axis16_t	z;
	axis16_t	xRot;
	axis16_t	yRot;
	axis16_t	zRot;
	axis16_t	slider;
	axis16_t	dial;
	//2 4-bit hat switches
	hats8_t		hats;
	//uint8_t	hatSw1;
	//uint8_t	hatSw2;
	//32 buttons
	//uint32_t	buttons;
	button32_t	buttons;
} JoyState_t;

class Joystick_
{
public:
	JoyState_t state;
	Joystick_(void);
	void clearState(void);
	void sendState(void);
};
extern Joystick_ Joystick;

#endif
#endif