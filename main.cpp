#include <iostream>
#include "list.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    list l;
    l.pushBack(12133);
    l.pushBack(12133.12);
    char* str = "hello";
    l.pushBack(str);
    l.showList();
    return 0;
}
