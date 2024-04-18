#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    if(!col.isEmpty()){
        MMIterator=col.headMap;
        valuesIterator=MMIterator->headList;
    }else{
        MMIterator= nullptr;
        valuesIterator= nullptr;
    }
}

//best case= worst case= average case=Theta(1)
TElem MultiMapIterator::getCurrent() const{
    if(!valid()){
        throw std::exception();
    }
    TKey key = MMIterator->key;

    TValue value = valuesIterator->value;

    return std::make_pair(key, value);
}

//best case= worst case= average case=Theta(1)
bool MultiMapIterator::valid() const {
    if (MMIterator != nullptr && valuesIterator != nullptr){
        return true;
    }
	return false;
}

//best case= worst case= average case=Theta(1)
void MultiMapIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    if (valuesIterator->next != nullptr) {//merg pe valori daca se mai poate
        valuesIterator = valuesIterator->next;
        return;
    }

    if(MMIterator->next != nullptr){//altfel merg la urm nod
        MMIterator=MMIterator->next;
        valuesIterator=MMIterator->headList;
        return;
    }

    MMIterator= nullptr;
    valuesIterator= nullptr;
}

//best case= worst case= average case=Theta(1)
void MultiMapIterator::first() {
    if (col.headMap != nullptr) {
        MMIterator = col.headMap;
        valuesIterator=MMIterator->headList;
    }
}

