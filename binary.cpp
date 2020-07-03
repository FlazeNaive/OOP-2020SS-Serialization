#define PRINT(X) cout << INT[X] << endl << FLO[X] << endl << BOO[X] << endl << STR[X] << endl ;\
	copy(VEC[X].begin(),VEC[X].end(),ostream_iterator<int   >(cout," "));\
	cout << endl ;\
	for ( auto i : LIS[X] )\
		cout << i << ' ' ; \
	cout << endl ;\
	for ( auto i : SET[X] )\
		cout << i << ' ' ; \
	cout << endl ;
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
#include<list>
#include<set>
#include<map>

using namespace std ;

//============================================================
//==================== Concept Definition ====================
template<typename T>
concept IsNumber = std::is_arithmetic<T>::value;

template<typename Container>
concept IsLinear = std::is_same<Container, std::vector<typename Container::value_type>>::value ||
		   std::is_same<Container, std::list<typename Container::value_type>>::value;

template<typename Container>
concept IsSet = std::is_same<Container, std::set<typename Container::value_type>>::value;

//============================================================
//==================== Arithmetic ============================
template<IsNumber T>
void serialize(T data, const char* FILENAME) {
	fstream OUT(FILENAME, ios::out | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	memcpy(TMP, &data, sizeof(data)) ;
	OUT.write(TMP, sizeof(TMP)) ;
}
template<IsNumber T>
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
	OUT.write(TMP, data.size() + 1) ;
}
void deserialize(string &data, const char* FILENAME) {
	fstream IN(FILENAME, ios::in | ios::binary) ;	
	data.clear() ;
	char cur ;
	IN.read(&cur, sizeof(cur)) ;
	while ( !IN.eof() ) {
		data += cur ;
		IN.read(&cur, sizeof(cur)) ;
	}
}

//============================================================
//==================== Vector & List =========================
template<IsLinear Container>
void serialize(Container data, const char* FILENAME) {
	fstream OUT(FILENAME, ios::out | ios::binary) ;	
	typedef typename Container::value_type T;
	char* TMP_SIZE = new char[sizeof(int)];
	for (auto &i : data) {
		int curSize = sizeof(i);
		memcpy(TMP_SIZE, &curSize, sizeof(int));
		OUT.write(TMP_SIZE, sizeof(int));

		char* TMP = new char[curSize];
		memcpy(TMP, &i, curSize);
		OUT.write(TMP, curSize);
	}
}

template<IsLinear Container>
void deserialize(Container &data, const char* FILENAME) {
	fstream IN(FILENAME, ios::in | ios::binary) ;	
	typedef typename Container::value_type T;
	
	char* TMP_SIZE = new char[sizeof(int)];
	int curSize;

	IN.read(TMP_SIZE, sizeof(int)) ;
	memcpy(&curSize, TMP_SIZE, sizeof(int)) ;
	while ( !IN.eof() ) {
		char* TMP = new char[curSize];
		T cur;	
		IN.read(TMP, curSize) ;
		memcpy(&cur, TMP, curSize);
		data.push_back(cur) ;

		IN.read(TMP_SIZE, sizeof(int)) ;
		memcpy(&curSize, TMP_SIZE, sizeof(int)) ;
	}
}

//============================================================
//==================== Set ===================================
template<IsSet Container>
void serialize(Container data, const char* FILENAME) {
	fstream OUT(FILENAME, ios::out | ios::binary) ;	
	typedef typename Container::value_type T;
	char* TMP_SIZE = new char[sizeof(int)];
	for (auto &i : data) {
		int curSize = sizeof(i);
		memcpy(TMP_SIZE, &curSize, sizeof(int));
		OUT.write(TMP_SIZE, sizeof(int));

		char* TMP = new char[curSize];
		memcpy(TMP, &i, curSize);
		OUT.write(TMP, curSize);
	}
}

template<IsSet Container>
void deserialize(Container &data, const char* FILENAME) {
	fstream IN(FILENAME, ios::in | ios::binary) ;	
	typedef typename Container::value_type T;
	
	char* TMP_SIZE = new char[sizeof(int)];
	int curSize;

	IN.read(TMP_SIZE, sizeof(int)) ;
	memcpy(&curSize, TMP_SIZE, sizeof(int)) ;
	while ( !IN.eof() ) {
		char* TMP = new char[curSize];
		T cur;	
		IN.read(TMP, curSize) ;
		memcpy(&cur, TMP, curSize);
		data.insert(cur) ;

		IN.read(TMP_SIZE, sizeof(int)) ;
		memcpy(&curSize, TMP_SIZE, sizeof(int)) ;
	}
}



int main() {
	int INT[2] = {7, 0} ;
	float FLO[2] = {float(3.27), float(0)} ;
	bool BOO[2] = {1, 0} ;
	string STR[2] = {"RUARUA", ""} ;
	vector<int> VEC[2] ;
	for ( int i = 1; i <= 3; ++i )
		VEC[0].push_back(i) ;
	list<float> LIS[2];
	for (float i = 0.1; i < 1; i += 0.2)
		LIS[0].push_back(i);
	set<float> SET[2];
	for (float i = 99; i < 101; i += 0.624)
		SET[0].insert(i);

	PRINT(0)
	cout << endl << endl ;

	serialize(INT[0], "int.data") ;	
	serialize(FLO[0], "float.data") ;	
	serialize(BOO[0], "bool.data") ;	
	serialize(STR[0], "string.data") ;	
	serialize(VEC[0], "vector.data") ;
	serialize(LIS[0], "list.data") ;	
	serialize(SET[0], "set.data") ;	

	cout << "serilization done\n\n";

	deserialize(INT[1], "int.data") ;
	deserialize(FLO[1], "float.data") ;
	deserialize(BOO[1], "bool.data") ;	
	deserialize(STR[1], "string.data") ;	
	deserialize(VEC[1], "vector.data") ;
	deserialize(LIS[1], "list.data") ;	
	deserialize(SET[1], "set.data") ;	

	PRINT(1) ;

	return 0 ;
}
