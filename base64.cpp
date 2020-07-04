#include"base64.h"

const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char DecodeTable[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    62, // '+'
    0, 0, 0,
    63, // '/'
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
    0, 0, 0, 0, 0, 0,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
};

std::string Encode64(std::string data) {
	std::string rtn;
	unsigned char tmp[3] = { 0 };
	int len = data.size();
	for (int i = 0; i < ((int)(len / 3)) * 3; ) {
		tmp[0] = data[i++];
		tmp[1] = data[i++];
		tmp[2] = data[i++];
		rtn += EncodeTable[tmp[0] >> 2];
		rtn += EncodeTable[((tmp[0] << 4) | (tmp[1] >> 4)) & 0x3f];
		rtn += EncodeTable[((tmp[1] << 2) | (tmp[2] >> 6)) & 0x3f];
		rtn += EncodeTable[tmp[2] & 0x3f];
	}
	switch (len % 3) {
		case 1: {
			tmp[0] = data[len - 1];
			rtn += EncodeTable[(tmp[0] & 0xfc) >> 2];
			rtn += EncodeTable[((tmp[0] & 0x03) << 4)];
			rtn += "==";
			break;
		}
		case 2: {
			tmp[0] = data[len - 2];
			tmp[1] = data[len - 1];
			rtn += EncodeTable[(tmp[0] & 0xfc) >> 2];
			rtn += EncodeTable[((tmp[0] & 0x03) << 4) | ((tmp[1] & 0xf0) >> 4)];
			rtn += EncodeTable[((tmp[1] & 0x0f) << 2)];
			rtn += "=";
			break;
		}
		default :
			break ;
	}
	return rtn;
}

std::string Decode64(std::string data) {
	std::string rtn;
	int len = data.size();
	for (int i = 0; i < len; ) {
		int tmp = DecodeTable[data[i++]] << 18;
		tmp += DecodeTable[data[i++]] << 12;
		rtn += (tmp & 0x00ff0000) >> 16;

		if (data[i] != '=') {
			tmp += DecodeTable[data[i++]] << 6;
			rtn += (tmp & 0x0000ff00) >> 8;

			if (data[i] != '=') {
				tmp += DecodeTable[data[i++]];
				rtn += tmp & 0x000000ff;
			} else
				++i ;
		} else
			i += 2 ;
	}
	return rtn ;
}
