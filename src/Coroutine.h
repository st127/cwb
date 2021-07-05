#ifndef __CWB_COROUTINE_H_INC
#define __CWB_COROUTINE_H_INC

#include"Conf.h"
#include<ucontext.h>

#define CWB_COROUTINE_SUSPEND	0x00	
#define CWB_COROUTINE_RUNNING	0x01
#define CWB_COROUTINE_DEAD	0x02
#define CWB_COROUTINE_ERROR	0x03

typedef struct __Cwb_Coroutine{
	ucontext_t coCtx,mainCtx;
	short int status;
}Cwb_Coroutine;

typedef int (*Cwb_Coroutine_Func)(Cwb_Coroutine *co,void *data);

Cwb_Coroutine *cwb_coroutine_create(Cwb_Coroutine_Func func,
				    void *data);
short int cwb_coroutine_resume(Cwb_Coroutine *co);
void cwb_coroutine_yield(Cwb_Coroutine *co);
short int cwb_coroutine_status(Cwb_Coroutine *co);
void cwb_coroutine_destroy(Cwb_Coroutine *co);

#endif
