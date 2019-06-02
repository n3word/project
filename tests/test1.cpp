
#ifdef __clang__
#define CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS
#endif


# include  "catch.hpp"
# include "hashtable.h"



TEST_CASE ("Hash-Table White Box testing", "[hash-table]") {
    HashTable ht;
    //Strategy "All ways" for all sections
    
    
    SECTION("Calculate hash-function") {
        //from ASCII character table "f" = 102; "i = 105"
        CHECK(hash(Identifier("if->false")) == 207);
        //from ASCII character table " " = 32, but name has 1 character
        CHECK(hash(Identifier(" ")) == 64);
        
        //CHECK(hash(Identifier("")) == NULL);
    }
    
    SECTION("Calculate hash-function for strings with different register") {
        INFO("Hash-function ignore register");
        REQUIRE(hash(Identifier("if-else")) != hash(Identifier("IF-ELSE")));
        REQUIRE(hash(Identifier("if-else")) != hash(Identifier("If-else")));
        REQUIRE(hash(Identifier("look")) != hash(Identifier("LoOk")));
    }
    
    SECTION("Add simple element") {
        //min_hash_value = int(' ')*2 = 64
        INFO("add() function works incorrectly");

        //here expected hash(id) > min_hash_value
        CHECK(ht.add(Identifier(" ")));
        CHECK(ht.add(Identifier("hello")));
        CHECK(ht.add(Identifier("z")));
    }
    
    SECTION("Add empty element") {
        INFO("add() function works incorrectly");
        //int('') = NULL, expected hash(id) < min_hash_value
        CHECK_FALSE(ht.add(Identifier("")));
    }
    
    SECTION("Get elements from a value after adding") {
        INFO("get() function works incorrectly");
        
        
        ht.add(Identifier("hello"));
        ht.add(Identifier(" "));
        CHECK(ht.get("hello").name() == "hello");
        CHECK(ht.get(" ").name() == " ");

    }
    
    SECTION("Get element from a value without adding") {
        INFO("get() function works incorrectly");
        //expected null result
        REQUIRE(ht.get("something") == Identifier(""));
    }
    
    SECTION("Get many elements with the same key") {
        ht.add(Identifier("if"));
        ht.add(Identifier("fi"));
        ht.add(Identifier("fiiiii"));
        size_t exp_key = hash(Identifier("if"));
        
        
        std::list<Identifier> test_list = ht.getFromKey(exp_key);
        std::list<Identifier>::iterator it;
        INFO ("Function getFromKey() returned not all items");
        for (it = test_list.begin(); it != test_list.end(); it++) {
            REQUIRE(((*it).name() == "if" || (*it).name() == "fi" || (*it).name() == "fiiiii"));
        }
    }
    
    SECTION("Get elements from key from empty table") {
        INFO("Expected empty hash-table, but it has some values");
        for(size_t i = 0; i < ht.hash_table_size; i++) {
            REQUIRE(ht.getFromKey(i).empty());
        }
    }
    
    
    
}
