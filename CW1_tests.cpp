#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CW1.cpp"// Include the header file where your library code is defined

TEST_CASE("Library System Tests", "[library]") {
     Librarian admin(1, "Name", "Adress", "email@mail.com", 00);
     REQUIRE(admin.getStaffId()==1);
     REQUIRE(admin.getSalary()==0);
}

TEST_CASE("Library System Test2", "[library]") {
    Person person("Name", "Adress", "email@mail.com");
     REQUIRE(person.getName()=="Name");
     REQUIRE(person.getAddress()=="Adress");
    REQUIRE(person.getEmail()=="email");
}


