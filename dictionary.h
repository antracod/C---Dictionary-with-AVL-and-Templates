#pragma once
#include <iostream>
#include <climits>
#include <process.h>
#include <cassert>
#include "node.h"
using namespace std;

template <class K, class V>
class dictionary
{

private:
	node<K, V>* root;
	int elementCount;

public:

	dictionary();
	dictionary(const dictionary& d);

	dictionary &operator =(const dictionary& d);
	~dictionary();

	node<K, V>* clone(node <K, V>*t) const;
	void cleanUp(node<K, V>* &t);
	void clear();

	node<K, V>* rotatieDr(node<K, V>* y);
	node<K, V>* rotatieSt(node<K, V>* x);
	int getBal(node <K, V>*n);

	node<K, V>* insert(K &key, V &val, node<K, V>* &t);
	void setWithKey(K key, V val);
	int getNrElem();

	node<K, V>* minValNod(node<K, V>* Nod);
	node<K, V>* deleteNode(K key, node<K, V>* rad);
	void erase(K key);

	V src(K key, node<K, V> *rad);
	V search(K key);

	void empty();
	V operator [](const K key);
	node<K, V>* getRad();
	static void inorder(node <K, V>*rad, ostream &out);

	friend ostream& operator<<(ostream &out, const dictionary& d);

};



template <class K,class V>
dictionary <K,V>::dictionary()
{
	root = nullptr;
	elementCount = 0;
}

template <class K, class V>
dictionary <K, V>::dictionary(const dictionary& d)
{
	root = nullptr;
	root = clone(d.root);

}

template <class K, class V>
dictionary <K,V>& dictionary <K, V>::operator =(const dictionary& d)
{
	clear();
	root = clone(d.root);
	this->elementCount = d.elementCount;
	return *this;
}

template <class K, class V>
dictionary <K, V>::~dictionary()
{
	clear();
}

template <class K, class V>
node <K,V>* dictionary <K, V>::clone(node<K,V>*t) const
{
	if (t == nullptr)
		return nullptr;

	node<K, V> *rad = new node<K, V>;
	rad->nKey = t->nKey;
	rad->valoare = t->valoare;
	rad->tata = t->tata;
	rad->st = clone(t->st);
	rad->dr = clone(t->dr);

	return rad;
}

template <class K, class V>
void dictionary <K, V>::cleanUp(node<K, V>* &t)
{
	if (t != nullptr)
	{
		cleanUp(t->st);
		cleanUp(t->dr);
		delete t;
	}
	t = nullptr;
}

template <class K, class V>
void dictionary <K, V>::clear()
{
	cleanUp(root);
}

template <class K, class V>
node<K, V>* dictionary <K, V>::rotatieDr(node<K, V>* y)
{
	node<K, V>* x = y->st;
	node<K, V>* z = x->dr;

	x->dr = y;
	y->st = z;

	y->inaltime = max(y->st->getHeight(), y->dr->getHeight()) + 1;
	x->inaltime = max(x->st->getHeight(), x->dr->getHeight()) + 1;

	return x;
}

template <class K, class V>
node<K, V>* dictionary <K, V>::rotatieSt(node<K, V>* x)
{
	node<K, V>* y = x->dr;
	node<K, V>* z = y->st;

	y->st = x;
	x->dr = z;

	x->inaltime = max(x->st->getHeight(), x->dr->getHeight()) + 1;
	y->inaltime = max(y->st->getHeight(), y->dr->getHeight()) + 1;

	return y;
}

template <class K, class V>
int dictionary <K, V>::getBal(node<K, V> *n)
{
	if (n == nullptr)
		return 0;
	return (n->st->getHeight() - n->dr->getHeight());
}

template <class K, class V>
node<K, V>* dictionary <K, V>::insert(K &key, V &val, node<K, V>* &t)
{
	if (t == nullptr)
	{
		t = new node<K, V>;
		t->nKey = key;
		t->valoare = val;
		t->st = t->dr = nullptr;
		t->inaltime = 1;
		return t;
	}
	if (key == t->nKey)
	{
		t->valoare = val;
		return t;
	}
	if (key < t->nKey)
	{
		node<K, V> *n = insert(key, val, t->st);
		t->st = n;
		n->tata = t;
	}
	else
	{
		node<K, V> *n = insert(key, val, t->dr);
		t->dr = n;
		n->tata = t;
	}

	t->inaltime = 1 + max(t->st->getHeight(), t->dr->getHeight());
	int bal = getBal(t);

	if (bal > 1 && key < t->st->nKey)
		return rotatieDr(t);

	if (bal < -1 && key > t->dr->nKey)
		return rotatieSt(t);

	if (bal > 1 && key > t->st->nKey)
	{
		t->st = rotatieSt(t->st);
		return rotatieDr(t);
	}

	if (bal < -1 && key > t->dr->nKey)
	{
		t->dr = rotatieDr(t->dr);
		return rotatieSt(t);
	}

	return t;
}

template <class K, class V>
void dictionary <K, V>::setWithKey(K key, V val)
{
	root = insert(key, val, root);
	elementCount++;
}

template <class K, class V>
int dictionary <K, V>::getNrElem()
{
	return elementCount;
}

template <class K, class V>
node<K, V>* dictionary <K, V>::minValNod(node<K, V>* Nod)
{
	node<K, V>* n = Nod;
	while (n && n->st != nullptr)
		n = n->st;

	return n;
}

template <class K, class V>
node<K, V>* dictionary <K, V>::deleteNode(K key, node<K, V>* rad)
{

	if (rad == nullptr)
		return rad;
	if (key < rad->nKey)
		rad->st = deleteNode(key, rad->st);
	else if (key > rad->nKey)
		rad->dr = deleteNode(key, rad->dr);
	else
	{

		if (rad->st == nullptr || rad->dr == nullptr)
		{
			node<K, V> *temp = rad->st ? rad->st : rad->dr;
			if (temp == nullptr)
			{
				temp = rad;
				rad = nullptr;
			}
			else
				*rad = *temp;
			delete temp;
		}
		else
		{
			node<K, V>* temp = minValNod(rad->dr);

			rad->nKey = temp->nKey;
			rad->valoare = temp->valoare;

			rad->dr = deleteNode(temp->nKey, rad->dr);
		}



	}

	if (rad == nullptr)
		return rad;

	rad->inaltime = 1 + max(rad->st->getHeight(), rad->dr->getHeight());
	int bal = getBal(rad);

	if (bal > 1 && getBal(rad->st) >= 0)
		return rotatieDr(rad);

	if (bal > 1 && getBal(rad->st) < 0)
	{
		rad->st = rotatieSt(rad->st);
		return rotatieDr(rad);

	}

	if (bal < -1 && getBal(rad->dr) <= 0)
		return rotatieSt(rad);

	if (bal < -1 && getBal(rad->dr) > 0)
	{
		rad->dr = rotatieDr(rad->dr);
		return rotatieSt(rad);
	}
	return rad;
}

template <class K, class V>
void dictionary <K, V>::erase(K key)
{
	root = deleteNode(key, root);
	elementCount--;
}

template <class K, class V>
V dictionary <K, V>::src(K key, node <K, V>*rad)
{

	try
	{
	    cout<<"Key found"<<'\n';
		if (rad == nullptr)
			throw 1;
	}
	catch (int e)
	{
		cout << "Key not found: " << key << '\n';
		return e;
	}
	if (rad->nKey == key)
		return rad->valoare;
	if (rad->nKey > key)
		return src(key, rad->st);
	else
		return src(key, rad->dr);
}

template <class K, class V>
V dictionary <K, V>::search(K key)
{
	return src(key, root);
}

template <class K, class V>
void dictionary <K, V>::empty()
{
	while (root != nullptr)
		erase(root->nKey);
}

template <class K, class V>
void dictionary <K, V>::inorder(node <K, V>*rad, ostream &out)
{
	if (rad != nullptr)
	{
		inorder(rad->st, out);
		out << rad->getKey() << '\t' << rad->getVal() << endl;
		inorder(rad->dr, out);
	}
}

template <class K, class V>
ostream& operator<<(ostream &out, const dictionary<K,V>& d)
{
	out << "Chei\tValori\n";

	node<K, V> *p = d.root;
	inorder(p, out);
	return out;
}

template <class K, class V>
V dictionary <K, V>::operator [](const K key)
{
	K s = key;
	return this->search(s);
}

template <class K, class V>
node<K, V>* dictionary <K, V>::getRad()
{
	return root;
}

