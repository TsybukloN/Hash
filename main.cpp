#include <iostream>
#include "hashMap.h"

using namespace std;

int main() {
    hashMap<string, int> hm(4);

    hm.insert("Hello", 1);
    hm.insert("world", 2);

    cout << hm.search("Hello");

    return 0;
}