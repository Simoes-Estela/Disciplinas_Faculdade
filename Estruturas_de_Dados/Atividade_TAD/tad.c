#include "tad.h"
#include<stdio.h>
#include<stdlib.h>

#define N 100

struct fila{
    int vet[N];
	int topo;//Proxima posição a ser inserida
};

Fila Inicializar(){
    Fila f=(Fila) malloc (sizeof(Fila));
    f->topo=0;
    return f;
    printf("A fila foi inicializada\n");
}
int Cheia(Fila f){
    if(f->topo=(N-1)){
        return 0;}else{
        return 1;
    }
}

int PushFila(Fila f,int x){
    if(Cheia(f)==1){
        f->vet[f->topo]=x;
        f->topo++;
    }else{
        printf("A FILA ESTÁ CHEIA\n");
    }
        
}
