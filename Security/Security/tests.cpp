﻿
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "AES.h"
#include "API.h"
using namespace MyAES;
MyAES::AES aes(MyAES::AESKeyLength::AES_128);

//vlaidTest
//TEST_CASE("Check validation plainText's Length")
//{
//    AES aes=AES(AESKeyLength::AES_128);
//    unsigned char short_plain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee };
//
//    unsigned char long_plain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee,0xff,0xaa};
//    unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//    REQUIRE_THROWS_AS(aes.EncryptECB(short_plain, sizeof(short_plain), key), length_error);
//    REQUIRE_THROWS_AS(aes.EncryptECB(long_plain, sizeof(long_plain), key), length_error);
//}
//unitTest
//TEST_CASE("Check ECB Encryption")
//{
//    AES aes = AES(AESKeyLength::AES_128);
//    unsigned char plain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//                               0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
//    unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//    unsigned char right[] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
//                             0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a };
//    unsigned char* out = aes.EncryptECB(plain, sizeof(plain), key);
//
//    CHECK(memcmp(out,right, sizeof(right)) == 0);
//    delete[] out;
//
//}



//TEST_CASE("CBC Encryption and Decryption with Key Lengths") {
//    unsigned char validPlain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//                                  0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
//    unsigned char validIv[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//                               0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
//
//    SUBCASE("Key Length 128") {
//        unsigned char validKey[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//        AES aes(AESKeyLength::AES_128);
//
//        unsigned char* out = aes.EncryptCBC(validPlain, sizeof(validPlain), validKey, validIv);
//        unsigned char* innew = aes.DecryptCBC(out, sizeof(validPlain), validKey, validIv);
//
//        CHECK(memcmp(innew, validPlain, sizeof(validPlain)) == 0);
//        delete[] out;
//        delete[] innew;
//    }
//
//    SUBCASE("Key Length 192") {
//        unsigned char validKey[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
//                                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
//                                    0x18, 0x19, 0x1a, 0x1b };
//        AES aes(AESKeyLength::AES_192);
//
//        unsigned char* out = aes.EncryptCBC(validPlain, sizeof(validPlain), validKey, validIv);
//        unsigned char* innew = aes.DecryptCBC(out, sizeof(validPlain), validKey, validIv);
//
//        CHECK(memcmp(innew, validPlain, sizeof(validPlain)) == 0);
//        delete[] out;
//        delete[] innew;
//    }
//
//    SUBCASE("Key Length 256") {
//        unsigned char validKey[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
//                                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
//                                    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
//        AES aes(AESKeyLength::AES_256);
//
//        unsigned char* out = aes.EncryptCBC(validPlain, sizeof(validPlain), validKey, validIv);
//        unsigned char* innew = aes.DecryptCBC(out, sizeof(validPlain), validKey, validIv);
//
//        CHECK(memcmp(innew, validPlain, sizeof(validPlain)) == 0);
//        delete[] out;
//        delete[] innew;
//    }
//}


//TEST_CASE("CBC TwoBlocksEncrypt") {
//    AES aes(AESKeyLength::AES_128);
//
//    unsigned char plain [] = {
//        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
//        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
//    };
//
//    unsigned char iv [] = {
//        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
//    };
//
//    unsigned char key [] = {
//        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
//    };
//
//    unsigned char right [] = {
//        0x1b, 0x87, 0x23, 0x78, 0x79, 0x5f, 0x4f, 0xfd,
//        0x77, 0x28, 0x55, 0xfc, 0x87, 0xca, 0x96, 0x4d,
//        0x4c, 0x5b, 0xca, 0x1c, 0x48, 0xcd, 0x88, 0x00,
//        0x3a, 0x10, 0x52, 0x11, 0x88, 0x12, 0x5e, 0x00
//    };
//
//    unsigned char *out = aes.EncryptCBC(plain,sizeof(plain), key, iv);
//    CHECK(out == right);
//}

//בדיקות טסט עבור כל שלב ושלב בתהליך ההצפנה
//TEST_CASE("check key expansion") {
//    API::writeLog("Test check key expansion");
//
//    // מפתח דוגמא באורך 128 ביטים (16 בתים)
//    unsigned char key[16] = {
//        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
//        0xab, 0xf7, 0xcf, 0x70, 0x4b, 0xd6, 0x5e, 0x4c
//    };
//
//    // התוצאה הצפויה של הרחבת המפתח למפתח של 128 ביטים (64 בתים ראשונים)
//    unsigned char expectedKeyExpansion[64] = {
//        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
//        0xab, 0xf7, 0xcf, 0x70, 0x4b, 0xd6, 0x5e, 0x4c,
//        0xa0, 0x88, 0x23, 0x2a, 0xfa, 0x54, 0xa3, 0x6c,
//        0xfe, 0x2c, 0x39, 0x76, 0x17, 0xb1, 0x39, 0x05,
//        0x0d, 0xa0, 0x60, 0x82, 0xf2, 0x7a, 0x59, 0x73,
//        0xc2, 0x96, 0x35, 0x59, 0x95, 0xb9, 0x80, 0xf6,
//        0xf2, 0x43, 0x7a, 0x7f, 0x3d, 0xed, 0x8a, 0xf9,
//        0x18, 0x5f, 0x4d, 0x4c, 0x4a, 0xf8, 0x45, 0x8a
//    };
//
//    unsigned char w[176]; // 176 בתים עבור מפתח של 128 ביטים
//
//    AES aes(AESKeyLength::AES_128);
//    aes.KeyExpansion(key, w);
//    for (int i = 0; i < 64; ++i) {
//        CHECK(w[i] == expectedKeyExpansion[i]);
//    }
//
//    // בדיקות נוספות
//    // בדיקת מפתח ריק
//    unsigned char empty_key[16] = { 0 };
//    unsigned char expected_empty_key_expansion[64] = { 0 }; // התוצאה הצפויה עבור מפתח ריק
//
//    aes.KeyExpansion(empty_key, w);
//    for (int i = 0; i < 64; ++i) {
//        CHECK(w[i] == expected_empty_key_expansion[i]);
//    }
//
//    // בדיקת מפתח עם כל הערכים השווים
//    unsigned char same_value_key[16] = { 0xFF };
//    unsigned char expected_same_value_key_expansion[64]; // התוצאה הצפויה עבור מפתח עם כל הערכים השווים
//    // כאן יש לחשב ידנית את התוצאה הצפויה ולהכניס אותה למערך
//
//    aes.KeyExpansion(same_value_key, w);
//    for (int i = 0; i < 64; ++i) {
//        CHECK(w[i] == expected_same_value_key_expansion[i]);
//    }
//
//    // בדיקת מפתח מקסימלי
//    unsigned char max_value_key[16] = {
//        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
//    };
//    unsigned char expected_max_value_key_expansion[64]; // התוצאה הצפויה עבור מפתח מקסימלי
//    // כאן יש לחשב ידנית את התוצאה הצפויה ולהכניס אותה למערך
//
//    aes.KeyExpansion(max_value_key, w);
//    for (int i = 0; i < 64; ++i) {
//        CHECK(w[i] == expected_max_value_key_expansion[i]);
//    }
//}
//TEST_CASE("check SubWord") {
//    unsigned char word[4] = { 0xcf, 0x4f, 0x3c, 0x09 };
//    //cout << word[0] / 16 <<"," << word[0] % 16 << endl;
//    //cout << word[1] / 16 << "," << word[1] % 16 << endl;
//    //cout << word[2] / 16 << "," << word[2] % 16 << endl;
//    //cout << word[3] / 16 << "," << word[3] % 16 << endl;
//    aes.SubWord(word);
//    CHECK(word[0] == 0x8a);
//    CHECK(word[1] == 0x84);
//    CHECK(word[2] == 0xeb);
//    CHECK(word[3] == 0x01); // הערכים הצפויים מה-S-box
//}
//TEST_CASE("check Rcon")
//{
//    unsigned char rcon[4];
//    aes.Rcon(rcon, 9);
//    CHECK(rcon[0] == 0x1b);
//    CHECK(rcon[1] == 0x00);
//    CHECK(rcon[2] == 0x00);
//    CHECK(rcon[3] == 0x00);
//
//    aes.Rcon(rcon, 10);
//    CHECK(rcon[0] == 0x36);
//    CHECK(rcon[1] == 0x00);
//    CHECK(rcon[2] == 0x00);
//    CHECK(rcon[3] == 0x00);
//}
//TEST_CASE("Testing AES SubBytes step1") {
//    // מקרה בדיקה בסיסי
//    unsigned char state[4][4] = {
//        {0x32, 0x88, 0x31, 0xe0},
//        {0x43, 0x5a, 0x31, 0x37},
//        {0xf6, 0x30, 0x98, 0x07},
//        {0xa8, 0x8d, 0xa2, 0x34}
//    };
//
//    unsigned char expected[4][4] = {
//        {0x23, 0xC4, 0xC7, 0xE1},
//        {0x1A, 0xBE, 0xC7, 0x9A},
//        {0x42, 0x04, 0x46, 0xC5},
//        {0xC2, 0x5D, 0x3A, 0x18}
//    };
//
//    aes.SubBytes(state);
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(state[i][j] == expected[i][j]);
//        }
//    }
//    // מקרה קצה: בדיקה של כל הערכים הגבוהים ביותר והנמוכים ביותר
//    unsigned char edge_case_state[4][4] = {
//        {0x00, 0xFF, 0x00, 0xFF},
//        {0xFF, 0x00, 0xFF, 0x00},
//        {0x00, 0xFF, 0xFF, 0x00},
//        {0xFF, 0x00, 0x00, 0xFF}
//    };
//
//    unsigned char edge_case_expected[4][4] = {
//        {0x63, 0x16, 0x63, 0x16},
//        {0x16, 0x63, 0x16, 0x63},
//        {0x63, 0x16, 0x16, 0x63},
//        {0x16, 0x63, 0x63, 0x16}
//    };
//
//    aes.SubBytes(edge_case_state);
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(edge_case_state[i][j] == edge_case_expected[i][j]);
//        }
//    }
//}
//TEST_CASE("Testing AES ShiftRows step2") {
//    // מקרה בדיקה בסיסי
//    unsigned char state[4][4] = {
//        {0x00, 0x01, 0x02, 0x03},
//        {0x10, 0x11, 0x12, 0x13},
//        {0x20, 0x21, 0x22, 0x23},
//        {0x30, 0x31, 0x32, 0x33}
//    };
//
//    unsigned char expected[4][4] = {
//        {0x00, 0x01, 0x02, 0x03},
//        {0x11, 0x12, 0x13, 0x10},
//        {0x22, 0x23, 0x20, 0x21},
//        {0x33, 0x30, 0x31, 0x32}
//    };
//
//    aes.ShiftRows(state);
//
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(state[i][j] == expected[i][j]);
//        }
//    }
//    // מקרה קצה: בדיקה של ערכים אפסיים בשורה
//    unsigned char edge_case_state[4][4] = {
//        {0x00, 0x01, 0x02, 0x03},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x20, 0x21, 0x22, 0x23},
//        {0x30, 0x31, 0x32, 0x33}
//    };
//
//    unsigned char edge_case_expected[4][4] = {
//        {0x00, 0x01, 0x02, 0x03},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x22, 0x23, 0x20, 0x21},
//        {0x33, 0x30, 0x31, 0x32}
//    };
//
//    aes.ShiftRows(edge_case_state);
//
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(edge_case_state[i][j] == edge_case_expected[i][j]);
//        }
//    }
//
//}
//TEST_CASE("Testing AES MixColumns step3") {
//    // בדיקה בסיסית
//    unsigned char state[4][4] = {
//        {0x87, 0xf2, 0x4d, 0x97},
//        {0x6e, 0x4c, 0x90, 0xec},
//        {0x46, 0xe7, 0x4a, 0xc3},
//        {0xa6, 0x8c, 0xd8, 0x95}
//    };
//
//    unsigned char expected[4][4] = {
//        {0x47, 0x40, 0xa3, 0x4c},
//        {0x37, 0xd4, 0x70, 0x9f},
//        {0x94, 0xe4, 0x3a, 0x42},
//        {0xed, 0xa5, 0xa6, 0xbc}
//    };
//
//    aes.MixColumns(state);
//
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(state[i][j] == expected[i][j]);
//        }
//    }
//
//    // מקרה קצה: כל הערכים במערך שווים לאפס
//    unsigned char zero_state[4][4] = {
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00}
//    };
//
//    unsigned char zero_expected[4][4] = {
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00},
//        {0x00, 0x00, 0x00, 0x00}
//    };
//
//    aes.MixColumns(zero_state);
//
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(zero_state[i][j] == zero_expected[i][j]);
//        }
//    }
//
//    // מקרה קצה: כל הערכים במערך שווים למקסימום
//    unsigned char max_state[4][4] = {
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff}
//    };
//
//    unsigned char max_expected[4][4] = {
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff},
//        {0xff, 0xff, 0xff, 0xff}
//    };
//
//    aes.MixColumns(max_state);
//
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            CHECK(max_state[i][j] == max_expected[i][j]);
//        }
//    }
//    //מקרה קצה: כל הערכים שווים לערך מסוים
//    //unsigned char same_state[4][4] = {
//    //{0x01, 0x01, 0x01, 0x01},
//    //{0x02, 0x02, 0x02, 0x02},
//    //{0x01, 0x01, 0x01, 0x01},
//    //{0x01, 0x01, 0x01, 0x01}
//    //};
//
//    //unsigned char same_expected[4][4] = {
//    //    {0x01, 0x01, 0x01, 0x01},
//    //    {0x01, 0x01, 0x01, 0x01},
//    //    {0x01, 0x01, 0x01, 0x01},
//    //    {0x01, 0x01, 0x01, 0x01}
//    //};
//    //aes.MixColumns(same_state);
//    //for (int i = 0; i < 4; ++i) {
//    //    for (int j = 0; j < 4; ++j) {
//    //        CHECK(same_state[i][j] == same_expected[i][j]);
//    //    }
//    //}
//}
//TEST_CASE("check level4 Add round key") {
//    unsigned char diff_state[4][4] = {
//           {0x01, 0x02, 0x03, 0x04},
//           {0x05, 0x06, 0x07, 0x08},
//           {0x09, 0x0A, 0x0B, 0x0C},
//           {0x0D, 0x0E, 0x0F, 0x10}
//    };
//
//    unsigned char diff_key[16] = {
//        0x0F, 0x0E, 0x0D, 0x0C,
//        0x0B, 0x0A, 0x09, 0x08,
//        0x07, 0x06, 0x05, 0x04,
//        0x03, 0x02, 0x01, 0x00
//    };
//
//    unsigned char diff_expected[4][4] = {
//        {0x0E, 0x09, 0x04, 0x07},
//        {0x0B, 0x0C, 0x01, 0x0A},
//        {0x04, 0x03, 0x0E, 0x0D},
//        {0x01, 0x06, 0x0B, 0x10}
//    };    
//    aes.AddRoundKey(diff_state, diff_key);
//    for(int i=0;i<4;i++)
//        for (int j = 0; j < 4; j++)
//        {
//            CHECK(diff_state[i][j] == diff_expected[i][j]);
//        }
//}

