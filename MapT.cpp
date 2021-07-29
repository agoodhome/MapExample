//
// Created by we7289 on 4/19/2021.
//

#include "MapT.h"
#include <unordered_map>
//using namespace std;

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD = 1.0;
template<class K, class T>
MapT<K, T>::MapT() {

    buckets = new forward_list<pair<K,T>>[DEFAULT_BUCKETS];
    numBuckets = DEFAULT_BUCKETS;
    numKeys = 0;
    maxLoad = DEFAULT_LOAD;

}

template<class K, class T>
void MapT<K, T>::Add(K key, T value) {

    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    // If key is already in the Map, then change the value associated with key
    for (auto it = buckets[bucket].begin();  it != buckets[bucket].end(); ++it) {
        // "auto" infers the type for "it".

        if (it->first == key) {
            it->second = value;    // Change the value associated with the key
            return;                // and return
        }
    }

    // Create key value pair
    pair<K,T> keyValuePair;
    keyValuePair.first = key;
    keyValuePair.second = value;

    ++numKeys;
    buckets[bucket].push_front(keyValuePair);   // Add the key/value to the Map
}

template<class K, class T>
void MapT<K, T>::Remove(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin();  it != buckets[bucket].end(); ++it) {
        // "auto" infers the type for "it".

        if (it->first == key) {
            buckets[bucket].remove(*it);  // Erase the item iterator points to
            --numKeys;
            return;
        }
    }
}

template<class K, class T>
bool MapT<K, T>::Contains(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);
    pair<K,T> p;

    for (auto it = buckets[bucket].begin();  it != buckets[bucket].end(); ++it) {
        // "auto" infers the type for "it".

        if (it->first == key) {
            return true;
        }
    }

    return false;
}

template<class K, class T>
T MapT<K, T>::operator[](K key) {
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin();  it != buckets[bucket].end(); ++it) {
        // "auto" infers the type for "it".

        if (it->first == key) {
            return it->second;
        }
    }

    throw KeyDoesNotExist();
}

template<class K, class T>
double MapT<K, T>::LoadFactor() {
    return static_cast<double>(numKeys)/numBuckets;
}

template<class K, class T>
void MapT<K, T>::SetMaxLoad(double maxLoad) {
    this->maxLoad = maxLoad;
}

template<class K, class T>
void MapT<K, T>::Rehash(int numBuckets) {
    MapT<K, T> newMap(numBuckets);

    ResetIterator();
    for (int i = 0; i < Size(); i++) {
        newMap.Add(GetNextPair());
    }
}

template<class K, class T>
void MapT<K, T>::ResetIterator() {
    mapIter = buckets[0].begin();
    currBucket = 0;
}

template<class K, class T>
pair<K,T> MapT<K, T>::GetNextPair() {
    pair<K,T> currVal;

    while(mapIter == buckets[currBucket].end()) {
        mapIter = buckets[++currBucket].begin();
    }

    currVal = *mapIter;
    mapIter++;

    return currVal;
}

template<class K, class T>
int MapT<K, T>::GetHashIndex(const K &key) {
    unordered_map<K,T> mapper;
    typename unordered_map<K,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}



