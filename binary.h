#ifndef BINARY_H
#define BINARY_H
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<set>
#include<map>

namespace binary_serialize {

//====================================================================================================
//==================== Concept Definition ============================================================
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
//====================================================================================================
//==================== Arithmetic ====================================================================
template<IsNumber T>
void serialize(T data, std::fstream &OUT) {
	//std::fstream OUT(FILENAME, ios::out | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	memcpy(TMP, &data, sizeof(data)) ;
	OUT.write(TMP, sizeof(TMP)) ;
}
template<IsNumber T>
void deserialize(T &data, std::fstream &IN) {
	//std::fstream IN(FILENAME, ios::in | ios::binary) ;	
	char *TMP = new char[sizeof(T)] ;
	IN.read(TMP, sizeof(TMP)) ;
	memcpy(&data, TMP, sizeof(data)) ;
}

//====================================================================================================
//==================== String ========================================================================
void serialize(std::string data, std::fstream& OUT);
void deserialize(std::string& data, std::fstream& IN);

//====================================================================================================
//==================== Vector & List =================================================================
template<IsLinear Container>
void serialize(Container data, std::fstream &OUT) {
	typedef typename Container::value_type T;
	int siz = data.size();
	serialize(siz, OUT);
	for (auto &i : data)
		serialize(i, OUT);
}

template<IsLinear Container>
void deserialize(Container &data, std::fstream &IN){
	typedef typename Container::value_type T;
	int siz;
	deserialize(siz, IN);

	for ( int i = 0; i < siz; ++i ) {
		T cur;	
		deserialize(cur, IN);
		data.push_back(cur);
	}
}

//====================================================================================================
//==================== Set ===========================================================================
template<IsSet Container>
void serialize(Container data, std::fstream &OUT){
	typedef typename Container::value_type T;
	int siz = data.size();
	serialize(siz, OUT);
	for (auto &i : data)
		serialize(i, OUT);
}

template<IsSet Container>
void deserialize(Container &data, std::fstream &IN){
	typedef typename Container::value_type T;
	int siz;
	deserialize(siz, IN);
	for ( int i = 0; i < siz; ++i ) {
		T cur;	
		deserialize(cur, IN);
		data.insert(cur) ;
	}
}

//====================================================================================================
//==================== Pair ==========================================================================
template<IsPair Container>
void serialize(Container data, std::fstream& OUT) {
	serialize(data.first, OUT);
	serialize(data.second, OUT);
}
template<IsPair Container>
void deserialize(Container &data, std::fstream& IN) {
	typedef typename Container::first_type T1;
	typedef typename Container::second_type T2;
	T1 x1;
	T2 x2;
	deserialize(x1, IN);
	deserialize(x2, IN);
	data = make_pair(x1, x2);
}
//====================================================================================================
//==================== Map ===========================================================================
template<IsMap Container>
void serialize(Container data, std::fstream& OUT) {
	int siz = data.size();
	serialize(siz, OUT);
	for (auto it : data)
		serialize(it, OUT);
}
template<IsMap Container>
void deserialize(Container &data, std::fstream& IN) {
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
//====================================================================================================

}
#endif
