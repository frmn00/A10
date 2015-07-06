#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <deque>
#include <ctime>
using namespace std;

/*
¬езде далее за K принимаетс€ тип ключа, а за V - тип значени€
  должен поддерживать сравнение, как минимум оператор "<"
“.е. если   - не встроенный тип данных, а, например, структура, то она должна перегрузить оператор меньше.
*/

template<typename K, typename V>
struct node {
	K key; //ключ
	V value; //значение
	node *parent = NULL; //указатель на родител€
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
		void walk(const node<K, V>*); //обход дерева в сортированном пор€дке
		node<K, V>* get_root(); //возвращает корень дерева
	private:
		node<K, V> *root;
};

template<typename K, typename V>
tree<K, V>::tree(){
	root = NULL; //изначально дерево пусто -> корн€ нет
}

//template<typename K, typename V>
//void tree<K, V>::insert(const K key, const V val){
//	node<K, V>* nd = new node<K, V>(key, val); //создаем узел 
//	node<K, V>* l = NULL, *r = NULL; //временные переменные
//	l = root; //полагаем узел - корнем
//	while (l != NULL){ //пока не дошли до листа
//		r = l;
//		if (key < l->key) //выбираем куда вставить
//			l = l->left;
//		else
//			l = l->right;
//	}
//	nd->parent = r; //полагаем предком последний просмотренный узел
//	if (r == NULL) //если такого нет - то дерево пусто, и вставл€емый узел €вл€етс€ корнем
//		root = nd;
//	else{
//		if (key < r->key) //иначе выбираем предка
//			r->left = nd;
//		else
//			r->right = nd;
//	}
//	return;
//}

template<typename K, typename V>
void tree<K, V>::insert(const K key, const V val){
	node<K, V>* nd = new node<K, V>(key, val); //создаем узел
	node<K, V>* r = root;
	while (r != NULL){
		if (nd->key > r->key){
			if (r->right != NULL)
				r = r->right;
			else{
				nd->parent = r;
				r->right = nd;
				break;
			}
		}
		else if (nd->key <= r->key){
			if (r->left != NULL)
				r = r->left;
			else{
				nd->parent = r;
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
	while (z.right != NULL) //пока не дошли до корн€ - идЄм в правое поддерево
		z = *z.right;
	return &z;
}

template<typename K, typename V>
node<K, V>* tree<K, V>::min(const node<K, V> *n){
	node<K, V> z = *n; //копируем в локальную переменную узел
	while (z.left != NULL) //пока не дошли до корн€ - идЄм в левое поддерево
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
		walk(z.left); //рекурсивно идЄм по левому поддереву
		cout << n->key << endl; //выводим ключ
		walk(z.right); // идЄм по правому поддереву
	}
}

int main()
{
	srand(time(NULL));
	tree<int, int>* tr = new tree<int, int>();
	int n;
	cin >> n;
	int z = clock();
	for (int i = 0; i < n; i++)
		tr->insert(rand() % 1000, 0);
	cout << clock() - z << endl;
	tr->walk(tr->get_root());
	return 0;
}

