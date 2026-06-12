#ifndef punto1.h
#define punto1.h
#include <stdint.h> //para mas tipos de variables
#include "stm32f103xb.h"

typedef struct{
GPIO_TypeDef* puerto;
int pines[4];
unsigned int grado_inicial;
unsigned int grado_final;
}motores_t;


void mPaP_Init(motores_t*);
void mPap_Steps(motores_t*);

#endif