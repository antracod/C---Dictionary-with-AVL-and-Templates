#include "dictionary.h"

dictionary <int,int> d;

void setKeys()
{
    d.setWithKey(1, 2);
    d.setWithKey(2, 3);
    d.setWithKey(3, 4);
    d.setWithKey(5, 77);
    d.setWithKey(8, 923);
    d.setWithKey(29, 392);
    d.setWithKey(399, 231);
    d.setWithKey(599, 999);
}

void getElements()
{
    assert(d.getNrElem()==8);
}

void searchDictionary()
{
    assert(d.search(8)==923);
    assert(d.search(29)==392);
    assert(d.search(1)==2);
}

void emptyDictionary()
{
    d.empty();
    assert(d.getNrElem() == 0);
}

void eraseElement()
{
      d.erase(3);
}

int main()
{
    setKeys();
    getElements();
    eraseElement();
    searchDictionary();
    emptyDictionary();

    return 0;
}
