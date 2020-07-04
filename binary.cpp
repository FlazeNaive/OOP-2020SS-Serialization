#include"binary.h"

namespace binary_serialize {
//============================================================
//==================== String ================================

void serialize(std::string data, std::fstream& OUT) {
	int len = data.size() + 1;
	serialize(len, OUT);
	for (int i = 0; i < len; ++i)
		serialize(data[i], OUT);
}
void deserialize(std::string& data, std::fstream& IN){
	int len;
	deserialize(len, IN);
	data.clear() ;
	for ( int i = 0; i < len; ++i ) {
		char cur ;
		deserialize(cur, IN);
		data += cur ;
	}
	data.pop_back();
}
}
