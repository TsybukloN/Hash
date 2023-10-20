//
// Created by Nikita on 20.10.2023.
//

#ifndef HASH_HASHSET_H
#define HASH_HASHSET_H

#include <vector>

class hashSet{ // Work only with int yet
public:
    explicit hashSet(int size_user) {
        size = size_user;
        set.resize(size);

        for(int i = 0;i  < size;i++) {
            set[i] = nullptr;
        }
    }

    void insert(int val) {
        Node*& actual = set[hashFunction(val)];

        while(actual != nullptr){
            if(actual->data == val) return;
            actual = actual->neighbour;
        }

        actual = new Node(val);
    }

    bool search(int val) {
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
        int data;
        Node* neighbour;

        explicit Node(int val) {
            data = val;
            neighbour = nullptr;
        }
    };

    int size;
    std::vector<Node*> set;

    [[nodiscard]] int hashFunction(int key) const {
        key = (~key) + (key << 15);
        key = key ^ (key >> 12);
        key = key + (key << 2);
        key = key * 2057;
        key = key ^ (key >> 16);
        return key % size;
    }
};

#endif //HASH_HASHSET_H
