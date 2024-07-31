#pragma once
#include <vector>
#include "Polynom.h"
#include "GaloisField.h"
using namespace std;

enum PolyError {
	POLY_SUCCESS,           // No error
	POLY_NULL_POINTER,      // Null pointer encountered
	POLY_ALLOCATION_FAILED, // Memory allocation failed
	POLY_OTHER_ERROR        // Other specific error (add more as needed)
};

class UsePoly
{
private:

	PolyError lastError;

public:
	UsePoly();
	//����� ������� ������� ���.
	//n: ���� �������� (���� �������). coef: ���� ������� �� ��������.
	vector<RS_WORD> Poly_Create(vector<RS_WORD>& coef);

	//����� ������ �� ������� �������.
	//poly: ������� ������� ������.
	void Poly_Free(vector<RS_WORD>& coef);

	// ����� ��� ���������.
	//out: ������� ����� �� ������, a, b: ���������� ������.
	//: �� ����� �� �������� �� ������ ������ ����� ����� ��� - �����, ��� ������� ��������(width, height, depth).
	void Poly_Add(vector<RS_WORD>& out, vector<RS_WORD>& a, vector<RS_WORD>& b);

	//��� ������� ������.
	//out: ������� ����� �� ������, in: �������� ����, scale: ������, gf: ��� ����� �� ����� ����.
	void Poly_Scale(vector<RS_WORD>& out, vector<RS_WORD>& in, RS_WORD scale, GaloisField* gf);

	//��� ��� ���������.
	//out: ������� ����� �� ������, a, b: ���������� ����, gf: ��� ����� �� ����� ����.
	void Poly_Mult(vector<RS_WORD>& out, vector<RS_WORD>& a, vector<RS_WORD>& b, GaloisField* gf);

	//����� ���������.
	//result: ������ �� ������, quotient, remainder: ���� ������� �� ������, a, b: ���������� ������, gf: ��� ����� �� ������ ������.
	void Poly_Div(vector<RS_WORD>& quotient, vector<RS_WORD>& remainder, vector<RS_WORD>& a, vector<RS_WORD>& b, GaloisField* gf);

	//����� ���� �� ������� ������ �����
	//poly: �������� ������, x: ���� ������, gf: ��� ����� �� ����� ������.
	RS_WORD Poly_Eval(vector<RS_WORD>& poly, RS_WORD x, GaloisField* gf);

	//����� ����� ������� ����� ������.
	// out: ����� ����� �� �������� �� �������, poly: �������� ������, max: ���� ������� ������, gf: ��� ����� �� ����� ������.
	void Poly_ChienSearch(vector<uint8_t>* out, vector<RS_WORD>& poly, int max, GaloisField* gf);

	//����� ����� ������� ��������
	//poly: �������� ������ ������, left, right: ���� ������ ������ ��� ��.
	void Poly_Pad(vector<RS_WORD>& poly, int left, int right);

	//���� ����� ������� ���������
	//poly: �������� ������ ������, left, right: ���� ������ ������ ��� ��.
	void Poly_Trim(vector<RS_WORD>& poly, int left, int right);

	//�������� ������ �� ���� �������� b ���� �������� a ������� �� ������ �������� out.
	//out: ����� �������� ������ ������ �� ������. a: ����� �������� ������ ����� �� ������. b : ����� �������� ������ ������� ���� a.
	void Poly_Append(vector<RS_WORD>& out, vector<RS_WORD>& a, vector<RS_WORD>& b);

	//�������� ����� �� �������� in ������� �� ������ �������� out.
	void Poly_Reverse(vector<RS_WORD>& out, vector<RS_WORD>& in);

	PolyError getLastError();
};

