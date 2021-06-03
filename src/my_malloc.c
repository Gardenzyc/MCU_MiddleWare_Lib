/*
 * my_malloc.c
 *
 *  Created on: May 20, 2021
 *      Author: zhuyc
 */
#include "my_malloc.h"

typedef enum{
	MALLOC_FAILED = 0xffffffff,
	FREE_FAILED = 0x2,
	UNINIT_ERROR = 0x01
}ERROR_CODE;

__attribute__((aligned(4))) static uint8_t s_memPool[MEM_MAX_SIZE];//memory pool

static uint16_t s_memMap[MEM_TABLE_NUM];//page num

static void _myMemInit(void);

static my_malloc_dev_t s_malloc_dev = {
		_myMemInit,
		s_memPool,
		s_memMap,
		0
};

void myMemcopy(void* des, void* src, uint32_t size)
{
	if(NULL == des || NULL == src)
		return;

	uint8_t *srcTmp = src;
	uint8_t *desTmp = des;
	while(size--) *desTmp++ = *srcTmp++;

	return;
}

void myMemset(void* ptr, uint8_t byte, uint32_t size)
{
	if(NULL == ptr)
		return;

	uint8_t* ptrTmp = ptr;
	while(size--) *ptrTmp++ = byte;

	return;
}

static void _myMemInit(void)
{
	myMemset(s_malloc_dev.memBase, 0, sizeof(s_malloc_dev.memBase));
	myMemset(s_malloc_dev.memMap, 0, sizeof(s_malloc_dev.memMap));

	s_malloc_dev.isMemRdy = 1;
}

static uint32_t _myMemMalloc(uint32_t size)
{
	uint32_t num = 0;
	uint16_t blockNeed = (size/MEM_PER_BLOCK_SIZE) + ((size%MEM_PER_BLOCK_SIZE)?1:0);//the blocks needed
	uint16_t blockContinue = 0;//the remain continue blocks
	if(!s_malloc_dev.isMemRdy)
		s_malloc_dev.initFun();

	if(0 == size)
		return MALLOC_FAILED;

	//search all blocks for continue memory space
	for(num=MEM_TABLE_NUM-1; num>=0; num--)
	{
		if(s_malloc_dev.memMap[num]) blockContinue++;
		else blockContinue = 0;

		if(blockContinue == blockNeed)
		{
			/* record memory used */
			myMemset(&s_malloc_dev.memMap[num], blockContinue, blockContinue);
			return (num*MEM_PER_BLOCK_SIZE);
		}
	}

	return MALLOC_FAILED;
}


static uint8_t _myMemFree(uint32_t offSize)
{
	if(!s_malloc_dev.isMemRdy)
	{
		s_malloc_dev.initFun();
		return UNINIT_ERROR;
	}

	if(offSize < MEM_MAX_SIZE)
	{
		uint16_t curBlock = offSize/MEM_PER_BLOCK_SIZE;
		uint16_t curPageSize = s_malloc_dev.memMap[curBlock];
		myMemset(&s_malloc_dev.memMap[curBlock], 0, curPageSize);
	}
	else
	{
		return FREE_FAILED;
	}

	return 0;
}

//return:1~100% * 100 = 1~100
uint8_t myMemUsed(void)
{
	uint32_t used = 0;
	uint32_t i = 0;
	for(; i<MEM_TABLE_NUM; i++)
		if(s_malloc_dev.memMap[i]) used++;

	return (used/MEM_TABLE_NUM)*100;
}

// functions supply for extern module
void myMemInit(void)
{
	s_malloc_dev.initFun();
}

void* myMemMalloc(uint32_t size)
{
	uint32_t offSet = _myMemMalloc(size);
	if(MALLOC_FAILED == offSet)
		return NULL;

	return (s_malloc_dev.memBase+offSet);
}

void myMemFree(void *ptr)
{
	if(NULL == ptr)
		return;

	uint32_t offSet = (uint32_t)ptr - (uint32_t)s_malloc_dev.memBase;
	_myMemFree(offSet);
}

void* myMemRealloc(void *ptr, uint32_t size)
{
	//realloc new ptr
	void* newPtr = myMemMalloc(size);
	//copy to new mem
	myMemcopy(newPtr, ptr, size);
	//free old mem
	myMemFree(ptr);

	return newPtr;
}
