#include "HeaderFile.h"

bool myRunKernel(const vector<MPoint>v1, const vector<MPoint>v2, vector<double>& currentHomography)
{
	int i;
	int count = v1.size();
	if (count != v2.size() || count < 4)
	{
		return false;
	}
	MPoint cM(0, 0), cm(0, 0), sM(0, 0), sm(0, 0);

	for (i = 0; i < count; i++)
	{
		cm.x += v2[i].x; cm.y += v2[i].y;
		cM.x += v1[i].x; cM.y += v1[i].y;
	}

	cm.x /= count;
	cm.y /= count;
	cM.x /= count;
	cM.y /= count;

	for (i = 0; i < count; i++)
	{
		sm.x += fabs(v2[i].x - cm.x);
		sm.y += fabs(v2[i].y - cm.y);
		sM.x += fabs(v1[i].x - cM.x);
		sM.y += fabs(v1[i].y - cM.y);
	}

	if (fabs(sm.x) < DBL_EPSILON || fabs(sm.y) < DBL_EPSILON ||
		fabs(sM.x) < DBL_EPSILON || fabs(sM.y) < DBL_EPSILON)
		return 0;

	sm.x = count / sm.x; sm.y = count / sm.y;
	sM.x = count / sM.x; sM.y = count / sM.y;

	double invHnorm[9] = { 1. / sm.x, 0, cm.x, 0, 1. / sm.y, cm.y, 0, 0, 1 };
	double Hnorm2[9] = { sM.x, 0, -cM.x * sM.x, 0, sM.y, -cM.y * sM.y, 0, 0, 1 };

	Matrix<double, 9, 9> LtL = Matrix<double, 9, 9>::Zero();

	for (int i = 0; i < count; i++) {
		double x = (v2[i].x - cm.x) * sm.x, y = (v2[i].y - cm.y) * sm.y;
		double X = (v1[i].x - cM.x) * sM.x, Y = (v1[i].y - cM.y) * sM.y;
		Matrix<double, 9, 1> Lx;
		Lx << X, Y, 1, 0, 0, 0, -x * X, -x * Y, -x;
		Matrix<double, 9, 1> Ly;
		Ly << 0, 0, 0, X, Y, 1, -y * X, -y * Y, -y;
		LtL += Lx * Lx.transpose() + Ly * Ly.transpose();
	}

	SelfAdjointEigenSolver<Matrix<double, 9, 9>> eigensolver(LtL);
	if (eigensolver.info() != Success) return 0;

	Matrix<double, 9, 1> smallest_eigenvector = eigensolver.eigenvectors().col(0);


	double H0[9];
	for (int i = 0; i < 9; i++) {
		H0[i] = smallest_eigenvector[i];
	}

	double Htemp[9];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Htemp[i * 3 + j] = 0;
			for (int k = 0; k < 3; ++k) {
				Htemp[i * 3 + j] += invHnorm[i * 3 + k] * H0[k * 3 + j];
			}
		}
	}
	int efes = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			currentHomography.at(i * 3 + j) = efes;
			for (int k = 0; k < 3; ++k) {
				currentHomography.at(i * 3 + j) += Htemp[i * 3 + k] * Hnorm2[k * 3 + j];
			}
		}
	}

	double scale = currentHomography.at(8);
	for (int i = 0; i < 9; i++) {
		currentHomography.at(i) /= scale;
	}
	return true;
}

int checkIfBetter(vector<MPoint>v, vector<MPoint>v2, vector<double>H, const double defaultDistance)
{
	int countGoodMatch = 0;
	//���� ����������
	for (int i = 0; i < v.size(); i++)
	{
		float ww = 1.f / (H[6] * v[i].x + H[7] * v[i].y + H[8]);
		float dx = (H[0] * v[i].x + H[1] * v[i].y + H[2]) * ww - v2[i].x;
		float dy = (H[3] * v[i].x + H[4] * v[i].y + H[5]) * ww - v2[i].y;
		double distanceSquared = dx * dx + dy * dy;

		if (distanceSquared <= defaultDistance * defaultDistance)
		{
			countGoodMatch++;
		}
	}

	return countGoodMatch;
}

pair<double, double > calculateFunction(MPoint p, MPoint p2)
{
	//double Incline2= atan2(p2.y - p.y, p2.x - p.x) * 180 / 3.14159;;
	double incline = (double(p2.y - p.y)) / (double(p2.x - p.x));
	double b = p.y - p.x * incline;
	return make_pair(incline, b);

}

bool checkIfOnSameLine(vector<MPoint>v)
{
	if (v.size() < 3) return false;

	MPoint p1 = v[0];
	MPoint p2 = v[1];
	float m = (p1.y - p2.y) / (p1.x - p2.x);
	float b = p1.y - m * p1.x;
	for (int i = 0; i < v.size(); i++)
	{
		MPoint pi = v[i];
		if (pi.y != m * pi.x + b) { return false; }
	}
	return true;


	/*MPoint p = v[randomNumbers[0]];
	MPoint p2 = v2[randomNumbers[0]];
	pair<double, double > incline = calculateFunction(p, p2);
	pair<double, double > incline2;
	for (int i = 1; i <= 3; i++)
	{
		p = v[randomNumbers[i]];
		p2 = v2[randomNumbers[i]];
		incline2 = calculateFunction(p, p2);
		if (incline == incline2)
			return true;
	}
	return false;*/
	//
	//MPoint p = v[randomNumbers[0]];
	//MPoint p2 = v[randomNumbers[1]];
	//MPoint p3 = v2[randomNumbers[0]];
	//MPoint p4 = v2[randomNumbers[1]];
	//pair<double, double > incline = calculateFunction(p, p2);
	//pair<double, double > incline2 = calculateFunction(p3, p4);
	//for (int i = 2; i <= 3; i++)
	//{
		//p = v[randomNumbers[i]];
		//p2 = v2[randomNumbers[i]];
		//int y = p.x * incline.first + incline.second;
		//int y2 = p2.x * incline2.first + incline2.second;
		//if (y == p.y || y2 == p2.y)
			//return true;
	//}
	//return false;


}

bool myCheckSubset(const std::vector<MPoint>& ms1, const std::vector<MPoint>& ms2)
{
	if (checkIfOnSameLine(ms1) || checkIfOnSameLine(ms2)) return false;


	static const int tt[][3] = { {0, 1, 2}, {1, 2, 3}, {0, 2, 3}, {0, 1, 3} };
	const MPoint* src = &ms1[0];// .ptr<MPoint>();
	const MPoint* dst = &ms2[0];// .ptr<MPoint>();
	int negative = 0;

	for (int i = 0; i < 4; i++)
	{
		const int* t = tt[i];
		double A = (src[t[0]].x, src[t[0]].y, 1., src[t[1]].x, src[t[1]].y, 1., src[t[2]].x, src[t[2]].y, 1.);
		double B = (dst[t[0]].x, dst[t[0]].y, 1., dst[t[1]].x, dst[t[1]].y, 1., dst[t[2]].x, dst[t[2]].y, 1.);

		//negative += determinant(A) * determinant(B) < 0;
		negative += myDeterminant(&A) * myDeterminant(&B) < 0;
	}
	if (negative != 0 && negative != 4)
		return false;


	return true;
}


//bool myCheckSubset(const std::vector<MPoint>& ms1, const std::vector<MPoint>& ms2)
//{
//	if (checkIfOnSameLine(ms1) || checkIfOnSameLine(ms2)) return false;
//
//
//	static const int tt[][3] = { {0, 1, 2}, {1, 2, 3}, {0, 2, 3}, {0, 1, 3} };
//	const MPoint* src = &ms1[0];// .ptr<MPoint>();
//	const MPoint* dst = &ms2[0];// .ptr<MPoint>();
//	int negative = 0;
//
//	for (int i = 0; i < 4; i++)
//	{
//		const int* t = tt[i];
//		double A = (src[t[0]].x, src[t[0]].y, 1., src[t[1]].x, src[t[1]].y, 1., src[t[2]].x, src[t[2]].y, 1.);
//		double B = (dst[t[0]].x, dst[t[0]].y, 1., dst[t[1]].x, dst[t[1]].y, 1., dst[t[2]].x, dst[t[2]].y, 1.);
//
//		//negative += determinant(A) * determinant(B) < 0;
//		negative += myDeterminant(&A) * myDeterminant(&B) < 0;
//	}
//	if (negative != 0 && negative != 4)
//		return false;
//
//
//	return true;
//}

bool myGetSubset(const vector<MPoint> m1, const vector<MPoint> m2, vector<MPoint>& ms1, vector<MPoint>& ms2, int maxAttempts)
{
	//for iters from 1 to maxAttempts :
		//randomly select modelPoints unique indices from 0 to length(m1) - 1
		//	create empty arrays ms1 and ms2

		//	for each selected index in the subset :
		//copy the corresponding data point from m1 to ms1
		//	copy the corresponding data point from m2 to ms2

		//	if checkSubset(ms1, ms2) is true :
		//		return true

		//		return false

	random_device rd;
	mt19937 gen(rd());

	//vector<MPoint> ms1;//(modelPoints);
	//vector<MPoint> ms2;//(modelPoints);
	for (int iters = 0; iters < maxAttempts; ++iters) {
		vector<double> indices(m1.size());
		iota(indices.begin(), indices.end(), 0);
		shuffle(indices.begin(), indices.end(), gen);

		ms1.clear();
		ms2.clear();

		for (int i = 0; i < 4; ++i)
		{
			ms1.push_back(m1[indices[i]]);
			ms2.push_back(m2[indices[i]]);
		}

		if (myCheckSubset(ms1, ms2)) {
			return true;
		}
	}
	/* for( int iters = 0; iters < maxAttempts; ++iters )
		{
			int i;

			for( i = 0; i < modelPoints; ++i )
			{
				int idx_i;

				for ( idx_i = rng.uniform(0, count);
					std::find(idx, idx + i, idx_i) != idx + i;
					idx_i = rng.uniform(0, count) )
				{}

				idx[i] = idx_i;

				for( int k = 0; k < esz1; ++k )
					ms1ptr[i*esz1 + k] = m1ptr[idx_i*esz1 + k];

				for( int k = 0; k < esz2; ++k )
					ms2ptr[i*esz2 + k] = m2ptr[idx_i*esz2 + k];
			}

			if( cb->checkSubset(ms1, ms2, i) )
				return true;
		}*/

	return false;
}

vector<double>homography(vector<MPoint>v, vector<MPoint>v2, const double biggestDistance)
{
	vector<double>mostGood(9);
	const int sizeMPoints = v.size();
	if (sizeMPoints != v2.size())
	{
		cout << "ERROR: Both vectors must be the same size." << endl;
		return mostGood;
	}
	if (sizeMPoints < 4)
	{
		cout << "ERROR: It is impossible to do a homography with less than 4 Points!!" << endl;
		return mostGood;
	}

	if (sizeMPoints == 4)
	{
		bool result;
		result= myRunKernel(v, v2, mostGood);
		if (!result)
			cout << "ERROR: the homography didn't success!!" << endl;
		return mostGood;
	}


	vector<MPoint>v1_randoMPoints;
	vector<MPoint>v2_randoMPoints;
	//vector<int> randomNumbers;
	vector<double>currentHomography(9);
	int count = sizeMPoints, biggestCount = 0;
	for (int index = 0; index < 2000; index++)
	{
		v1_randoMPoints.clear();
		v2_randoMPoints.clear();
		//randomNumbers.clear();
		//random_device rd;
		//mt19937 gen(rd());
		//uniform_int_distribution<> dis(0, v.size()-1);

		//while (randomNumbers.size() < 4) {
		//	int randomNumber = dis(gen);
		//	if (std::find(randomNumbers.begin(), randomNumbers.end(), randomNumber) == randomNumbers.end()) {
		//		randomNumbers.push_back(randomNumber);	
		//		v1_randoMPoints.push_back(v.at(randomNumber));
		//		v2_randoMPoints.push_back(v2.at(randomNumber));
		//	}
		//}
		if (count > 4)
		{
			bool found = myGetSubset(v, v2, v1_randoMPoints, v2_randoMPoints, 10000);
			//bool myGetSubset(const std::vector<MPoint>&m1, const std::vector<MPoint>&m2, int modelPoints, int maxAttempts)
			if (!found)
			{
				if (index == 0)
				{
					cout << "can not calculate the homography" << endl;
					return mostGood;
				}
				break;
			}
		}
		//����� ���������� ��� 4 ������
		bool res = myRunKernel(v1_randoMPoints, v2_randoMPoints, currentHomography);
		if (!res)
			continue;

		//����� �� �� ���� ����
		count = checkIfBetter(v, v2, currentHomography, biggestDistance);
		if (count > biggestCount)
		{
			/*cout << "count good points:  " << count << endl;*/
			biggestCount = count;
			mostGood = currentHomography;
		}
	}
	return mostGood;
}

double myDeterminant(const double* mat) {
	/*  return a(0,0)*(a(1,1)*a(2,2) - a(2,1)*a(1,2)) -
			a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) +
			a(0,2)*(a(1,0)*a(2,1) - a(2,0)*a(1,1));*/
	return mat[0] * (mat[4] * mat[8] - mat[5] * mat[7]) - 
		mat[1] * (mat[3] * mat[8] - mat[5] * mat[6]) + 
		mat[2] * (mat[3] * mat[7] - mat[4] * mat[6]);
}

