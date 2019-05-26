#include <iostream>
#include <climits>
#include <process.h>
#include <cassert>
using namespace std;

template <class K, class V>
class node
{
public:
	node* st;
	node* dr;
	node* tata;
	K nKey;
	V valoare;
	int inaltime;
	node()
	{
		st = nullptr;
		dr = nullptr;
		tata = nullptr;
	}
	node(K key, V val)
	{
		st = nullptr;
		dr = nullptr;
		tata = nullptr;
		valoare = val;
		nKey = key;

	}
	K getKey()
	{
		return this->nKey;
	}
	V getVal()
	{
		return this->valoare;
	}
	int getHeight()
	{
		if (this == nullptr)
			return 0;
		return this->inaltime;
	}
};