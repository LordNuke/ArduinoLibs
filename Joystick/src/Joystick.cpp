#include "joystick.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptorJoystick[] PROGMEM = {
	//32 buttons, 2 8-way hats, and 8 axes.
    0x05, 0x01,			//USAGE_PAGE (Generic Desktop)
    0x09, 0x05,			//USAGE (Game Pad)
    0xa1, 0x01,			//COLLECTION (Application)
    0x85, 0x03,			//	REPORT_ID (3)
    0xa1, 0x00,			//	COLLECTION (Physical)
	//32 buttons
    0x05, 0x09,			//		USAGE_PAGE (Button)
    0x19, 0x01,			//		USAGE_MINIMUM (Button 1)
    0x29, 0x20,			//		USAGE_MAXIMUM (Button 32)
    0x15, 0x00,			//		LOGICAL_MINIMUM (0)
    0x25, 0x01,			//		LOGICAL_MAXIMUM (1)
    0x95, 0x20,			//		REPORT_COUNT (32)
    0x75, 0x01,			//		REPORT_SIZE (1)
    0x81, 0x02,			//		INPUT (Data,Var,Abs)
	//2 8-way hat switches
	0x05, 0x01,			//		USAGE_PAGE (Generic Desktop)
	0x09, 0x39,			//		USAGE (Hat switch)
	0x15, 0x00,			//		LOGICAL_MINIMUM (0)
	0x25, 0x07,			//		LOGICAL_MAXIMUM (7)
	0x35, 0x00,			//		PHYSICAL_MINIMUM (0)
	0x46, 0x3B, 0x01,	//		PHYSICAL_MAXIMUM (315)
	0x65, 0x14,			//		UNIT (Eng Rot:Angular Pos)
	0x75, 0x04,			//		REPORT_SIZE (4)
	0x95, 0x01,			//		REPORT_COUNT (1)
	0x81, 0x02,			//		INPUT (Data,Var,Abs)
	0x09, 0x39,			//		USAGE (Hat switch)
	0x15, 0x00,			//		LOGICAL_MINIMUM (0)
	0x25, 0x07,			//		LOGICAL_MAXIMUM (7)
	0x35, 0x00,			//		PHYSICAL_MINIMUM (0)
	0x46, 0x3B, 0x01,	//		PHYSICAL_MAXIMUM (315)
	0x65, 0x14,			//		UNIT (Eng Rot:Angular Pos)
	0x75, 0x04,			//		REPORT_SIZE (4)
	0x95, 0x01,			//		REPORT_COUNT (1)
	0x81, 0x02,			//		INPUT (Data,Var,Abs)
	//8 16-bit axes
	0xA1, 0x00,			//		COLLECTION (Physical)
    0x05, 0x01,			//			USAGE_PAGE (Generic Desktop)
    0x09, 0x30,			//			USAGE (X)
    0x09, 0x31,			//			USAGE (Y)
    0x09, 0x32,			//			USAGE (Z)
    0x09, 0x33,			//			USAGE (Rx)
    0x09, 0x34,			//			USAGE (Ry)
    0x09, 0x35,			//			USAGE (Rz)
    0x09, 0x36,			//			USAGE (Slider)
    0x09, 0x37,			//			USAGE (Dial)
    0x16, 0x00, 0x80,	//			LOGICAL_MINIMUM (-32768)
    0x26, 0xff, 0x7f,	//			LOGICAL_MAXIMUM (32767)
    0x75, 0x10,			//			REPORT_SIZE (16)
    0x95, 0x08,			//			REPORT_COUNT (8)
    0x81, 0x02,			//			INPUT (Data,Var,Abs)
	0xc0,				//		END_COLLECTION
    0xc0,				//	END_COLLECTION
    0xc0				//END_COLLECTION
};

//constructor that does nothing
Joystick_::Joystick_(void){
	clearState();
	//append the discriptor to a thing idk
	static HIDSubDescriptor node(_hidReportDescriptorJoystick, sizeof(_hidReportDescriptorJoystick));
    HID().AppendDescriptor(&node);
}

//reset joy state to defaults
void Joystick_::clearState(void){
	state.x.axis = AXIS_CENTER;
	state.y.axis = AXIS_CENTER;
	state.z.axis = AXIS_CENTER;
	state.xRot.axis = AXIS_CENTER;
	state.yRot.axis = AXIS_CENTER;
	state.zRot.axis = AXIS_CENTER;
	state.slider.axis = AXIS_CENTER;
	state.dial.axis = AXIS_CENTER;
	state.hats.switch1 = HAT_CENTER;
	state.hats.switch2 = HAT_CENTER;
	state.buttons.bitfield = 0;
}
//format and send state report. The report data format must match the one defined in the descriptor exactly
//or it either won't work, or the pc will make a mess of unpacking the data
#define JOY_DATA_SIZE 21
void Joystick_::sendState(void){
	uint8_t data[]{
		//buttons
		state.buttons.data1,
		state.buttons.data2,
		state.buttons.data3,
		state.buttons.data4,
		//hats
		state.hats.data,
		//axes
		state.x.dataHi,
		state.x.dataLo,
		state.y.dataHi,		
		state.y.dataLo,
		state.z.dataHi,
		state.z.dataLo,
		state.xRot.dataHi,	
		state.xRot.dataLo,
		state.yRot.dataHi,
		state.yRot.dataLo,
		state.zRot.dataHi,	
		state.zRot.dataLo,
		state.slider.dataHi,
		state.slider.dataLo,
		state.dial.dataHi,
		state.dial.dataLo
	};
	//HID_SendReport(Report number, array of values in same order as HID descriptor, length)
	//HID_SendReport(3, data, JOY_DATA_SIZE);
	HID().SendReport(3,data,sizeof(data));
	// The joystick is specified as using report 3 in the descriptor. That's where the "3" comes from
}

Joystick_ Joystick;


#endif