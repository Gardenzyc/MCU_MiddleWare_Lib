/*
 * cryptoAESInterface.c
 *
 *  Created on: 2021年6月3日
 *      Author: zhuyc
 */
#include "cryptoAESInterface.h"
#include "cryptoAES.h"

static uint8_t s_key[] = { 0x1a, 0x7e, 0x15, 0x16, 0x68, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x75, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
static uint8_t s_iv[]  = { 0x26, 0x51, 0x32, 0x63, 0x14, 0x05, 0x06, 0x07, 0x08, 0x79, 0x2a, 0x6b, 0x8c, 0x0d, 0x0e, 0xef };

static struct AES_ctx s_cbc;

//init AES LIB
void AES_INIT()
{
	AES_init_ctx_iv(&s_cbc, s_key, s_iv);
}

//encode
void AES_ENCRYPT(uint8_t* buf, size_t length)
{
	AES_CBC_encrypt_buffer(&s_cbc, buf, length);
}

//decode
void AES_DECRYPT(uint8_t* buf, size_t length)
{
	AES_CBC_decrypt_buffer(&s_cbc, buf, length);
}


