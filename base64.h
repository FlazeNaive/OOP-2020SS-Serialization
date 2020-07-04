#ifndef BASE64_H
#define BASE64_H
#include<string>

extern const char EncodeTable[];
extern const char DecodeTable[];

std::string Encode64(std::string data);
std::string Decode64(std::string data);
#endif
