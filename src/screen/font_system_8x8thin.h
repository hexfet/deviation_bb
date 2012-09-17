/* ********************************************************************************
	NAME 		: FONT.C
	EXTENDED NAME	: Fonts for graphic LCD based on KS0108 or HD61202
	LAYER		: Application
	DESCRIPTION	: 
	AUTHOR		: Stephane REY			  

Ported from Original C51 code to ARM By 

Mukund Deshmukh.
email betacomp_ngp@sancharnet.in
http://betacomp.com
Dt 08.06.2006

*/
//width = 8
//height = 8
//Proportional = 0
//first_char = 0x20
//last_char = 0x80
const u8 Font8x8thn[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x5F,0x00,0x00,0x00,0x00,
    0x00,0x00,0x07,0x00,0x00,0x07,0x00,0x00,
    0x00,0x14,0x7F,0x14,0x14,0x7F,0x14,0x00,
    0x00,0x24,0x2A,0x6B,0x6B,0x2A,0x12,0x00,
    0x00,0x46,0x26,0x10,0x08,0x64,0x62,0x00,
    0x30,0x4A,0x45,0x4D,0x32,0x48,0x48,0x00,
    0x00,0x00,0x04,0x03,0x00,0x00,0x00,0x00,
    0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00,
    0x00,0x00,0x41,0x22,0x1C,0x00,0x00,0x00,
    0x08,0x2A,0x1C,0x1C,0x1C,0x2A,0x08,0x00,
    0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00,
    0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,
    0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
    0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,
    0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x00,
    0x00,0x3E,0x61,0x51,0x49,0x45,0x3E,0x00,
    0x00,0x44,0x42,0x7F,0x40,0x40,0x00,0x00,
    0x00,0x62,0x51,0x51,0x49,0x49,0x66,0x00,
    0x00,0x22,0x41,0x49,0x49,0x49,0x36,0x00,
    0x10,0x18,0x14,0x52,0x7F,0x50,0x10,0x00,
    0x00,0x27,0x45,0x45,0x45,0x45,0x39,0x00,
    0x00,0x3C,0x4A,0x49,0x49,0x49,0x30,0x00,
    0x00,0x03,0x01,0x71,0x09,0x05,0x03,0x00,
    0x00,0x36,0x49,0x49,0x49,0x49,0x36,0x00,
    0x00,0x06,0x49,0x49,0x49,0x29,0x1E,0x00,
    0x00,0x00,0x00,0x66,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x66,0x00,0x00,0x00,0x00,
    0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00,
    0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x00,
    0x00,0x00,0x00,0x41,0x22,0x14,0x08,0x00,
    0x00,0x02,0x01,0x01,0x51,0x09,0x06,0x00,
    0x00,0x3E,0x41,0x5D,0x55,0x55,0x1E,0x00,
    0x00,0x7C,0x12,0x11,0x11,0x12,0x7C,0x00,
    0x00,0x41,0x7F,0x49,0x49,0x49,0x36,0x00,
    0x00,0x1C,0x22,0x41,0x41,0x41,0x22,0x00,
    0x00,0x41,0x7F,0x41,0x41,0x22,0x1C,0x00,
    0x00,0x41,0x7F,0x49,0x5D,0x41,0x63,0x00,
    0x00,0x41,0x7F,0x49,0x1D,0x01,0x03,0x00,
    0x00,0x1C,0x22,0x41,0x51,0x51,0x72,0x00,
    0x00,0x7F,0x08,0x08,0x08,0x08,0x7F,0x00,
    0x00,0x00,0x41,0x7F,0x41,0x00,0x00,0x00,
    0x00,0x30,0x40,0x40,0x41,0x3F,0x01,0x00,
    0x00,0x41,0x7F,0x08,0x14,0x22,0x41,0x40,
    0x00,0x41,0x7F,0x41,0x40,0x40,0x60,0x00,
    0x00,0x7F,0x01,0x02,0x04,0x02,0x01,0x7F,
    0x00,0x7F,0x01,0x02,0x04,0x08,0x7F,0x00,
    0x00,0x3E,0x41,0x41,0x41,0x41,0x3E,0x00,
    0x00,0x41,0x7F,0x49,0x09,0x09,0x06,0x00,
    0x00,0x1E,0x21,0x21,0x31,0x21,0x5E,0x40,
    0x00,0x41,0x7F,0x49,0x19,0x29,0x46,0x00,
    0x00,0x26,0x49,0x49,0x49,0x49,0x32,0x00,
    0x00,0x03,0x01,0x41,0x7F,0x41,0x01,0x03,
    0x00,0x3F,0x40,0x40,0x40,0x40,0x3F,0x00,
    0x00,0x0F,0x10,0x20,0x40,0x20,0x10,0x0F,
    0x00,0x3F,0x40,0x40,0x38,0x40,0x40,0x3F,
    0x00,0x41,0x22,0x14,0x08,0x14,0x22,0x41,
    0x00,0x01,0x02,0x44,0x78,0x44,0x02,0x01,
    0x00,0x43,0x61,0x51,0x49,0x45,0x43,0x61,
    0x00,0x7F,0x41,0x41,0x41,0x00,0x00,0x00,
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x00,
    0x00,0x41,0x41,0x41,0x7F,0x00,0x00,0x00,
    0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00,
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
    0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,
    0x00,0x20,0x54,0x54,0x54,0x54,0x78,0x40,
    0x00,0x01,0x7F,0x30,0x48,0x48,0x48,0x30,
    0x00,0x38,0x44,0x44,0x44,0x44,0x28,0x00,
    0x00,0x30,0x48,0x48,0x48,0x31,0x7F,0x40,
    0x00,0x38,0x54,0x54,0x54,0x54,0x18,0x00,
    0x00,0x00,0x48,0x7E,0x49,0x01,0x02,0x00,
    0x00,0x98,0xA4,0xA4,0xA4,0xA4,0x78,0x04,
    0x00,0x41,0x7F,0x08,0x04,0x04,0x78,0x00,
    0x00,0x00,0x44,0x7D,0x40,0x00,0x00,0x00,
    0x00,0x60,0x80,0x80,0x80,0x84,0x7D,0x00,
    0x00,0x01,0x7F,0x10,0x28,0x44,0x40,0x00,
    0x00,0x00,0x41,0x7F,0x40,0x00,0x00,0x00,
    0x00,0x7C,0x04,0x04,0x78,0x04,0x04,0x78,
    0x00,0x7C,0x08,0x04,0x04,0x04,0x78,0x00,
    0x00,0x38,0x44,0x44,0x44,0x44,0x38,0x00,
    0x00,0x84,0xFC,0x98,0x24,0x24,0x18,0x00,
    0x00,0x18,0x24,0x24,0x98,0xFC,0x84,0x00,
    0x00,0x44,0x7C,0x48,0x04,0x04,0x18,0x00,
    0x00,0x48,0x54,0x54,0x54,0x54,0x24,0x00,
    0x00,0x04,0x04,0x3F,0x44,0x44,0x20,0x00,
    0x00,0x3C,0x40,0x40,0x40,0x20,0x7C,0x00,
    0x00,0x0C,0x10,0x20,0x40,0x20,0x10,0x0C,
    0x00,0x3C,0x40,0x40,0x38,0x40,0x40,0x3C,
    0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,
    0x00,0x9C,0xA0,0xA0,0xA0,0xA0,0x7C,0x00,
    0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00,
    0x00,0x08,0x08,0x36,0x41,0x41,0x00,0x00,
    0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x00,
    0x00,0x00,0x41,0x41,0x36,0x08,0x08,0x00,
    0x00,0x02,0x01,0x01,0x02,0x02,0x01,0x00,
    0x00,0x70,0x48,0x44,0x42,0x44,0x48,0x70,
    0x00,0x0E,0x91,0x91,0xB1,0xB1,0x4A,0x00,
    0x00,0x3A,0x40,0x40,0x40,0x7A,0x40,0x00,
    0x00,0x38,0x54,0x54,0x55,0x55,0x18,0x00,
    0x00,0x22,0x55,0x55,0x55,0x79,0x42,0x00,
    0x00,0x21,0x54,0x54,0x54,0x78,0x41,0x00,
    0x00,0x20,0x55,0x55,0x54,0x78,0x40,0x00,
    0x00,0x20,0x54,0x55,0x54,0x78,0x40,0x00,
    0x00,0x18,0x24,0xA4,0xA4,0xE4,0x40,0x00,
    0x00,0x3A,0x55,0x55,0x55,0x55,0x1A,0x00,
    0x00,0x39,0x54,0x54,0x54,0x54,0x19,0x00,
    0x00,0x38,0x55,0x55,0x54,0x54,0x18,0x00,
    0x00,0x00,0x01,0x44,0x7C,0x41,0x00,0x00,
    0x02,0x01,0x45,0x7D,0x41,0x01,0x02,0x00,
    0x00,0x00,0x01,0x45,0x7C,0x40,0x00,0x00,
    0x00,0x79,0x14,0x12,0x12,0x14,0x79,0x00,
    0x00,0x70,0x28,0x2B,0x2B,0x28,0x70,0x00,
    0x00,0x44,0x7C,0x54,0x55,0x45,0x00,0x00,
    0x00,0x20,0x54,0x54,0x58,0x38,0x54,0x54,
    0x00,0x7C,0x0A,0x09,0x09,0x7F,0x49,0x49,
    0x00,0x30,0x4A,0x49,0x49,0x4A,0x30,0x00,
    0x00,0x32,0x48,0x48,0x48,0x48,0x32,0x00,
    0x00,0x30,0x49,0x4A,0x48,0x48,0x30,0x00,
    0x00,0x38,0x42,0x41,0x41,0x42,0x38,0x00,
    0x00,0x38,0x41,0x42,0x40,0x40,0x38,0x00,
    0x00,0x1A,0xA0,0xA0,0xA0,0xA0,0x7A,0x00,
    0x00,0x19,0x24,0x42,0x42,0x24,0x19,0x00,
    0x00,0x3D,0x40,0x40,0x40,0x40,0x3D,0x00,
    0x00,0x18,0x24,0x24,0xE7,0x24,0x24,0x00,
    0x00,0x68,0x5E,0x49,0x41,0x42,0x20,0x00,
    0x00,0x15,0x16,0x7C,0x16,0x15,0x00,0x00,
    0x81,0xFF,0x85,0x05,0x17,0xFA,0x90,0x50,
    0x40,0x88,0x88,0x7F,0x09,0x09,0x02,0x00,
    0x00,0x20,0x54,0x54,0x55,0x79,0x40,0x00,
};
