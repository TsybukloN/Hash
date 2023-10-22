//
// Created by Nikita on 20.10.2023.
//

#ifndef HASH_HASHMAP_H
#define HASH_HASHMAP_H

#include <vector>
#include <string>
#include <stdexcept>

template <class KayT, class DataT>
class hashMap{
public:
    explicit hashMap(int size_user) {
        size = size_user;
        set.resize(size);
    }

    void insert(KayT key, DataT val) {
        insertionToNull(set[hashFunction(key)], key, val);
    }

    DataT search(KayT key) {
        Node* actual = set[hashFunction(key)];

        while(actual != nullptr) {
            if(actual->key == key) {
                return actual->data;
            }
            actual = actual->neighbour;
        }
        return DataT();
    }

    DataT operator[](KayT key) {
        return this->search(key);
    }

private:

    struct Node {
        KayT key;
        DataT data;
        Node* neighbour;

        explicit Node(KayT key, DataT val) {
            this->key = key;
            data = val;
            neighbour = nullptr;
        }
    };

    int size;
    std::vector<Node*> set;

    [[nodiscard]] int hashFunction(long long key) const {
        key = (~key) + (key << 15);
        key = key ^ (key >> 12);
        key = key + (key << 2);
        key = key * 2057;
        key = key ^ (key >> 16);
        return std::abs(key) % size;
    }

    [[nodiscard]] int hashFunction(const std::string& key) const {
        unsigned int hash = 0;
        for (char ch : key) {
            hash = hash * 7 + ch;
        }
        return hash % size;
    }

    Node* insertionToNull(Node*& actual, KayT key, DataT val) {
        if (actual == nullptr) {
            actual = new Node(key, val);
            return actual;
        }
        return insertionToNull(actual->neighbour, key, val);
    }
};

void Test_hashMap() {
    int iteration = 0;

    // Testcase 1
    { // string in hash
        std::string error_dis =  "Test " + std::to_string(++iteration) + " failed for int in hashMap: ";
        hashMap<std::string, double> hm(4);

        hm.insert("PI", 3.141592);
        hm.insert("E", 2.7);
        hm.insert("V", 1.6);
        hm.insert("K", 3);

        if(hm["PI"] != 3.141592) {
            throw std::runtime_error(error_dis + "PI was not founded");
        }

        if(hm["pi"] == 3.141592) {
            throw std::runtime_error(error_dis + "pi is not PI");
        }
    }

    // Testcase 2
    { // double in hash
        std::string error_dis =  "Test " + std::to_string(++iteration) + " failed for int in hashMap: ";
        hashMap<double, std::string> hm(4);

        hm.insert(3.141592, "PI");
        hm.insert(2.7, "E");
        hm.insert(1.6, "V");
        hm.insert( 3, "K");

        if(hm[3.141592] != "PI") {
            throw std::runtime_error(error_dis + "3.141592 was not founded");
        }

        if(hm[3.14] == "PI") {
            throw std::runtime_error(error_dis + "3.14 is not 3.141592");
        }
    }
}

#endif //HASH_HASHMAP_H
