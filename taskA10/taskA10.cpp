#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <deque>
#include <ctime>
using namespace std;

/*
����� ����� �� K ����������� ��� �����, � �� V - ��� ��������
� ������ ������������ ���������, ��� ������� �������� "<"
�.�. ���� � - �� ���������� ��� ������, �, ��������, ���������, �� ��� ������ ����������� �������� ������.
*/

template<typename K, typename V>
struct node {
	K key; //����
	V value; //��������
	node *parent = NULL; //��������� �� ��������
	node *left = NULL, *right = NULL; //��������� �� ����� � ������ ���������
	
	//����������� �� ���������
	node(){

	}

	//�����������
	node(K key, V value, node<K, V> *parent = NULL, node<K, V> *left = NULL, node<K, V> *right = NULL){
		this->key = key;
		this->value = value;
		this->parent = parent;
		this->left = left;
		this->right = right;
	}
};

template<typename K, typename V>
class tree{
	public:
		tree(); //�����������
		void insert(const K, const V); //������� ����
		node<K, V>* max(const node<K, V>*); //���� ��������� � ������������ ��������� �����
		node<K, V>* min(const node<K, V>*); //���� ��������� � ����������� ��������� �����
		void walk(const node<K, V>*); //����� ������ � ������������� �������
		node<K, V>* get_root(); //���������� ������ ������
	private:
		node<K, V> *root;
};

template<typename K, typename V>
tree<K, V>::tree(){
	root = NULL; //���������� ������ ����� -> ����� ���
}

template<typename K, typename V>
void tree<K, V>::insert(const K key, const V val){
	node<K, V>* nd = new node<K, V>(key, val); //������� ����
	if (root == NULL){ //���� ������ ����� - �� ������� ������
		root = nd;
		return;
	}
	node<K, V>* r = root;
	while (r != NULL){ //���� �� ���������� �� ����
		if (nd->key > r->key){ // ���� ���� ������ ��������
			if (r->right != NULL) //���� �� ���� - ����������
				r = r->right; // ��� ������
			else{
				nd->parent = r; // ���� ���� - ���������
				r->right = nd;
				break;
			}
		}
		else if (nd->key <= r->key){ //���� ���� ������
			if (r->left != NULL) // ���� ����
				r = r->left; // ��� �����
			else{
				nd->parent = r; //����� ���������
				r->left = nd;
				break;
			}
		}
	}
	return;
}

template<typename K, typename V>
node<K, V>* tree<K, V>::max(const node<K, V> *n){
	node<K, V> z = *n; //�������� � ��������� ���������� ����
	while (z.right != NULL) //���� �� ����� �� ����� - ��� � ������ ���������
		z = *z.right;
	return &z;
}

template<typename K, typename V>
node<K, V>* tree<K, V>::min(const node<K, V> *n){
	node<K, V> z = *n; //�������� � ��������� ���������� ����
	while (z.left != NULL) //���� �� ����� �� ����� - ��� � ����� ���������
		z = *z.left;
	return &z;
}

template<typename K, typename V> 
node<K, V>* tree<K, V>::get_root(){
	return root;
}

template<typename K, typename V>
void tree<K, V>::walk(const node<K, V>* n){
	if (n != NULL){
		node<K, V> z = *n; //�������� ���� � ��������� ����������
		walk(z.left); //���������� ��� �� ������ ���������
		cout << n->key << endl; //������� ����
		walk(z.right); // ��� �� ������� ���������
	}
}

int main()
{
	//freopen("out.txt", "w", stdout);
	srand(time(NULL));
	tree<int, int>* tr = new tree<int, int>();
	int n, k = 0;
	cin >> n;
	int z = clock(); //����� ����� ������ �������
	for (int i = 0; i < n; i++){
		tr->insert(rand() % 1000, 0);
	}
	cout << clock() - z << endl; //����� ������� n ���������
	return 0;
}

