#pragma once
#include <future>
#include <vector>
#include <map>
#include <string>
#include "../Communication/Meta_Data.h" 
#include "../Socket_communication/DroneCommunicationManager.h" 
constexpr size_t MAX_DATA_SIZE_FOR_THREAD = 4;//4 bytes 1048576=1mb
constexpr size_t OPTION_TO_SEND = 2; //sends Asynchronously
using namespace std;

class TransferData {
public:

    int num_cores();
    void waiting(vector<future<bool>>& futures);
    bool sendMessageByChunk(const string& chunk, size_t chunkIndex, int num_drone);
    bool sendMetaData(const Meta_Data& metaData, int num_drone);
    bool sendData(const string& data, const Meta_Data& metaData, int num_drone);
    void sendsAsynchronously(const string& dataAsStr, const Meta_Data& metaData, size_t numChunks, size_t chunk_size, size_t numThreads, int num_drone);
    void sendsSynchronously(const string& dataAsStr, const Meta_Data& metaData, int num_drone);
    void preparingTheDataForTransferring(const string& dataAsStr, const Meta_Data& metaData, int num_drone);
    void addChunk(const string& chunk, size_t chunkIndex);
    string getCollectedData();

private:
    map<size_t, string> collectedDataMap;
    mutex dataMutex;
    DroneCommunicationManager* droneCommunicationManager=new DroneCommunicationManager();
};
