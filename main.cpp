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
	cout <<  "USER_DEFINED (TYPE_CAR): \n\t" ;\
	cout << "ID = " <<  CAR[X].ID << "\n\towner = " << CAR[X].owner << "\n\tdist = " << CAR[X].dist << "\n\tage = " << CAR[X].age ;\
	cout << endl ;

#include"binary.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
#include<list>
#include<set>
#include<map>

using namespace std ;

//==========================================================================================
//==================== User-Defined ========================================================
struct TYPE_CAR {
	string ID, owner;
	int dist, age;
	TYPE_CAR() {}
	TYPE_CAR(string ID, string owner, int dist, int age) :
		ID(ID), owner(owner), dist(dist), age(age) {}
};
void serialize(struct TYPE_CAR data, fstream &OUT) {
	serialize(data.ID, OUT);
	serialize(data.owner, OUT);
	serialize(data.dist, OUT);
	serialize(data.age, OUT);
}
void deserialize(struct TYPE_CAR &data, fstream &IN) {
	deserialize(data.ID, IN);
	deserialize(data.owner, IN);
	deserialize(data.dist, IN);
	deserialize(data.age, IN);
}
//==========================================================================================

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

	struct TYPE_CAR CAR[2];
	CAR[0] = TYPE_CAR("ABC01", "someone", 10238, 7);

//==========================================================================================

	PRINT(0)
	cout << endl << endl ;

//==========================================================================================

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

	OUT.open("type-car.data", ios::out | ios::binary);
	serialize(CAR[0], OUT) ;	
	OUT.close();

//==========================================================================================

	cout << "serilization done\n\n";

//==========================================================================================

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

	IN.open("type-car.data", ios::in | ios::binary);
	deserialize(CAR[1], IN) ;	
	IN.close();

//==========================================================================================

	PRINT(1) ;

//==========================================================================================

	return 0 ;
}
