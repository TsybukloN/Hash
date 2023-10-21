#include <iostream>
#include "hashSet.h"
#include "hashMap.h"

using namespace std;

int main() {
    /*
    hashSet<string> hs(4);

    hs.insert("Hello");
    hs.insert("world");

    cout << hs.search("Hello");
    */

    hashMap<string, int> hm(2); 

    hm.insert("Hello", 1);
    hm.insert("?", 3);
    hm.insert("word", 2);

    cout << hm.search("?");

    return 0;
}