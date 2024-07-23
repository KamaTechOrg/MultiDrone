#ifndef ENCRYPTIONRESULT_H
#define ENCRYPTIONRESULT_H

#include <vector>
#include "Point.h" // �� ��� ���� ������ �� ��� �-Point

struct EncryptionResult {
    std::vector<unsigned char> ciphertext;
    Point R; // ��� ��-Point ����� ��� �� ���� ����� ��
};

#endif // ENCRYPTIONRESULT_H
