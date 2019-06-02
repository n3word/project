#include "hashtable.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>


    Identifier::Identifier(const std::string& name): m_name(name) {}

    std::string Identifier::name() const {
        return m_name;
    }

    bool HashTable::add(const Identifier& id) {
            if (hash(id) < min_hash_value) return false;
            m_hash_table[hash(id)].push_back(id);
            return true;
    }


    Identifier& HashTable::get(const std::string& id_name) {
        std::list<Identifier>& line = m_hash_table[hash(id_name)];
        std::list<Identifier>::iterator it =
        std::find(line.begin(), line.end(), id_name);

        if (it == line.end()) {
            //std::cout << "Identifier \'" << id_name << "\' not found!" << std::endl;
        }

        return *it;
    }

    std::list<Identifier>& HashTable::getFromKey (size_t Key) {
        std::list<Identifier>& line = m_hash_table[Key];
        if (m_hash_table[Key].empty()) {
            //std::cout << "Items with key '" << Key << "\' not found!" << std::endl;
        }
        return line;
    }

    bool operator==(const Identifier& left, const Identifier& right)
    {
        return left.name() == right.name();
    }

    size_t hash(const Identifier& id) {
        
        if (id.name().length() == 1)
            return 2 * size_t(id.name()[0]);
        return size_t(id.name()[0]) + size_t(id.name()[1]);
    }

