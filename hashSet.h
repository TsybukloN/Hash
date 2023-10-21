//
// Created by Nikita on 20.10.2023.
//

#ifndef HASH_HASHSET_H
#define HASH_HASHSET_H

#include <vector>
#include <string>

template <class Type>
class hashSet{
public:
    explicit hashSet(int size_user) {
        size = size_user;
        set.resize(size);

        for(int i = 0;i  < size;i++) {
            set[i] = nullptr;
        }
    }

    void insert(Type val) {
        insertioinToNull(set[hashFunction(val)], val);
    }

    bool search(Type val) {
        Node* actual = set[hashFunction(val)];

        while(actual != nullptr) {
            if(actual->data == val) {
                return true;
            }
            actual = actual->neighbour;
        }

        return false;
    }

private:

    struct Node {
        Type data;
        Node* neighbour;

        explicit Node(Type val) {
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

    Node* insertioinToNull(Node*& actual, Type val) {
        if (actual == nullptr) {
            actual = new Node(val);
            return actual;
        }
        return insertioinToNull(actual->neighbour, val);
    }
};

#endif //HASH_HASHSET_H
