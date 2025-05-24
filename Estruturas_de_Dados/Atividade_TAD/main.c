#include "tad.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
int op=0,x=0;
Fila a=Inicializar();
	do{
	    printf("\n-----------------------------MENU-----------------------------\n");
	    printf("1. Inserir um elemento na fila\n");
	    printf("2. Remover um elemento da fila (imprima o elemento removido)\n");
	    printf("3. Imprimir a fila\n");
	    printf("4. Sair\n");
	    printf("\n--------------------------------------------------------------\n");
	    scanf("%d",&op);
        printf("\n--------------------------------------------------------------\n");

    	switch(op){
    	    case 1:
    	        printf("\n-----------Inserir um elemento-----------");
                printf("\nDigite o elemento: ");
                scanf("%d",&x);
                PushFila(a,x);
                printf("\n------------------------------------------\n");
                break;
	        case 2:
	            printf("\n-----------Remover um elemento-----------");
                //Pop(p,&x);
                printf("\nO elemento %d foi removido da pilha",x);
                printf("\n------------------------------------------\n");
                break;
            case 3:
	            printf("\n-----------Imprimir Pilha-------------------");
               // Imprimir(p);
                printf("\n------------------------------------------\n");
                break;
	        default:
                printf("\nOpção invalida,tente novamente");
	            break;
        }   
	}while(op!=4);
}