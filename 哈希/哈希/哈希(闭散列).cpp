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
		//�����ڹ�ϣ���е�λ��
		int index = data.first%_ht.size();
		//�жϼ����λ���Ƿ��Ѿ���Ԫ��
		while (_ht[index]._state == EXIST){
			//�����,�ж��Ƿ��ǵ�ǰ��Keyֵ
			if (_ht[index]._data.first == data.first)
				return false;
			//�������,index������ƶ�,Ѱ�ҿյ�λ�ý��в���
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
		//ѭ������,ֱ����Ϊֹ
		while (_ht[index]._state != EMPTY){
			//��ǰλ����ֵ,�������
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
		//����key�ڱ��е�λ��
		int index = key%_ht.size();
		//ѭ���жϵ�ǰλ���Ƿ���ֵ,�����,�ж��Ƿ���key
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
		//�����Ƿ���Ҫ����
		if ((_size * 10) / _ht.size() >= 8 || _size == 0){
			int newC =_ht.size() == 0 ? 10 : 2 * _ht.size();
			HashTable<K, V> newTable(newC);
			//���ɱ��е�ֵ�����ҵ��±��е�λ��
			int i = 0;
			while (i < _ht.size()){
				//�൱ǰλ��Ϊ�ջ���ɾ�������
				if (_ht[i]._state == EXIST)
					newTable.Insert(_ht[i]._data);
				++i;
			}
			swap(_ht, newTable._ht);
		}
		//�����ֵ����80%��,����Ҫ����
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