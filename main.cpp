#include <iostream>
#include "hashSet.h"

using namespace std;

int main() {
    hashSet hs(10);

    srand(time(0));

    for(int i = 0;i < 10;i++) {
        int tmp = rand() % 1000;
        cout << tmp << endl;
        hs.insert(tmp);
        cout << hs.search(tmp) << endl;
    }

    return 0;
}