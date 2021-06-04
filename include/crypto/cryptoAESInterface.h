/*
 * cryptoAESInterface.h
 *
 *  Created on: 2021年6月3日
 *      Author: zhuyc
 */
//workmode:CBC
#ifndef __CRYPTO_AES_INTERFACE_H__
#define __CRYPTO_AES_INTERFACE_H__

#include "my_malloc_cfg.h"

#ifdef __cplusplus
extern "C"{
#endif

#define AES_CBC 1
//key length
#define AES_128 1

//init AES LIB
void AES_INIT();
//encode
void AES_ENCRYPT(uint8_t* buf, size_t length);
//decode
void AES_DECRYPT(uint8_t* buf, size_t length);

#ifdef __cplusplus
}
#endif

#endif
