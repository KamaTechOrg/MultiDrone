#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cstdlib>
#include <ctime>
#include <stdbool.h>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
extern "C" {
#include "Disk_Mng_Master.h"
#include "Disk_Mng_Master.c"
#include "Disk_Mng_Master_API.h"
}
struct GlobalSetup {
    GlobalSetup() {
        srand(time(0));
    }
};
GlobalSetup globalSetup;

int generateRandomNumber(int upper = DISK_SIZE) {
    int lower = 0;
    return (rand() % (upper - lower + 1)) + lower;
}
void printTreeDetails(AVLNode_t* node) {
    if (node == NULL) {
        return;
    }

    // Print current node details
    printf("Node details:\n");
    printf("Map Size: %d\n", node->avlNodeInfo->mapSize);
    printf("Array Index: %d\n", node->avlNodeInfo->arrayIndex);
    printf("LRU: %d\n", node->avlNodeInfo->lru);
    printf("Height: %d\n\n", node->height);

    // Recurse on the left and right subtrees
    printTreeDetails(node->left);
    printTreeDetails(node->right);
}

void printNode(AVLNode_t* node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }
    printf("Node details:\n");
    printf("Map Size: %d\n", node->avlNodeInfo->mapSize);

    printf("Array Index: %d\n", node->avlNodeInfo->arrayIndex);
    printf("LRU: %d\n", node->avlNodeInfo->lru);
}
void printTree(AVLNode_t* root) {
    if (root == nullptr) {
        return;
    }

    // Queue for level order traversal
    std::queue<AVLNode_t*> q;
    q.push(root);

    // Vector to store levels of the tree
    std::vector<std::vector<AVLNode_t*>> levels;

    // Traverse the tree level by level
    while (!q.empty()) {
        int nodeCount = q.size();
        std::vector<AVLNode_t*> currentLevel;

        while (nodeCount > 0) {
            AVLNode_t* node = q.front();
            q.pop();
            currentLevel.push_back(node);

            if (node != nullptr) {
                q.push(node->left);
                q.push(node->right);
            }
            nodeCount--;
        }

        // Add level only if there are nodes at this level
        if (std::any_of(currentLevel.begin(), currentLevel.end(), [](AVLNode_t* n) { return n != nullptr; })) {
            levels.push_back(currentLevel);
        }
    }

    int maxLevel = levels.size();
    int width = 1 << (maxLevel - 1); // Maximum width of the tree at the last level

    for (int i = 0; i < maxLevel; ++i) {
        std::vector<AVLNode_t*> currentLevel = levels[i];
        int numNodes = currentLevel.size();
        int spacing = width / (numNodes + 1);
        int offset = spacing / 2;

        // Print leading spaces
        std::cout << std::setw(offset) << "";

        // Print nodes at current level
        for (AVLNode_t* node : currentLevel) {
            if (node == nullptr) {
                std::cout << std::setw(width) << "";
            }
            else {
                std::cout << std::setw(width) << node->avlNodeInfo->mapSize;
            }
            std::cout << std::setw(offset) << "";
        }
        std::cout << std::endl;

        // Print level separators
        if (i < maxLevel - 1) {
            std::cout << std::setw(width / 2) << "";
            for (AVLNode_t* node : currentLevel) {
                if (node == nullptr) {
                    std::cout << std::setw(width) << "";
                }
                else {
                    std::cout << std::setw(width / 2) << (node->left != nullptr ? "/" : " ");
                    std::cout << std::setw(width / 2) << (node->right != nullptr ? "\\" : " ");
                }
                std::cout << std::setw(width / 2) << "";
            }
            std::cout << std::endl;
        }
    }
}
int index, popValue,value;

//mock functions

int* disk_addMap(int* map)
{
    //int num = generateRandomNumber(10000000);
    //if (num % 2 == 0)
    //{
        int* map1 = (int*)allocate_memory(sizeof(int*), "Failed to allocate memory for disk control block", "disk_addMap");
        return map1;
    //}
    //return NULL;
}

//the function get pointer to map in the disk and delete this map from disk
bool disk_deleteMap(int* diskPointer) 
{
    return true;
}
void cache_deleteMap(int mapId)
{
}
//the function fill in the structer all the data which save befoe the computer closed,the function get  destenation,suorce,length;
void disk_loadDataForInitializeDataStructers(void* destination,void* startAddress,void* howManyToLoad)
{
}

void disk_saveDataFromStructersToDisk(void* data, void* startAddress, void* endAddrehowManyToLoadss)
{
}
bool disk_isThereEnoughSpace(int mapSize)
{
    //int num = generateRandomNumber(10000000);
    //if (num % 2 == 0)
    //{
    //    return true;
    //}
    //return false;
    return true;

}

TEST_CASE("test_disk_mng_initialize_CB")
{
    disk_mng_initialize_CB();
    CHECK(disk_mng_CB != NULL);
}

TEST_CASE("test_disk_mng_initialize")
{
	disk_mng_initialize();
}

//avlNode tests

TEST_CASE("test_avlNodeInfo_create")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo = avlNodeInfo_create(mapSize, indexArray);

	CHECK(avlNodeInfo->mapSize == mapSize);
	CHECK(avlNodeInfo->arrayIndex == indexArray);
	CHECK(avlNodeInfo->lru == 1);
}

TEST_CASE("test_avlNodeInfo_delete")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo = avlNodeInfo_create(mapSize, indexArray);
	avlNodeInfo_delete(avlNodeInfo);
}

TEST_CASE("test_avlNode_create")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode = avlNode_create(avlNodeInfo);

	CHECK(avlNode->avlNodeInfo == avlNodeInfo);
	CHECK(avlNode->height == 1);
	CHECK(avlNode->left  == NULL);
	CHECK(avlNode->right == NULL);
}

TEST_CASE("test_avlNode_delete")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode = avlNode_create(avlNodeInfo);
	avlNode_delete(avlNode);
}

TEST_CASE("test_avlNode_height")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode = avlNode_create(avlNodeInfo);

	CHECK(avlNode->height == avlNode_height(avlNode));
}

//avlTree tests

TEST_CASE("avlTree_firstInitialize")
{

}

TEST_CASE("avlTree_normalInitialize")
{

}

TEST_CASE("avlTree_saveData")
{

}

TEST_CASE("test_avlTree_rightRotate")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo1 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode1 = avlNode_create(avlNodeInfo1);

	AVLNodeInfo_t* avlNodeInfo2 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode2 = avlNode_create(avlNodeInfo2);

	AVLNodeInfo_t* avlNodeInfo3 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode3 = avlNode_create(avlNodeInfo3);

	avlNode1->left = avlNode2;
	avlNode2->left = avlNode3;

	avlNode2->height = std::max(avlNode_height(avlNode2->left), avlNode_height(avlNode2->right)) + 1;
	avlNode1->height = std::max(avlNode_height(avlNode1->left), avlNode_height(avlNode1->right)) + 1;

	AVLNode_t* newRoot = avlTree_rightRotate(avlNode1);

	CHECK(newRoot == avlNode2); 
	CHECK(newRoot->right == avlNode1); 
	CHECK(newRoot->left == avlNode3); 
	CHECK(avlNode1->left == nullptr);
	CHECK(avlNode1->height == 1); 
	CHECK(newRoot->height == 2);
}

TEST_CASE("test_avlTree_leftRotate")
{
    disk_mng_initialize();

	int mapSize = generateRandomNumber();
	int indexArray = generateRandomNumber();

	AVLNodeInfo_t* avlNodeInfo1 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode1 = avlNode_create(avlNodeInfo1);

	AVLNodeInfo_t* avlNodeInfo2 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode2 = avlNode_create(avlNodeInfo2);

	AVLNodeInfo_t* avlNodeInfo3 = avlNodeInfo_create(mapSize, indexArray);
	AVLNode_t* avlNode3 = avlNode_create(avlNodeInfo3);



	avlNode1->right = avlNode2;
	avlNode2->right = avlNode3;

	avlNode2->height = std::max(avlNode_height(avlNode2->left), avlNode_height(avlNode2->right)) + 1;
	avlNode1->height = std::max(avlNode_height(avlNode1->left), avlNode_height(avlNode1->right)) + 1;

	AVLNode_t* newRoot = avlTree_leftRotate(avlNode1);

	CHECK(newRoot == avlNode2); 
	CHECK(newRoot->left == avlNode1); 
	CHECK(newRoot->right == avlNode3); 
	CHECK(avlNode1->right == nullptr); 
	CHECK(avlNode1->height == 1); 
	CHECK(newRoot->height == 2);
}

TEST_CASE("avlTree_getBalance")
{
    disk_mng_initialize();

    int mapSize = generateRandomNumber();
    int indexArray = generateRandomNumber();


    AVLNodeInfo_t* info1 = avlNodeInfo_create(mapSize, indexArray);
    AVLNodeInfo_t* info2 = avlNodeInfo_create(mapSize, indexArray);
    AVLNodeInfo_t* info3 = avlNodeInfo_create(mapSize, indexArray);

    AVLNode_t* node1 = avlNode_create(info1);
    AVLNode_t* node2 = avlNode_create(info2);
    AVLNode_t* root = avlNode_create(info3);

    SUBCASE("Node is NULL") {
        CHECK(avlTree_getBalance(nullptr) == 0);
    }

    SUBCASE("Balance factor of a node with children having different heights") {
        root->left = node1;
        root->right = node2;
        node1->height = 3;
        node2->height = 1;
        root->height = 4; 
        CHECK(avlTree_getBalance(root) == 2);
    }

    SUBCASE("Balance factor of a node with both children having the same height") {
        root->left = node1;
        root->right = node2;
        node1->height = 2;
        node2->height = 2;
        root->height = 3; 
        CHECK(avlTree_getBalance(root) == 0);
    }

    SUBCASE("Balance factor of a node with one child") {
        root->left = node1;
        root->right = nullptr;
        node1->height = 2;
        root->height = 3; 
        CHECK(avlTree_getBalance(root) == 2);
    }
}
TEST_CASE("test_avlTree_minValueNode") {
    disk_mng_initialize();

    int mapSize1 = generateRandomNumber();
    int indexArray1 = generateRandomNumber();

    int mapSize2 = generateRandomNumber();
    int indexArray2 = generateRandomNumber();

    int mapSize3 = generateRandomNumber();
    int indexArray3 = generateRandomNumber();

    AVLNodeInfo_t* info1 = avlNodeInfo_create(mapSize1, indexArray1);
    AVLNodeInfo_t* info2 = avlNodeInfo_create(mapSize2, indexArray2);
    AVLNodeInfo_t* info3 = avlNodeInfo_create(mapSize3, indexArray3);

    AVLNode_t* node1 = avlNode_create(info1);
    AVLNode_t* node2 = avlNode_create(info2);
    AVLNode_t* node3 = avlNode_create(info3);

    SUBCASE("Node with no left child") {
        CHECK(avlTree_minValueNode(node1) == node1);
    }
    node1->left = node2; 
    node2->left = node3; 

    SUBCASE("Node with left child") {
        CHECK(avlTree_minValueNode(node1) == node3);
    }
}
TEST_CASE("test_avlTree_insert") {
    disk_mng_initialize();

    SUBCASE("Insert into an empty tree") {
        int mapSize = generateRandomNumber();
        int arrayIndex = generateRandomNumber();

        AVLNodeInfo_t* info = avlNodeInfo_create(mapSize, arrayIndex);
        avlTree_insertElement(info);

        CHECK(disk_mng_CB->disk_SortByMapSize->root != nullptr);
        CHECK(disk_mng_CB->disk_SortByMapSize->root->avlNodeInfo->mapSize == mapSize);
        CHECK(disk_mng_CB->disk_SortByMapSize->root->avlNodeInfo->lru == 1);
        CHECK(disk_mng_CB->disk_SortByMapSize->totalElements == 1);

        printf("first tree\n");
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printf("\n");
    }

    SUBCASE("Insert nodes and check balancing") {

        for (int i = 0; i < 7; ++i) {
            int mapSize = generateRandomNumber();
            int arrayIndex = generateRandomNumber();

            AVLNodeInfo_t* info = avlNodeInfo_create(mapSize, arrayIndex);
            avlTree_insertElement(info);
        }

        CHECK(disk_mng_CB->disk_SortByMapSize->root != nullptr);
        CHECK(disk_mng_CB->disk_SortByMapSize->totalElements == 7);

        printf("second tree\n");
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printf("\n");

    }

    SUBCASE("Insert duplicate mapSize") {
        int mapSize = generateRandomNumber();
        int arrayIndex1 = generateRandomNumber();
        int arrayIndex2 = generateRandomNumber();

        AVLNodeInfo_t* info1 = avlNodeInfo_create(mapSize, arrayIndex1);
        AVLNodeInfo_t* info2 = avlNodeInfo_create(mapSize, arrayIndex2);

        avlTree_insertElement(info1);
        avlTree_insertElement(info2);

        CHECK(disk_mng_CB->disk_SortByMapSize->root != nullptr);
        CHECK(disk_mng_CB->disk_SortByMapSize->root->right != nullptr);
        CHECK(disk_mng_CB->disk_SortByMapSize->root->left == nullptr);

        CHECK(disk_mng_CB->disk_SortByMapSize->root->right->avlNodeInfo->mapSize == mapSize);
        CHECK(disk_mng_CB->disk_SortByMapSize->root->right->avlNodeInfo->arrayIndex == arrayIndex2);     
        CHECK(disk_mng_CB->disk_SortByMapSize->totalElements == 2);

        printf("third tree\n");
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printf("\n");
    }
}
TEST_CASE("test_avlTree_FindingTheNodeThatIsSuitableForDeletion") {
    disk_mng_initialize();

    SUBCASE("Find eligible node for deletion") {
        // Insert nodes into the AVL tree with different LRU values
        for (int i = 0; i < 5; ++i) {
            int mapSize = generateRandomNumber();
            int arrayIndex = generateRandomNumber();
            int lru = (i == 3) ? disk_mng_CB->disk_SortByMapSize->lruCounter * 0.6 : generateRandomNumber();

            AVLNodeInfo_t* info = avlNodeInfo_create(mapSize, arrayIndex);
            avlTree_insertElement(info);
        }

        AVLNode_t* result = avlTree_FindingTheNodeThatIsSuitableForDeletion(disk_mng_CB->disk_SortByMapSize->root);

        CHECK(result != nullptr);
        CHECK(result->avlNodeInfo->lru <= disk_mng_CB->disk_SortByMapSize->lruCounter * 0.7);
        printf("Node suitable for deletion:\n");
        printNode(result);
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printTreeDetails(disk_mng_CB->disk_SortByMapSize->root);
        printf("%d\n", disk_mng_CB->disk_SortByMapSize->totalElements);

        printf("\n");

    }

    SUBCASE("All nodes are eligible for deletion") {
        // Insert nodes with LRU values such that all are eligible for deletion
        for (int i = 0; i < 5; ++i) {
            int mapSize = generateRandomNumber();
            int arrayIndex = generateRandomNumber();
            int lru = generateRandomNumber();

            AVLNodeInfo_t* info = avlNodeInfo_create(mapSize, arrayIndex);
            avlTree_insertElement(info);
        }

        AVLNode_t* result = avlTree_FindingTheNodeThatIsSuitableForDeletion(disk_mng_CB->disk_SortByMapSize->root);

        CHECK(result != nullptr);
        CHECK(result->avlNodeInfo->lru <= disk_mng_CB->disk_SortByMapSize->lruCounter * 0.7);
        printf("Node suitable for deletion:\n");
        printNode(result);
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printTreeDetails(disk_mng_CB->disk_SortByMapSize->root);
        printf("%d\n", disk_mng_CB->disk_SortByMapSize->totalElements);

        printf("\n");

    }

    SUBCASE("No node is eligible for deletion") {
        // Insert nodes with LRU values such that none are eligible for deletion
        for (int i = 0; i < 5; ++i) {
            int mapSize = generateRandomNumber();
            int arrayIndex = generateRandomNumber();
            int lru = disk_mng_CB->disk_SortByMapSize->lruCounter * 0.8;

            AVLNodeInfo_t* info = avlNodeInfo_create(mapSize, arrayIndex);
            avlTree_insertElement(info);
        }

        AVLNode_t* result = avlTree_FindingTheNodeThatIsSuitableForDeletion(disk_mng_CB->disk_SortByMapSize->root);

        CHECK(result != nullptr);
        CHECK(result->avlNodeInfo->mapSize == avlTree_FindingTheNodeThatIsSuitableForDeletion(disk_mng_CB->disk_SortByMapSize->root)->avlNodeInfo->mapSize);
        printf("Node with largest mapSize:\n");
        printNode(result);
        printTree(disk_mng_CB->disk_SortByMapSize->root);
        printTreeDetails(disk_mng_CB->disk_SortByMapSize->root);
        printf("%d\n", disk_mng_CB->disk_SortByMapSize->totalElements);

        printf("\n");

    }
}
TEST_CASE("test_avlTree_deleteNode") {
    disk_mng_initialize();

    for (int i = 0; i < 10; i++)
    {
        AVLNodeInfo_t* info1 = avlNodeInfo_create(generateRandomNumber(), generateRandomNumber());
        avlTree_insertElement(info1);
    }
    printf("Tree before deletion:\n");
    printTree(disk_mng_CB->disk_SortByMapSize->root);

    AVLNode_t* nodeToDelete = avlTree_FindingTheNodeThatIsSuitableForDeletion(disk_mng_CB->disk_SortByMapSize->root);
    if (nodeToDelete!=NULL)
    {
        printf("the node to delete:\n");
        printNode(nodeToDelete);

        disk_mng_CB->disk_SortByMapSize->root = avlTree_deleteNode(disk_mng_CB->disk_SortByMapSize->root, nodeToDelete);

        printf("Tree after deletion:\n");
        printTree(disk_mng_CB->disk_SortByMapSize->root);

    }
}


//stack tests

TEST_CASE("test_stack_firstInitialize")
{
    disk_mng_initialize();
    for (int i = 0; i < DISK_SIZE; i++)
    {
        
        stack_push(i);
    }

    for (int i =DISK_SIZE-1; i >0; i--)
    {
        CHECK( stack_pop() == i);
    }
}


TEST_CASE("test_stack_normalInitialize")
{
    disk_mng_initialize();
}

TEST_CASE("stack_saveData")
{

}

TEST_CASE("test_stack_push")
{
    disk_mng_initialize();
    for (size_t i = 0; i < DISK_SIZE; i++)
    {  
    index = generateRandomNumber();
    stack_push(index);
    popValue = stack_pop();
    CHECK(popValue == index);
    }

}
TEST_CASE("test_stack_pop")
{
    disk_mng_initialize();
    for (size_t i = 4; i < 0; i++)
    {
        value = stack_pop();
        CHECK(value !=stack_top());
    }
}
TEST_CASE("test_stack_top")
{
    disk_mng_initialize();
    for (size_t i = DISK_SIZE-1; i < 0; i--)
    {
        value = stack_top();
        stack_pop();
        CHECK(value == i);
    }
}
TEST_CASE("test_stack_is_empty")
{
    disk_mng_initialize();
    for (size_t i = 0; i < DISK_SIZE; i++)
    {
        stack_pop();
    }
    CHECK(stack_is_empty());

}

TEST_CASE("test_stackNode_create")
{
    disk_mng_initialize();
    int index = generateRandomNumber();
    StackNode_t* new_node = stackNode_create(index);
    CHECK(new_node->freeIndex == index);
    CHECK(new_node->next == disk_mng_CB->diskFreeIndexesInArray->top);
}

//array tests

TEST_CASE("array_firstInitialize")
{

}

TEST_CASE("array_normalInitialize")
{

}

TEST_CASE("array_saveData")
{

}

TEST_CASE("test_array_deleteFromArray")
{
    disk_mng_initialize();
    int index = generateRandomNumber();
    array_deleteFromArray(index);
    CHECK(disk_mng_CB->arrayForAllMApsInformation[index]== NULL);
}

TEST_CASE("test_arrayInfo_create")
{
    disk_mng_initialize();
    int * diskPointer = NULL;
    int size = generateRandomNumber();
    Point_t topLeft;
    topLeft.x = generateRandomNumber();
    topLeft.y = generateRandomNumber();
    Point_t bottomRight;
    bottomRight.x = generateRandomNumber();
    bottomRight.y = generateRandomNumber();
    MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
    ArrayInfo_t* arrayInfo= arrayInfo_create(diskPointer, size, mapRange);
    CHECK(arrayInfo->mapid == 1);
    CHECK(arrayInfo->diskPointer == NULL);
    CHECK(arrayInfo->size == size);
    CHECK(arrayInfo->range == mapRange);
}

TEST_CASE("test_array_addToArray")
{
    disk_mng_initialize(); 
    for (int i = 0; i < DISK_SIZE; i++)
    {
        int* diskPointer = NULL;
        int size = generateRandomNumber();
        Point_t topLeft;
        topLeft.x = generateRandomNumber();
        topLeft.y = generateRandomNumber();
        Point_t bottomRight;
        bottomRight.x = generateRandomNumber();
        bottomRight.y = generateRandomNumber();
        MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
        ArrayInfo_t* arrayInfo = arrayInfo_create(diskPointer, size, mapRange);
        int index = stack_pop();
        array_addToArray(arrayInfo, index);
        CHECK(disk_mng_CB->arrayForAllMApsInformation[index] == arrayInfo);
        printf("mapId%d\n", disk_mng_CB->mapIdIndex);

    }
}

//range functions
TEST_CASE("test_mapRange_create")
{
    disk_mng_initialize();
    Point_t topLeft;
    topLeft.x = generateRandomNumber();
    topLeft.y = generateRandomNumber();
    Point_t bottomRight;
    bottomRight.x = generateRandomNumber();
    bottomRight.y = generateRandomNumber();
    MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
    CHECK(mapRange->bottomRight.x == bottomRight.x);
    CHECK(mapRange->bottomRight.y == bottomRight.y);
    CHECK(mapRange->topLeft.x == topLeft.x);
    CHECK(mapRange->topLeft.y == topLeft.y);
}

TEST_CASE("test_disk_mng_addMap")
{
    disk_mng_initialize();
    for (int i = 0; i < 20; i++)
    {
        Point_t topLeft;
        topLeft.x = generateRandomNumber();
        topLeft.y = generateRandomNumber();
        Point_t bottomRight;
        bottomRight.x = generateRandomNumber();
        bottomRight.y = generateRandomNumber();
        MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
        int size = generateRandomNumber();
        int* map = (int*)allocate_memory(sizeof(int*), "Failed to allocate memory for map", "test_disk_mng_addMap");
        disk_mng_addMap(mapRange, size, map);
        printf("totalElements%d\n", disk_mng_CB->disk_SortByMapSize->totalElements);
        printf("mapIdIndex%d\n", disk_mng_CB->mapIdIndex);

    }

    REQUIRE(disk_mng_CB->disk_SortByMapSize->totalElements == 20);

}

TEST_CASE("Test disk_mng_deleteMapFromDiskManagementDataStructures") {
    disk_mng_initialize(); 
    SUBCASE("Delete a single map when disk is full") {
        // Add maps until the disk is full
        for (int i = 0; i < 5; i++) {
            Point_t topLeft;
            topLeft.x = generateRandomNumber();
            topLeft.y = generateRandomNumber();
            Point_t bottomRight;
            bottomRight.x = generateRandomNumber();
            bottomRight.y = generateRandomNumber();
            MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
            int size = generateRandomNumber();
            int* map = (int*)allocate_memory(sizeof(int*), "Failed to allocate memory for map", "test_disk_mng_addMap");
            disk_mng_addMap(mapRange, size, map); // Add maps to the disk
            printf("%d\n", disk_mng_CB->disk_SortByMapSize->totalElements);
        }

        // Verify that the disk is full and needs deletion
        REQUIRE(disk_mng_CB->disk_SortByMapSize->totalElements == 5);

        // Perform deletion
        int sizeToFree = generateRandomNumber(); // Random size to free
        disk_mng_delete(sizeToFree);

        // Ensure that space has been freed
        REQUIRE(disk_mng_CB->disk_SortByMapSize->totalElements < 5);
    }

}

TEST_CASE("Test disk_mng_delete") {
    disk_mng_initialize(); // Initialize the disk management control block

    SUBCASE("Delete multiple maps until sufficient space is freed") {
        // Add maps until the disk is full
        for (int i = 0; i < 10; i++) {
            Point_t topLeft;
            topLeft.x = generateRandomNumber();
            topLeft.y = generateRandomNumber();
            Point_t bottomRight;
            bottomRight.x = generateRandomNumber();
            bottomRight.y = generateRandomNumber();
            MapRange_t* mapRange = mapRange_create(bottomRight, topLeft);
            int size = generateRandomNumber();
            int* map = (int*)allocate_memory(sizeof(int*), "Failed to allocate memory for map", "test_disk_mng_addMap");
            disk_mng_addMap(mapRange, size, map); // Add maps to the disk
        }

        // Perform multiple deletions to free space
        int totalSizeToFree = generateRandomNumber();
        disk_mng_delete(totalSizeToFree);

        // Ensure that sufficient space has been freed
        REQUIRE(disk_mng_CB->disk_SortByMapSize->totalElements < 10);
        REQUIRE(totalSizeToFree <= 0); // Verify that enough space was freed
    }
}

