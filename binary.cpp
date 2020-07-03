#define PRINT(X) cout << INT[X] << endl << FLO[X] << endl << BOO[X] << endl << STR[X] << endl << "\nVECTOR: \n\t";\
	copy(VEC[X].begin(),VEC[X].end(),ostream_iterator<int   >(cout," "));\
	cout << endl << "LIST: \n\t";\
	for ( auto i : LIS[X] )\
		cout << i << ' ' ; \
	cout << endl << "SET: \n\t" ;\
	for ( auto i : SET[X] )\
		cout << i << ' ' ; \
	cout << endl << "PAIR: \n\t" << PAI[X].first << ' ' << PAI[X].second;\
	cout << endl << "MAP: \n" ;\
	for ( auto i : MAP[X] )\
		cout << "\tMAP[" << i.first << "] = " << i.second << '\n' ; \
	cout << endl ;

#include<iostream>
#include<fstream>
#include<sstream>
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

template<typename Container>
concept IsPair = std::is_same<Container,
			      std::pair<typename Container::first_type,
					typename Container::second_type>>::value;
template<typename Container>
concept IsMap = std::is_same<Container,
			     std::map<typename Container::key_type,
				      typename Container::mapped_type>>::value;
//============================================================
//==================== Arithmetic ============================
template<IsNumber T>
void serialize(T data, fstream &OUT) {
	//fstream OUT(FILENAME, ios::out | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	memcpy(TMP, &data, sizeof(data)) ;
	OUT.write(TMP, sizeof(TMP)) ;
}
template<IsNumber T>
void deserialize(T &data, fstream &IN) {
	//fstream IN(FILENAME, ios::in | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	IN.read(TMP, sizeof(TMP)) ;
	memcpy(&data, TMP, sizeof(data)) ;
}

//============================================================
//==================== String ================================
void serialize(string data, fstream& OUT);
void deserialize(string& data, fstream& IN);

void serialize(string data, fstream& OUT) {
	int len = data.size() + 1;
	serialize(len, OUT);
	for (int i = 0; i < len; ++i)
		serialize(data[i], OUT);
}
void deserialize(string& data, fstream& IN){
	int len;
	deserialize(len, IN);
	cout << "len = " << len << endl;
	data.clear() ;
	for ( int i = 0; i < len; ++i ) {
		char cur ;
		deserialize(cur, IN);
		data += cur ;
	}
	data.pop_back();
	cout << "STR : " << data << endl;
}

//============================================================
//==================== Vector & List =========================
template<IsLinear Container>
void serialize(Container data, fstream &OUT) {
	typedef typename Container::value_type T;
	int siz = data.size();
	serialize(siz, OUT);
	for (auto &i : data)
		serialize(i, OUT);
}

template<IsLinear Container>
void deserialize(Container &data, fstream &IN){
	typedef typename Container::value_type T;
	int siz;
	deserialize(siz, IN);

	for ( int i = 0; i < siz; ++i ) {
		T cur;	
		deserialize(cur, IN);
		data.push_back(cur);
	}
}

//============================================================
//==================== Set ===================================
template<IsSet Container>
void serialize(Container data, fstream &OUT){
	typedef typename Container::value_type T;
	int siz = data.size();
	serialize(siz, OUT);
	for (auto &i : data)
		serialize(i, OUT);
}

template<IsSet Container>
void deserialize(Container &data, fstream &IN){
	typedef typename Container::value_type T;
	int siz;
	deserialize(siz, IN);
	for ( int i = 0; i < siz; ++i ) {
		T cur;	
		deserialize(cur, IN);
		data.insert(cur) ;
	}
}

//============================================================
//==================== Pair ==================================
template<IsPair Container>
void serialize(Container data, fstream& OUT) {
	serialize(data.first, OUT);
	serialize(data.second, OUT);
}
template<IsPair Container>
void deserialize(Container &data, fstream& IN) {
	typedef typename Container::first_type T1;
	typedef typename Container::second_type T2;
	T1 x1;
	T2 x2;
	deserialize(x1, IN);
	deserialize(x2, IN);
	data = make_pair(x1, x2);
}
//============================================================
//==================== Map ===================================
template<IsMap Container>
void serialize(Container data, fstream& OUT) {
	int siz = data.size();
	serialize(siz, OUT);
	for (auto it : data)
		serialize(it, OUT);
}
template<IsMap Container>
void deserialize(Container &data, fstream& IN) {
	typedef typename Container::key_type T1;
	typedef typename Container::mapped_type T2;
	int siz;
	T1 x1;
	T2 x2;
	data.clear();
	deserialize(siz, IN);
	for (int i = 0; i < siz; ++i) {
		deserialize(x1, IN);
		deserialize(x2, IN);
		data[x1] = x2;
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

	list<string> LIS[2];
	string tmpstr = "Ceeeeb";
	for (int i = 1; i <= 3; ++i) {
		tmpstr = tmpstr + "!";
		LIS[0].push_back(tmpstr);
	}

	set<float> SET[2];
	for (float i = 99; i < 101; i += 0.624)
		SET[0].insert(i);

	pair<string, int> PAI[2];
	PAI[0] = make_pair("PAIR_FIRST", 2);
	
	map<string, double> MAP[2];
	MAP[0]["eleven"] = 11;
	MAP[0]["thousand"] = 1000;


	PRINT(0)
	cout << endl << endl ;



	fstream OUT;
	OUT.open("int.data", ios::out | ios::binary);
	serialize(INT[0], OUT) ;	
	OUT.close();
	OUT.open("float.data", ios::out | ios::binary);
	serialize(FLO[0], OUT) ;	
	OUT.close();
	OUT.open("bool.data", ios::out | ios::binary);
	serialize(BOO[0], OUT) ;	
	OUT.close();
	OUT.open("string.data", ios::out | ios::binary);
	serialize(STR[0], OUT) ;	
	OUT.close();
	OUT.open("vector.data", ios::out | ios::binary);
	serialize(VEC[0], OUT) ;
	OUT.close();
	OUT.open("list.data", ios::out | ios::binary);
	serialize(LIS[0], OUT) ;	
	OUT.close();
	OUT.open("set.data", ios::out | ios::binary);
	serialize(SET[0], OUT) ;	
	OUT.close();
	OUT.open("pair.data", ios::out | ios::binary);
	serialize(PAI[0], OUT) ;	
	OUT.close();
	OUT.open("map.data", ios::out | ios::binary);
	serialize(MAP[0], OUT) ;	
	OUT.close();

	cout << "serilization done\n\n";

	fstream IN;
	IN.open("int.data", ios::in | ios::binary);
	deserialize(INT[1], IN) ;
	IN.close();
	IN.open("float.data", ios::in | ios::binary);
	deserialize(FLO[1], IN) ;
	IN.close();
	IN.open("bool.data", ios::in | ios::binary);
	deserialize(BOO[1], IN) ;	
	IN.close();
	IN.open("string.data", ios::in | ios::binary);
	deserialize(STR[1], IN) ;	
	IN.close();
	IN.open("vector.data", ios::in | ios::binary);
	deserialize(VEC[1], IN) ;
	IN.close();
	IN.open("list.data", ios::in | ios::binary);
	deserialize(LIS[1], IN) ;	
	IN.close();
	IN.open("set.data", ios::in | ios::binary);
	deserialize(SET[1], IN) ;	
	IN.close();
	IN.open("pair.data", ios::in | ios::binary);
	deserialize(PAI[1], IN) ;	
	IN.close();
	IN.open("map.data", ios::in | ios::binary);
	deserialize(MAP[1], IN) ;	
	IN.close();

	PRINT(1) ;

	return 0 ;
}
