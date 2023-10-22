//
// Created by Nikita on 20.10.2023.
//

#ifndef HASH_HASHSET_H
#define HASH_HASHSET_H

#include <vector>
#include <string>
#include <stdexcept>

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
        insertionToNull(set[hashFunction(val)], val);
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

    bool operator[](Type val) {
        return this->search(val);
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

    Node* insertionToNull(Node*& actual, Type val) {

        if (actual == nullptr) {
            actual = new Node(val);
            return actual;
        }

        if (actual->data == val) {
            return actual;
        }

        return insertionToNull(actual->neighbour, val);
    }
};

void Test_hashSet() {
    int iteration = 0;

    // Testcase 1
    {
        std::string error_dis =  "Test " + std::to_string(++iteration) + " failed for int in hashSet: ";
        hashSet<int> hs(4);

        hs.insert(1);
        hs.insert(12);
        hs.insert(42);
        hs.insert(1);

        if(hs.search(1) != true) {
            throw std::runtime_error(error_dis + "1 is attend");
        }
    }

    // Testcase 2
     {
        std::string error_dis =  "Test " + std::to_string(++iteration) + " failed for int in hashSet: ";
        hashSet<std::string> hs(10);

        hs.insert("12");
        hs.insert("Hello");
        hs.insert("VE");
        hs.insert("Bubble");

        if(hs["12"] != true) {
            throw std::runtime_error(error_dis + "\"12\" is attend");
        }
    }

    // Testcase 3
    {
        std::string error_dis =  "Test " + std::to_string(++iteration) + " failed for int in hashSet: ";
        hashSet<long double> hs(10);

        hs.insert(3.141592);
        hs.insert(2.7);
        hs.insert(1.61234567890);
        hs.insert(0);

        if(hs.search(0) != true) {
            throw std::runtime_error(error_dis + "0 is attend");
        }

        if(hs[1.61234567890]  != true) {
            throw std::runtime_error(error_dis + "1.61234567890 is attend");
        }

        if(hs[2.7]  != true) {
            throw std::runtime_error(error_dis + "2.7 is attend");
        }

        if(hs[3.141592]  != true) {
            throw std::runtime_error(error_dis + "3.141592 is attend");
        }

        if(hs[12]  != false) {
            throw std::runtime_error(error_dis + "12 is not attend");
        }
    }
}


#endif //HASH_HASHSET_H
