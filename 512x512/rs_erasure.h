#ifndef _RS_DECODER_ERASURE_H_
#define _RS_DECODER_ERASURE_H_

#include "string.h"


#define PARA_N	255
#define PARA_K	241
#define PARA_M	8


#define PARA_N1	84
#define PARA_K1	70
#define PARA_FRAMESIZE	240
#define PARA_N_K		(PARA_N-PARA_K)

// #define PARA_N	255
// #define PARA_K	85
// #define PARA_M	8
// #define PARA_N1	255
// #define PARA_K1	85
// #define PARA_FRAMESIZE	242
// #define PARA_N_K		(PARA_N-PARA_K)
#ifdef __cplusplus
extern "C" {
#endif
	


void rs_enc(unsigned char msg[],unsigned char code[]);
void rs_dec(unsigned char rx[],unsigned char decode[],unsigned char err_pos[],int num_err);

#ifdef __cplusplus
}
#endif

#endif
