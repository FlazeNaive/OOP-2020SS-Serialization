# **Object** Serialization

Final project for OOP during 2020 SS semester. 

It uses some features (concept)  of C++20 standard. You can compile it with VisualStudio2019 or the latest version of g++. 

## Function

Binary serialization and xml serialization. 

Base64 decoding of data. 

## How to Use

We provide functions for serialization and deserialization, and the usage example is shown in **main.cpp**. 

### Binary serialization

When using it, call the function as below. 

```c++
serialize(T data, fstream& OUT);
deserialize(T &data, fstream& IN);
```

It support the serialization of arithmetic types, C++ string type, and STL containers. And for the user-defined type, it can be easily used as shown in main. 

```c++
struct TYPE_CAR {
	string ID;
	vector<string> owner;
	int dist, age;
	TYPE_CAR() {}
	TYPE_CAR(string ID, int dist, int age) :
		ID(ID), dist(dist), age(age) {}
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
```

### XML serialization



## Task-Division

He Qingyi (3180105438): Binary serialization, Base64 encoding module. 

