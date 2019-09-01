#include<iostream>
#include<vector>
using namespace std;
enum STATE{
	EMPTY, EXIST, DELETE
};
template<class K, class V>
struct HashNode{
	pair<K, V> _data;
	STATE _state = EMPTY;
};

template<class K, class V>
class HashTable{
public:
	typedef HashNode<K, V> Node;
	HashTable(const int n = 10){
		_ht.resize(n);
		_size = 0;
	}

	bool Insert(const pair<K, V>& data){
		HashCapacity();
		//机算在哈希表中的位置
		int index = data.first%_ht.size();
		//判断计算的位置是否已经有元素
		while (_ht[index]._state == EXIST){
			//如果有,判断是否是当前的Key值
			if (_ht[index]._data.first == data.first)
				return false;
			//如果不是,index向后以移动,寻找空的位置进行插入
			index++;
			if (index == _ht.size())
				index = 0;
		}
		_ht[index]._data = data;
		_ht[index]._state = EXIST;
		_size++;
		return true;
	}
	
	Node* Find(const K& key){
		int index = key % _ht.size();
		//循环查找,直到空为止
		while (_ht[index]._state != EMPTY){
			//当前位置有值,并且相等
			if (_ht[index]._state == EXIST){
				if (_ht[index]._data.first == key)
					return &_ht[index];
			}

			++index;
			if (index == _ht.size())
				index = 0;
		}
		return false;
	}

	bool Esert(const K& key){
		//计算key在表中的位置
		int index = key%_ht.size();
		//循环判断当前位置是否有值,如果有,判断是否是key
		while (_ht[index] != EMPTY){
			if (_ht[index]._data.first == key){
				_ht[index]._state == DELETE;
				--_size;
				return true;
			}
			++index;
			if (index == _ht.size())
				index = 0;
		}
		return false;
	}
private:

	void HashCapacity(){
		//计算是否需要扩容
		if ((_size * 10) / _ht.size() >= 8 || _size == 0){
			int newC =_ht.size() == 0 ? 10 : 2 * _ht.size();
			HashTable<K, V> newTable(newC);
			//将旧表中的值依次找到新表中的位置
			int i = 0;
			while (i < _ht.size()){
				//多当前位置为空或者删除向后走
				if (_ht[i]._state == EXIST)
					newTable.Insert(_ht[i]._data);
				++i;
			}
			swap(_ht, newTable._ht);
		}
		//当存的值少于80%是,不需要增容
		else
			return;
	}

	vector<Node> _ht;
	size_t _size;
};
void testhash2()
{
	HashTable<int, int>  ht;
	ht.Insert(make_pair(5, 5));
	ht.Insert(make_pair(1, 1));
	ht.Insert(make_pair(0, 0));
	ht.Insert(make_pair(10, 10));
	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(30, 30));
	ht.Insert(make_pair(32, 32));
	ht.Insert(make_pair(8, 8));
   	ht.Insert(make_pair(110, 110));
	ht.Insert(make_pair(23, 23));

	HashTable<int, int>::Node* pos = ht.Find(110);
	pos = ht.Find(130);
}

int main()
{
	testhash2();
	return 0;
}