#include<iostream>
#include<vector>
using namespace std;
//��¡������
template <class T>
class BoomFilter{

public:
	BoomFilter(size_t number){
		_bs(number * 5)
	}
	void Set(const T& data){

	}
private:
	vector<int> _bs;
};