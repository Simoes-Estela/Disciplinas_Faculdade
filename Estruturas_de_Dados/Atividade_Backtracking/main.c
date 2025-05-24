/******************************************************************************
◆ Exercício para postagem no Classroom:

2. Todas as combinações de {15, 31, 55, 44}, de tamanho n, cuja soma dos elementos da combinação é par.
3. Dado um valor em centavos, imprimir todas as maneiras de representá-lo utilizando moedas de 1, 5, 10, 25 e 50 centavos.
Exemplo: valor = 6 centavos, temos: 6 moedas de 1 (nenhuma das outras) ou 1 de 5, 1 de 1 (nenhuma das restantes)
*******************************************************************************/
#include <stdio.h>

//1. Todas as combinações de {a, e, i}, de tamanho n, que o número de a's é maior que a soma dos totais de e's e de i's
void combinações1(char *vetorAEI,int pos, int n,char *vet){
int i,CountA;
    if (pos=n){
        int Count0=0;
        for(i=0;i<n;i++){
            if(vet[i]=='a'){
                CountA++;
            }
        }
        if(CountA>n/2){
            for(i=0;i<n;i++){
                printf("%d",vet[i]);
            }
        printf("\n");
        }
    }else{
        for(i=0;i<n;i++){
        vet[pos]=vetorAEI[i];
        combinações1(vetorAEI,pos+1,n,vet);
        }
    }
}


int main()
{
    printf("Digite o tamanho do vetor: ");
    int tamanho;
    scanf("%d",&tamanho);
    char vet[tamanho],vetor[3]={'a','e','i'};
    combinações1(vetor,0,tamanho,vet);
}