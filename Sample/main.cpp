
#include "hashtable.h"

int main()
{
    HashTable ht;
    
    ht.add(Identifier("a"));
    ht.add(Identifier("aa"));
    ht.add(Identifier("aaa"));
    ht.add(Identifier("if"));
    ht.add(Identifier("fi"));
    ht.add(Identifier("A0"));
    ht.add(Identifier(" "));
    ht.get("kek").name();
    
    std::cout << ht.get("a").name() << std::endl;
    std::cout << ht.get("aa").name() << std::endl;
    std::cout << ht.get("aaa").name() << std::endl;
    std::cout << ht.get("if").name() << std::endl;
    std::cout << ht.get("fi").name() << std::endl;
    std::cout << ht.get("hello").name() << std::endl;
    
    std::list<Identifier> list = ht.getFromKey(94);
    std::list<Identifier>::iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        std::cout << (*it).name();
    }
    
    
    return 0;
}

