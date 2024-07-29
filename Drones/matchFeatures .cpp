#include "matchFeatures .h"
using namespace std;

//@params 2 vectors of key point
//@return vector of matches
//this function initialized data for the search
std::vector<std::vector<PointMatch>> MatchFeaturers::knnMatch(const std::vector<std::vector<int>>& descriptors1, const std::vector<std::vector<int>>& descriptors2, int k) {
   
    //vector to store index of descript2
    std::vector<std::vector<int>> indices(descriptors1.size(), std::vector<int>(k));
    //vector to store distence between the vectors
    std::vector<std::vector<float>> dists(descriptors1.size(), std::vector<float>(k));

    SearchParams searchParams;
    //check vector is not empty
    if (descriptors1.empty() || descriptors2.empty())
        return std::vector<std::vector<PointMatch>>();
    //send to the searchfunction
    knnSearch(descriptors1, descriptors2, indices, dists, k, searchParams);

    //store the indc and dist that is now full in poinMacth vec
    for (size_t i = 0; i < descriptors1.size(); ++i) {
        std::vector<PointMatch> matches;
        for (int j = 0; j < k; ++j) {
            PointMatch point;
            point.queryIdx = i;
            point.trainIdx = indices[i][j];
            point.distance = dists[i][j];
            matches.push_back(point);
        }
        knn_matches.push_back(matches);
    }

    return knn_matches;
}
//@params 2 vectors of key point ,dists for storing the distance,
//indices for index,k find the k nearest neighbor
void MatchFeaturers::knnSearch(const std::vector<std::vector<int>>& descriptors1, const std::vector<std::vector<int>>& descriptors2, std::vector<std::vector<int>>& indices, std::vector<std::vector<float>>& dists, int knn, SearchParams searchParams) {
    
    //build hash table with descrip2 stores the vecs
        for (int i=0; i<table_number; i++) {
            //Each bucket has keys and each key has its nearest neighbors  
                Bucket bucket;
            for (int row = 0; row < descriptors2.size(); row++)
            {
                //send to hash func to get key
                size_t key = getKey(descriptors2[row]);
                //insert to current key in map
                bucket[key].push_back(row);
            }
            //adds the bucket to the table
            hash_table.push_back(bucket);
    }

    //fill mask for quick finding of key
        fill_xor_mask(0, descriptors2[0].size(), 2, xor_masks);

    //find neighbors for descrip1
    for (size_t i = 0; i < descriptors1.size(); ++i)
    {
        //stores the k nearest neighbors
        ResultSet resultSet(knn);

        //find k nearest neighbors
        findNeighbors(descriptors1[i], resultSet , descriptors2);

        std::vector<int> resultIndices = resultSet.getIndices();
        std::vector<float> resultDistances = resultSet.getDistances();
        //fill indices and dists with result
        for (int j = 0; j < knn; ++j) {
            indices[i][j] = resultIndices[j];
            dists[i][j] = resultDistances[j];
        }
    }
}
//@params x=vec1[i] ^ vec2[i]
//counts the number of bits whose value is 1 in the binary expression .
//return count of bits 1;
int popcount(unsigned int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}
//@param vec1-desc1,vec2-desc2 in the table ,size of vec
//finds distence using bits between vectors
//returns distance
int computeDistance(const int* vec1, const int* vec2, size_t size)
{
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result +=popcount(vec1[i] ^ vec2[i]);
    }
    return result;
}
//@params vec- one key point,result - for result ,desc2 -for finding the neighbors 
void MatchFeaturers::findNeighbors(const std::vector<int>& vec, ResultSet& result, const std::vector<std::vector<int>>& descriptors2) 
{

    auto table_s = hash_table.begin();
    auto table_e = hash_table.end();
    int ind = 0;
    //run on table
    for (; table_s != table_e; ++table_s) {
        size_t key = getKey(vec);
        //run on mask for quick finding 
        for (const auto& xor_mask : xor_masks) {
            size_t sub_key = key ^ xor_mask;
            //get the vector in the current key in the bucket
            const auto sub_bucket = getBucketFromKey(sub_key,ind);
            if (sub_bucket.size() == 0) continue;

            // run on vector in the found key in the bucket
            for (const auto& index : sub_bucket) {
                int dist = 0;
                //send to hamming function to calculate the distanse
                dist = computeDistance(vec.data(), descriptors2[index].data(), vec.size());
                //add the distanse and index of the neighbor if necsery
                result.addPoint(dist, index);
            }
        }
        //the next index in the table
        ind++;

    }
}
