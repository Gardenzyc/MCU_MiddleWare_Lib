/*
 * my_malloc.h
 *
 *  Created on: May 20, 2021
 *      Author: zhuyc
 */

#ifndef INCLUDE_MY_MALLOC_H_
#define INCLUDE_MY_MALLOC_H_

#include "my_malloc_cfg.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef NULL
#define NULL 0
#endif

#define MEM_PER_BLOCK_SIZE 	32									//per memory block size
#define MEM_MAX_SIZE 		20*1024								//total memory block size
#define MEM_TABLE_NUM 		(MEM_MAX_SIZE/MEM_PER_BLOCK_SIZE)	//memory page number

typedef struct{
	void (*initFun)(void);
	uint8_t *memBase;
	uint16_t *memMap;
	uint8_t isMemRdy;
}my_malloc_dev_t;

extern my_malloc_dev_t g_mallocDev;

void myMemInit(void);
void* myMemMalloc(uint32_t size);
void myMemFree(void *ptr);
void* myMemRealloc(void *ptr, uint32_t size);

void myMemset(void *ptr, uint8_t data, uint32_t size);
void myMemcopy(void *des, void *src, uint32_t size);
//return:1~100% * 100 = 1~100
uint8_t myMemUsed(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_MY_MALLOC_H_ */
