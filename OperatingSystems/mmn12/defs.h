/*
 * creator: solekiller 
 * */
#define BUCKETS 9999
#define BUCKET_DEPTH 20
#define true 1
#define false 0

typedef int bool;
static double heapSize = 0;
bool mallocCalled = false;
unsigned totalAllocated = 0;
typedef struct t_cell {
	void *p;
	void **pp;
} t_cell;
static t_cell hashTable[BUCKETS][BUCKET_DEPTH];
int hashFunction(void *);
bool isEmpty(t_cell cell);
int add(void **pp);
void removePointer(void **pp);
void removePointers(void **pp);
void initializeHashTable();
void updatePointerValue(void **destination, void **source);
void printHashTable();
void updateAddressesInHashTable(unsigned int startAddy, unsigned int endAddy, unsigned int offset);
bool timeHasPassed(struct timeval* tv, unsigned int dt);
bool needCompaction();
