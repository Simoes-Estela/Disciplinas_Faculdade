/******************************************************************************

implemente uma minheap, apresentando na tela um menu com as seguintes opções:
1. Inserir um elemento x na heap
2. Remover um elemento-o elemento removido deve ser impresso na tela
3. Imprimir a heap
4. Sair

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalDeElementos=0;
//Funções Auxiliares

int indiceFilhoEsq(int x){
    int indice= (2*x)+1;
    if (x >= totalDeElementos || indice >= totalDeElementos){
        return -1;
    }else{
        return indice;
    }
}

int indiceFilhoDir(int x){
    int indice= (2 - x) + 2;
    if (x >=totalDeElementos || indice>=totalDeElementos){
        return -1;
    }else{
        return indice;
    }
}

int indicePai(int x){
    int indice = (int) floor ((x-1)/2);
    if (x <= 0 || x >= totalDeElementos){
        return -1;
    }else{
        return indice;
    }
}

void Inserir(int *heap, int x){
    heap[totalDeElementos] = x;
    totalDeElementos++;
    AjustarSubindo(heap, totalDeElementos -1);
}

void AjustarSubindo(int *heap, int pos){
    if (pos != -1){
        int pai=indicePai(pos);
        if (pai != -1){
            if (heap[pos]<heap[pai]){
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                AjustarSubindo(heap,pai);
            }
        }
    }
}

int Remover (int *heap){
    if (totalDeElementos == 0){
        return -1;
    }else{
        int retorno = heap[0];
        heap[0] = heap[totalDeElementos-1];
        totalDeElementos--;
        AjustarDescendo(heap,0);
        return retorno;
    }
}

void AjustarDescendo(int *heap, int pos){
    if( pos!=-1 && indiceFilhoEsq(pos) !=-1){
        int indiceMenorFilho = indiceFilhoEsq (pos);
        if (indiceFilhoDir(pos)!= -1 && heap[indiceFilhoDir(pos)]<heap[indiceMenorFilho]){
            indiceMenorFilho=indiceFilhoDir(pos);
        }
        if(heap[indiceMenorFilho]<heap[pos]){
            int aux = heap[pos];
            heap[pos] = heap[indiceMenorFilho];
            heap[indiceMenorFilho] = aux;
            AjustarDescendo(heap,indiceMenorFilho);
        
            
        }
        
    }
}

int main(){

int i,op=0,ValorIndice;
int *Heap;
printf("Digite a quantidade de elementos da Heap: ");
scanf("%d",&ValorIndice);
Heap = malloc( totalDeElementos * sizeof(int) );
do {
printf("\nMenu\n");
printf("1. Inserir um elemento x na heap\n");
printf("2. Remover um elemento-o elemento removido deve ser impresso na tela\n");
printf("3. Imprimir a heap\n");
printf("4. Sair\n");
scanf("%d",&op);
    switch(op){
        case 1:
            printf("Opção escolhida: Inserir\n");
            printf("Digite o valor:");
            int num;
            scanf("%d",&num);
            Inserir(Heap,num);
        break;
        
        case 2:
            Remover(Heap);
        break;
        
        case 3:
            for(i=0;i<totalDeElementos;i++){
                printf("|%d| ",Heap[i]);
             } 
        break;
    }
}while(op!=4);


}



