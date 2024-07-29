#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stdint.h>
//#include <opencv2/opencv.hpp>
#include <any>
#include <map>
#include "HashTable.h"
#include <algorithm>

// for each point from what img and the poin distance distance
struct PointMatch
{
	int queryIdx;
	int trainIdx;
	float distance;
};

//Search behavior, such as speed, accuracy and order of results.
struct SearchParams
{
	int checks = 32;
	float eps = 0;
	bool sorted = true;
};

class MatchFeaturers:public HashTable
{
private:
    std::vector<PointMatch>good_matches;
    std::vector<std::vector<PointMatch>> knn_matches;

public:
	std::vector<std::vector<PointMatch>> knnMatch(const std::vector<std::vector<int>>& descriptors1, const std::vector<std::vector<int>>& descriptors2, int k);
	void knnSearch(const std::vector<std::vector<int>>& descriptors1, const std::vector<std::vector<int>>& descriptors2, std::vector<std::vector<int>>& indices, std::vector<std::vector<float>>& dists, int knn, SearchParams searchParams);
	std::vector<PointMatch> matchFilter(const std::vector<std::vector<PointMatch>>& knn_matches);
	void findNeighbors(const std::vector<int>& vec, ResultSet& result, const std::vector<std::vector<int>>& descriptors2);
   
};
