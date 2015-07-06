#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <deque>
#include <ctime>
using namespace std;

/*
Везде далее за K принимается тип ключа, а за V - тип значения
К должен поддерживать сравнение, как минимум оператор "<"
Т.е. если К - не встроенный тип данных, а, например, структура, то она должна перегрузить оператор меньше.
*/

template<typename K, typename V>
struct node {
	K key; //ключ
	V value; //значение
	node *parent = NULL; //указатель на родителя
	node *left = NULL, *right = NULL; //указатели на левое и правое поддерево
	
	//конструктор по умолчанию
	node(){

	}

	//конструктор
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
		tree(); //конструктор
		void insert(const K, const V); //вставка узла
		node<K, V>* max(const node<K, V>*); //узел поддерева с максимальным значением ключа
		node<K, V>* min(const node<K, V>*); //узел поддерева с минимальным значением ключа
		void walk(const node<K, V>*); //обход дерева в сортированном порядке
		node<K, V>* get_root(); //возвращает корень дерева
	private:
		node<K, V> *root;
};

template<typename K, typename V>
tree<K, V>::tree(){
	root = NULL; //изначально дерево пусто -> корня нет
}

template<typename K, typename V>
void tree<K, V>::insert(const K key, const V val){
	node<K, V>* nd = new node<K, V>(key, val); //создаем узел
	if (root == NULL){ //если дерево пусто - то создаем корень
		root = nd;
		return;
	}
	node<K, V>* r = root;
	while (r != NULL){ //пока не наткнулись на лист
		if (nd->key > r->key){ // если ключ больше текущего
			if (r->right != NULL) //если не лист - продолжаем
				r = r->right; // идём вправо
			else{
				nd->parent = r; // если лист - вставляем
				r->right = nd;
				break;
			}
		}
		else if (nd->key <= r->key){ //если ключ меньше
			if (r->left != NULL) // если лист
				r = r->left; // идём влево
			else{
				nd->parent = r; //иначе вставляем
				r->left = nd;
				break;
			}
		}
	}
	return;
}

template<typename K, typename V>
node<K, V>* tree<K, V>::max(const node<K, V> *n){
	node<K, V> z = *n; //копируем в локальную переменную узел
	while (z.right != NULL) //пока не дошли до корня - идём в правое поддерево
		z = *z.right;
	return &z;
}

template<typename K, typename V>
node<K, V>* tree<K, V>::min(const node<K, V> *n){
	node<K, V> z = *n; //копируем в локальную переменную узел
	while (z.left != NULL) //пока не дошли до корня - идём в левое поддерево
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
		node<K, V> z = *n; //копируем узел в локальную переменную
		walk(z.left); //рекурсивно идём по левому поддереву
		cout << n->key << endl; //выводим ключ
		walk(z.right); // идём по правому поддереву
	}
}

int main()
{
	//freopen("out.txt", "w", stdout);
	srand(time(NULL));
	tree<int, int>* tr = new tree<int, int>();
	int n, k = 0;
	cin >> n;
	int z = clock(); //время после старта консоли
	for (int i = 0; i < n; i++){
		tr->insert(rand() % 1000, 0);
	}
	cout << clock() - z << endl; //время вставки n элементов
	return 0;
}

