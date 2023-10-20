//
// Created by Nikita on 20.10.2023.
//

#ifndef HASH_HASHMAP_H
#define HASH_HASHMAP_H

#include <vector>
#include <string>

template <class KayT, class DataT>
class hashMap{
public:
    explicit hashMap(int size_user) {
        size = size_user;
        set.resize(size);

        for(int i = 0;i  < size;i++) {
            set[i] = nullptr;
        }
    }

    void insert(KayT key, DataT val) {
        Node*& actual = set[hashFunction(key)];

        while(actual != nullptr){
            if(actual->key == key) {
                return;
            }
            actual = actual->neighbour;
        }

        actual = new Node(key, val);
    }

    DataT search(KayT key) {
        Node* actual = set[hashFunction(key)];

        while(actual != nullptr) {
            if(actual->key == key) {
                return actual->data;
            }
            actual = actual->neighbour;
        }

        return false;
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
};

#endif //HASH_HASHMAP_H
