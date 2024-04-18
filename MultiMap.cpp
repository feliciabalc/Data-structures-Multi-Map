#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>

using namespace std;

MultiMap::MultiMap() {
    mapSize = 0;
    headMap = nullptr;
    tailMap = nullptr;
}

//vezi cod si comm+ preg metode suplim+ scrie complexitati!!!!!!!!!!!!!!!!!!!!

//best case=Theta(1), worst case=Theta(size), average case=O(size)
void MultiMap::add(TKey c, TValue v) {
    ValueNode *newValueNode = new ValueNode;
    newValueNode->value = v;
    newValueNode->next = nullptr;
    newValueNode->previous = nullptr;

    if (this->headMap == nullptr) {
        Node *newNode = new Node;
        newNode->previous = nullptr;
        newNode->next = nullptr;
        newNode->key = c;
        newNode->headList = newValueNode;
        newNode->tailList = newValueNode;
        this->headMap = newNode;
        this->tailMap = newNode;
        this->mapSize += 1;

        return;
    }

    Node *current = headMap;
    while (current != nullptr) {
        if (current->key == c) {
            current->tailList->next = newValueNode;
            newValueNode->previous = current->tailList;
            current->tailList = newValueNode;
            mapSize += 1;
            return;
        }
        current = current->next;
    }
    Node *newNode = new Node;
    newNode->key = c;
    newNode->headList = newValueNode;
    newNode->tailList = newValueNode;
    newNode->next = nullptr;
    newNode->previous = tailMap;

    tailMap->next = newNode;
    tailMap = newNode;
    mapSize += 1;
}

//best case=Theta(1), worst case=Theta(size^2), average case=O(size^2)
bool MultiMap::remove(TKey c, TValue v) {
    bool exists = false;
    vector<TValue> valuesVector = search(c);
    for(int i=0; i<valuesVector.size();i++)
        if(valuesVector[i]==v)
            exists=true;
    if(exists==false)
        return false;

    Node *current = headMap;
    while (current != nullptr) {
        if (current->key == c) {
            ValueNode *currentValueNode = current->headList;
            while (currentValueNode != nullptr && currentValueNode->value!=v) {//te opresti la val cautata din lista
                currentValueNode = currentValueNode->next;
            }
            if(currentValueNode->value==v){
                //stergi head
                if (currentValueNode->previous == nullptr) {
                    // ai un singur element in lista, sterge nodu, caz daxca era singurul
                    if (currentValueNode->next == nullptr) {
                        //current->headList = nullptr;
                        //current->tailList= nullptr;
                        delete currentValueNode;
                        if (current == headMap && current == tailMap) {//daca e singuru din map si syergem nod
                            delete current;
                            headMap = nullptr;
                            tailMap = nullptr;
                        } else if (current ==
                                   headMap) { //nodul e head, sterg si nodul pentru ca inca sunt pe cazul in care aveam o singura valoare in lista de valori
                            current->next->previous = nullptr;
                            headMap = current->next;
                            delete current;

                        } else if (current ==
                                   tailMap) { //nodul e tail, sterg si nodul pentru ca inca sunt pe cazul in care aveam o singura valoare
                            current->previous->next = nullptr;
                            tailMap = current->previous;
                            delete current;
                        } else { //nodul nu e nici head nici tail, refac legaturile, sterg nodu
                            current->previous->next = current->next;
                            current->next->previous = current->previous;
                            delete current;

                        }
                        mapSize-=1;
                        return  true;
                        // stergi head,dar mai ai elem in lista
                    }else {
                        currentValueNode->next->previous = nullptr;
                        current->headList = currentValueNode->next;
                        delete currentValueNode;
                        mapSize-=1;
                        return true;
                    }

                } else {
                    // o valoare din mijloc
                    if (currentValueNode->next != nullptr) {
                        currentValueNode->next->previous = currentValueNode->previous;
                        currentValueNode->previous->next = currentValueNode->next;
                        delete currentValueNode;
                        mapSize-=1;
                        return true;
                    // e tail
                    } else {
                        currentValueNode->previous->next = nullptr;
                        current->tailList = currentValueNode->previous;
                        delete currentValueNode;
                        mapSize-=1;
                        return true;
                    }
                }
            }else
                return false;
        }
        current = current->next;
    }
    return false;
}

//best case=Theta(1), worst case=Theta(size^2), average case=O(size^2)
vector<TValue> MultiMap::search(TKey c) const {
    std::vector<TValue> valuesVector;

    if (isEmpty()) {
        return vector<TValue>();
    }

    Node *current = headMap;
    while (current != nullptr) {
        if (current->key == c) {
            ValueNode *currentValue = current->headList;
            while (currentValue != nullptr) {
                valuesVector.push_back(currentValue->value);
                currentValue = currentValue->next;
            }
            break;
        }
        current = current->next;
    }
    return valuesVector;
}

//best case= worst case= average case=Theta(1)
int MultiMap::size() const {
    return mapSize;
}

//best case= worst case= average case=Theta(1)
bool MultiMap::isEmpty() const {
    if (headMap == nullptr) {
        return true;
    }
    return false;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

//best case=Theta(size^2), worst case=Theta(size^2), average case=O(size^2)
MultiMap::~MultiMap() {
    Node *current = headMap;

    while (current != nullptr) {
        Node *next = current->next;
        ValueNode *valCurrent = current->headList;
        while (valCurrent != nullptr) {
            ValueNode *valNext = valCurrent->next;
            delete valCurrent;
            valCurrent = valNext;
        }
        delete current;
        current = next;
    }

}


