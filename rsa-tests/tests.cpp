#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "C:\Users\The user\Desktop\מסמכים לימודיים\פרקטיקום\RSAAlgorithem_after_boost\RSAAlgorithem_after_boost\doctest.h"


using namespace std;
using namespace boost::multiprecision;

cpp_int public_key;
cpp_int private_key;
cpp_int n;
cpp_int gcd(cpp_int a, cpp_int b);
void set_Private_And_Public_Keys();
bool is_key_at_least_2048_bits(cpp_int n);
std::vector<cpp_int> encoder(std::string message);
std::string decoder(std::vector<cpp_int> encoded);


// Test cases
TEST_CASE("testing gcd function") {
    CHECK(gcd(48, 18) == 6);
    CHECK(gcd(101, 103) == 1);
    CHECK(gcd(54, 24) == 6);
}
TEST_CASE("testing if RSA key length is at least 2048 bits") {
    std::cout << "Setting private and public keys..." << std::endl;
    set_Private_And_Public_Keys();
    std::cout << "Checking if key is at least 2048 bits..." << std::endl;
    CHECK(is_key_at_least_2048_bits(n));
}

TEST_CASE("testing encryption and decryption of a message with special characters") {
    set_Private_And_Public_Keys();
    string original = "H3ll0, RSA! @2024";
    auto encoded = encoder(original);
    auto decoded = decoder(encoded);
    CHECK(decoded == original);
}
TEST_CASE("testing empty message encryption and decryption") {
    set_Private_And_Public_Keys();
    string original = "";
    auto encoded = encoder(original);
    auto decoded = decoder(encoded);
    CHECK(decoded == original);
}
TEST_CASE("testing encryption and decryption of a message with special characters") {
    set_Private_And_Public_Keys();
    string original = "H3ll0, RSA! @2024";
    auto encoded = encoder(original);
    auto decoded = decoder(encoded);
    CHECK(decoded == original);
}