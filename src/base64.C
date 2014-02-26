
#include "base64.h"

namespace base64{

/*

uint8_t base64EncodeChars[] = { 'r', 'Y', 'K', 'p', 'w', '5', 'f', 'Z', 'P', 'h', '8', 'T', 'o', 'q', '0', 'z', 'x', '-', 'J', 'E', 'S', 'k', 'a', '9', 'H', 's', 'O', '4', 't', 'X', 'j', 'c', 'Q', '1', 'F', '6', 'L', 'v', 'l', 'W', 'R', 'b', '_', 'D', 'e', 'M', 'N', 'g', 'y', 'u', 'd', 'G', 'A', 'm', 'C', '3', 'U', 'i', '7', 'B', '2', 'V', 'I', 'n' };

uint8_t base64DecodeChars[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, 14, 33, 60, 55, 27, 5, 35, 58, 10, 23, -1, -1, -1, -1, -1, -1, -1, 52, 59, 54, 43, 19, 34, 51, 24, 62, 18, 2, 36, 45, 46, 26, 8, 32, 40, 20, 11, 56, 61, 39, 29, 1, 7, -1, -1, -1, -1, 42, -1, 22, 41, 31, 50, 44, 6, 47, 9, 57, 30, 21, 38, 53, 63, 12, 3, 13, 0, 25, 28, 49, 37, 4, 16, 48, 15, -1, 38, -1, -1, -1 };


void SohuEncodeBase64(uint8_t *src, uint32_t src_len, uint8_t *dst, uint32_t *dst_len)
{
	uint8_t	*d, *s;
	register uint32_t i = 0;
	uint32_t b1, b2, b3;

	s = src;
	d = dst;

	while (i < src_len)
	{
		b1 = s[i++] & 0xff;
		if (i == src_len)
		{
			*d++ = base64EncodeChars[b1 >> 2];
			*d++ = base64EncodeChars[(b1 & 0x3) << 4];
			break;
		}
		b2 = s[i++] & 0xff;
		if (i == src_len)
		{
			*d++ = base64EncodeChars[b1 >> 2];
			*d++ = base64EncodeChars[((b1 & 0x03) << 4) | ((b2 & 0xf0) >> 4)];
			*d++ = base64EncodeChars[(b2 & 0x0f) << 2];
			break;
		}
		b3 = s[i++] & 0xff;
		*d++ = base64EncodeChars[b1 >> 2];
		*d++ = base64EncodeChars[((b1 & 0x03) << 4) | ((b2 & 0xf0) >> 4)];
		*d++ = base64EncodeChars[((b2 & 0x0f) << 2) | ((b3 & 0xc0) >> 6)];
		*d++ = base64EncodeChars[b3 & 0x3f];
	}

	*dst_len = d - dst;
}

void SohuDecodeBase64(uint8_t *src, uint32_t src_len, uint8_t *dst, uint32_t *dst_len)
{
	register uint32_t i = 0;
	uint8_t *d, *s;

	uint32_t b1 = -1, b2 = -1, b3 = -1, b4 = -1;
	d = dst;
	s = src;
	while (i < src_len)
	{

		do {
			b1 = base64DecodeChars[s[i++]];
		} while (i < src_len && b1 == (uint32_t)-1);


		while (i < src_len)
		{
			b2 = base64DecodeChars[s[i++]];
			if (b2 != (uint32_t)-1)
			{
				*d++ = (b1 << 2) | ((b2 & 0x30) >> 4);
				break;
			}
		}


		while (i < src_len)
		{
			b3 = base64DecodeChars[s[i++]];
			if (b3 != (uint32_t)-1)
			{
				*d++ = ((b2 & 0x0f) << 4) | ((b3 & 0x3c) >> 2);
				break;
			}
		}


		while (i < src_len)
		{
			b4 = base64DecodeChars[s[i++]];
			if (b4 != (uint32_t)-1)
			{
				*d++ = ((b3 & 0x03) << 6) | b4;
				break;
			}
		}
	}

	*dst_len = d - dst;
}
*/
}
