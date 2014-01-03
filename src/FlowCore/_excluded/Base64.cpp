// -----------------------------------------------------------------------------
//  File        Base64.cpp
//  Project     FlowCore
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/10/20 $
// -----------------------------------------------------------------------------

#include "FlowCore/Base64.h"
#include "FlowCore/MemoryTracer.h"

// Source:
// http://base64.sourceforge.net/b64.c

// -----------------------------------------------------------------------------
//  Class FBase64
// -----------------------------------------------------------------------------

// Static members --------------------------------------------------------------

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char cd64[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

static void encodeBlock(uint8_t* inBuf, uint8_t* outBuf, int len)
{
	outBuf[0] = (uint8_t) cb64[ (int)(inBuf[0] >> 2) ];
	outBuf[1] = (uint8_t) cb64[ (int)(((inBuf[0] & 0x03) << 4) | ((inBuf[1] & 0xf0) >> 4)) ];
	outBuf[2] = (uint8_t) (len > 1 ? cb64[ (int)(((inBuf[1] & 0x0f) << 2) | ((inBuf[2] & 0xc0) >> 6)) ] : '=');
	outBuf[3] = (uint8_t) (len > 2 ? cb64[ (int)(inBuf[2] & 0x3f) ] : '=');
}

static void decodeBlock(uint8_t* inBuf, uint8_t* outBuf)
{   
	outBuf[0] = (uint8_t) (inBuf[0] << 2 | inBuf[1] >> 4);
	outBuf[1] = (uint8_t) (inBuf[1] << 4 | inBuf[2] >> 2);
	outBuf[2] = (uint8_t) (((inBuf[2] << 6) & 0xc0) | inBuf[3]);
}

string_t FBase64::encode(const uint8_t* pData, size_t length, int lineSize /* = 256 */)
{
	uint8_t inBuf[3];
	uint8_t outBuf[4];
	int i, len, blocksout = 0;
	int retcode = 0;

	*inBuf = (uint8_t) 0;
	*outBuf = (uint8_t) 0;

	std::ostringstream oStream;
	oStream << "\"";

	size_t pos = 0;
	while(pos < length)
	{
		len = 0;
		for (i = 0; i < 3; i++) {
			if (pos < length) {
				inBuf[i] = pData[pos++];
				len++;
			}
			else {
				inBuf[i] = uint8_t(0);
			}
		}

		if (len > 0) {
			encodeBlock(inBuf, outBuf, len);
			for (i = 0; i < 4; i++) {
				oStream << outBuf[i];
			}
			blocksout++;
		}

		if (blocksout >= (lineSize / 4) || pos >= length) {
			oStream << "\"";
			if (pos < length)
				oStream << ",\n\"";
			blocksout = 0;
		}
	}

	return oStream.str();
}

bool FBase64::decode(const string_t encodedData, uint8_t* pBuffer, size_t bufLength)
{
	int retcode = 0;
	uint8_t in[4];
	uint8_t out[3];
	int v;
	int i, len;

	*in = (uint8_t) 0;
	*out = (uint8_t) 0;

	std::istringstream iStream(encodedData);
	size_t pos = 0;

	while(!iStream.eof())
	{
		for (len = 0, i = 0; i < 4 && !iStream.eof(); i++)
		{
			v = 0;
			while(!iStream.eof() && v == 0) {
				char c;
				iStream.get(c);
				v = (int)c;
				v = ((v < 43 || v > 122) ? 0 : (int) cd64[ v - 43 ]);
				if( v != 0 ) {
					v = ((v == (int)'$') ? 0 : v - 61);
				}
			}
			if(!iStream.eof())
			{
				len++;
				if( v != 0 ) {
					in[ i ] = (uint8_t) (v - 1);
				}
			}
			else {
				in[i] = (uint8_t) 0;
			}
		}
		if (len > 0)
		{
			decodeBlock(in, out);
			for (i = 0; i < len - 1; i++) {
				pBuffer[pos++] = out[i];
				if (pos >= bufLength)
					return false;
			}
		}
	}

	return true;
}


// -----------------------------------------------------------------------------