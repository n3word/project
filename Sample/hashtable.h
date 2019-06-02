#ifndef hashtable_h
#define hashtable_h


#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class Identifier
{
public:
    Identifier(const std::string& name);
    std::string name() const;
    
private:
    std::string m_name;
};


class HashTable
{
public:
    static const size_t min_hash_value = int(' ') + int(' ');
    static const size_t max_hash_value = int('z') + int('z') + 1;
    static const size_t hash_table_size = max_hash_value;
    
public:
    bool add(const Identifier& id);
    Identifier& get(const std::string& id_name);
    std::list<Identifier>& getFromKey (size_t Key);
    
private:
    std::list<Identifier> m_hash_table[hash_table_size];
};

bool operator==(const Identifier& left, const Identifier& right);
size_t hash(const Identifier& id);

#endif /* hashtable_h */
