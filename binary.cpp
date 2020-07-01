#define PRINT(X) cout << INT[X] << endl << FLO[X] << endl << BOO[X] << endl << S[X] << endl
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<set>
#include<map>

using namespace std ;

//============================================================
//==================== Arithmetic ============================
template<typename T>
void serialize(T data, const char* FILENAME) {
	fstream OUT(FILENAME, ios::out | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	memcpy(TMP, &data, sizeof(data)) ;
	OUT.write(TMP, sizeof(TMP)) ;
}
template<typename T>
void deserialize(T &data, const char* FILENAME) {
	fstream IN(FILENAME, ios::in | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	IN.read(TMP, sizeof(TMP)) ;
	memcpy(&data, TMP, sizeof(data)) ;
}

//============================================================
//==================== String ================================
void serialize(string data, const char* FILENAME) ;
void deserialize(string &data, const char* FILENAME) ;

void serialize(string data, const char* FILENAME) {
	fstream OUT(FILENAME, ios::out | ios::binary) ;	
	const char *TMP = new char[data.size() + 1] ;
	TMP = data.c_str() ;
	OUT.write(TMP, sizeof(TMP)) ;
}
void deserialize(string &data, const char* FILENAME) {
	fstream IN(FILENAME, ios::in | ios::binary) ;	
	data.clear() ;
	char cur ;
	while ( !IN.eof() ) {
		IN.read(&cur, sizeof(cur)) ;
		data += cur ;
	}
}

//============================================================
//==================== Vector ================================



int main() {
	int INT[2] = {7, 0} ;
	float FLO[2] = {3.27, 0} ;
	bool BOO[2] = {1, 0} ;
	string S[2] = {"RUARUA", ""} ;
	PRINT(0) ;
	cout << endl ;

	serialize(INT[0], "int.data") ;	
	serialize(FLO[0], "float.data") ;	
	serialize(BOO[0], "bool.data") ;	
	serialize(S[0], "string.data") ;	

	deserialize(INT[1], "int.data") ;
	deserialize(FLO[1], "float.data") ;
	deserialize(BOO[1], "bool.data") ;	
	deserialize(S[1], "string.data") ;	

	PRINT(1) ;

	return 0 ;
}
