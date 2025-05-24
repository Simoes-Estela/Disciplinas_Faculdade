#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
/*Implemente um programa que apresente na tela o seguinte menu de opções:
1- Ler uma árvore de um arquivo fornecido pelo usuário
2- Imprimir a árvore (opções: pré-ordem; em-ordem; pós-ordem; e em largura)
3- Verificar se um elemento x existe na árvore
4- Contar o número de elementos na árvore
5- Imprimir os nós folhas da árvore
6- Verificar se uma árvore está balanceada
7- Verificar se uma árvore é cheia
8- Imprimir o nível de um nó x
9- Sair*/

//Struct da Árvore
typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;
arvore *LerArqArvore(FILE *arq){
    char c; //tipo char para ler os '()'
    int num;

    fscanf(arq,"%c",&c); //lê '('
    fscanf(arq,"%d",&num); //ler os nós ou raizes


    if(num==-1){
        fscanf(arq,"%c",&c);
        return NULL;
    }else{
        arvore *a=(arvore*)malloc(sizeof(arvore));
        a->info=num;
        a->esq=LerArqArvore(arq); //Sub Esquerda
        a->dir=LerArqArvore(arq);//Sub Direita
        fscanf(arq,"%c",&c); //Lê ')'
        return a;
        
    }

}
void PreOrdem(arvore *a){
    if(a!=NULL){
        printf("%d ",a->info);
        PreOrdem(a->esq);
        PreOrdem(a->dir);
    }
}
void EmOrdem(arvore *a){
    if (a!=NULL){
        EmOrdem(a->esq);
        printf("%d ",a->info);
        EmOrdem(a->dir);
    }
}
void PosOrdem(arvore *a){
    if(a!=NULL){
        PosOrdem(a->esq);
        PosOrdem(a->dir);
        printf("%d ",a->info);
    }
}
void ImprimirNivel (arvore *a, int cont, int nivel) {
    if (a != NULL) {
        if (cont == nivel){
           printf ("%d ", a->info);
        }else{
            ImprimirNivel(a->esq, cont+1, nivel); //Subesq
            ImprimirNivel(a->dir, cont+1, nivel); //Subdir
        }
    }
}
void ImprimirLargura (arvore *a) {
    if (a!=NULL) {
        int i;
        int h = Altura(a);
        for (i=0; i<h; i++) {
            ImprimirNivel(a, 0, i);
            printf("\n");
        }
    }
}
int Existe(arvore *a, int x){
int aux=0;
    if(a!=NULL){
        if(a->info==x){
            return 1;
        }else{
           aux=Existe(a->esq,x);
           if(aux==1){
               return 1;
           }else{
               aux=Existe(a->dir,x);
           }
        }
    }else{
        return 0;
    }
}
int ContExiste(arvore *a,int x){
int contador=0;
    if(a!=NULL){
        if(a->info==x){
            return 1+ContExiste(a->esq,x)+ContExiste(a->dir,x);
        }else{
            return 0+ContExiste(a->esq,x)+ContExiste(a->dir,x);
        }
    }else{
        return 0;
    }
printf("O numero foi achado %d vez/vezes",contador);
}
void NosFolhas(arvore *a){
    if(a!=NULL){
        if(a->dir==NULL && a->esq==NULL){
            printf(" %d ",a->info);
        }else{
            NosFolhas(a->esq);
            NosFolhas(a->dir);
        }
        
    }
}
int Altura(arvore *a){
if(a==NULL){
        return 0;
    }
    else{
        int esq = Altura(a->esq);
        int dir = Altura(a->dir);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
int Balanceada(arvore *a){
   int b1=Altura(a->esq)-Altura(a->dir);
   int b2=Altura(a->dir)-Altura(a->esq);
    if ((b1>1)||(b2>1)){
        return 0;
    }else{
        return 1;
    }
}
int Cheia(arvore *a){
    if (a!=NULL){
        return 1+Cheia(a->esq)+Cheia(a->dir);
    }else{
        return 0;
    }
}
void Nivel(arvore *a,int x,int count){
  if(a!=NULL){
      if(a->info==x){
          printf ("O valor foi encontrado no nível %d",count);
      }else if(a->info!=x){
          Nivel(a->esq,x,count+1);
          Nivel(a->dir,x,count+1);
      }
  }
}

int main(){
setlocale(LC_ALL, "Portuguese");
arvore *a;
int op=0,num=0;//Opção do menu escolhida pelo usuario

do{
    //system("clear"); //Comando para limpar a tela    
    printf("\n---------------------------------------------------------------------------------\n");
    printf("                    MENU                      \n");
    printf("---------------------------------------------------------------------------------\n");
    printf("1- Ler uma árvore de um arquivo fornecido pelo usuário \n");
    printf("2- Imprimir a árvore (opções: pré-ordem; em-ordem; pós-ordem; e em largura) \n");
    printf("3- Verificar se um elemento x existe na árvore \n");
    printf("4- Contar o número de elementos na árvore \n");
    printf("5- Imprimir os nós folhas da árvore \n");
    printf("6- Verificar se uma árvore está balanceada \n");
    printf("7- Verificar se uma árvore é cheia \n");
    printf("8- Imprimir o nível de um nó x \n");
    printf("9- Sair \n");
    printf("---------------------------------------------------------------------------------\n\n");
    
    scanf("%d",&op);
    
        switch (op){
            case 1:
                FILE *arq=fopen("ArquivoArvore.txt","rt");
                a=LerArqArvore(arq);
                fclose(arq);
                printf("A arvore do arquivo 'ArquivoArvore.txt' foi lida\n");
                break;
            case 2:
                printf("1-pré-ordem\n2-em-ordem \n3-pós-ordem \n4-em largura\n");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        PreOrdem(a);
                        break;
                    case 2:
                        EmOrdem(a);
                        break;
                    case 3:
                        PosOrdem(a);
                        break;
                    case 4:
                        //Largura(a,Altura(a));
                        ImprimirLargura(a);
                        break;
                }
                break;
            case 3:
                printf("Digite o numero a ser procurado: ");
                scanf("%d",&num);
                if ((Existe(a,num))>0){
                    printf("O elemento existe na árvore");
                }else{
                    printf("O elemento não existe na árvore");
                }
                break;
            case 4:
                printf("Digite o numero a ser procurado: ");
                scanf("%d",&num);
                    printf("O número foi encontrado %d vez/vezes",ContExiste(a,num));
                break;
            case 5:
                NosFolhas(a);
                break;
            case 6:
                if (Balanceada(a)==1){
                    printf("A árvore é balanceada");
                }else{
                    printf("A árvore não é balanceada");
                }
                break;
            case 7:
                int aux=pow(2,(Altura(a)-1))+1;//+1 por conta da raiz, a função cheia
                if(Cheia(a)==aux){
                    printf("A árvore é cheia");
                }else{
                    printf("A árvore não é cheia");
                }
                break;
            case 8:
            int contador=0;
            printf("Digite o valor: ");
            scanf("%d",&num);
            Nivel(a,num,contador);
                break;
        }
}while(op!=9);
}


