#include<iostream>
#include<vector>
using namespace std;
template<class K,class V>
struct HashNode{
	HashNode(const pair<K,V>& data = pair<K,V>())
	:_data(data)
	, _next(nullptr)
	{}
	pair<K,V> _data;
	HashNode<K,V>* _next;
};
template<class K,class V>
class HashTable{
public:
	typedef HashNode<K,V> Node;
	typedef Node* pNode;

	HashTable(size_t n = 10){
		_ht.resize(10);
		_size = 0;
	}

	//����
	bool Insert(const pair<K,V>& data){
		HashCapacity();
		//�����ϣͰ��λ��
		int index = data.first%_ht.size();
		pNode cur = _ht[index];
		//�жϹ�ϣͰ���Ƿ��Ѿ���Ҫ�����Ԫ��
		while (cur){
			if (cur->_data.first == data.first)
				return false;
			cur = cur->_next;
		}
		//�������½ڵ�
		cur = new Node(data);
		//ͷ��
		cur->_next = _ht[index];
		_ht[index] = cur;
		++_size;
		return true;
	}

	//����
	pNode Find(const K& key){
		//��������,�ҵ��ڱ�Ͱ��λ��
		int index = key % _ht.size();
		pNode cur = _ht[index];
		while (cur){
			if (cur->_data.first == key)
				return cur;
			cur = cur->_next;
		}
		return nullptr;
	}
	//ɾ��
	bool Erase(const K& key){
		int index = key%_ht.size();
		pNode cur = _ht[index];
		pNode prev = nullptr;
		while (cur){
			if (cur->_data.first == key){
				if (prev == nullptr)
					_ht[index] = nullptr;
				else
					prev->_next = cur->_next;
				delete cur;
				cur = nullptr;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
		return false;
	}
private:
	//��ϣͰ������
	void HashCapacity(){
		//�����Ƿ���Ҫ����
		if (_size == _ht.size()){
			int newC = _size == 0 ? 10 : 2 * _ht.size();
			//�������±�
			vector<pNode> newT;
			newT.resize(newC);
			//���ɱ��е�����Ԫ�ط��뵽�±���
			for (size_t i = 0; i < _ht.size(); i++){
				pNode cur = _ht[i];
				//����һ��Ͱ�е����ҽڵ�
				while (cur){
					pNode next = cur->_next;
					int index = cur->_data.first % newT.size();
					cur->_next = newT[index];
					newT[index] = cur;
					cur = next;
				}
				_ht[i] = nullptr;
			}
			swap(_ht, newT);
		}
	}
	//��ϣ��ı�ͷ��������ͷ
	vector<pNode> _ht;
	size_t _size;
};

void testHashTable()
{
	HashTable<int, int> _ht;
	_ht.Insert(make_pair(1, 1));
	_ht.Insert(make_pair(3, 3));
	_ht.Insert(make_pair(6, 6));
	_ht.Insert(make_pair(0, 0));
	_ht.Insert(make_pair(10, 10));
	_ht.Insert(make_pair(13, 13));
	_ht.Insert(make_pair(16, 16));
	_ht.Insert(make_pair(11, 11));
	_ht.Insert(make_pair(14, 14));
	_ht.Insert(make_pair(15, 15));
	//_ht.Insert(make_pair(9, 9));
	// 1 , 11       3, 13    6 16  0 10       2
	_ht.Erase(11);  
	_ht.Erase(6);
	_ht.Erase(2);
}

int main()
{

	testHashTable();
	system("pause");
	return 0;
}