#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;
private:
	const MultiMap& col;

    Node *MMIterator;
    ValueNode *valuesIterator; //nod actual in lista de valori a cheii actuale


	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

