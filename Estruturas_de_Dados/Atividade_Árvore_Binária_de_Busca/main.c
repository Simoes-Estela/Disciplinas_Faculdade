 /******************************************************************************
Implemente um programa que apresente na tela o seguinte menu de opções:
1- Ler uma árvore de um arquivo fornecido pelo usuário
2- Imprimir a árvore (opções: pré-ordem; em-ordem; pós-ordem; e em largura)
3- Verificar se um elemento x existe na árvore
4- Imprimir o nível de um nó x
5- Imprimir as folhas menores que um valor x
6- Inserir um nó x na árvore
7- Remover um nó x da árvore
8- Sair
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
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
    //não tem como tirar proveito da ordenação
    if(a!=NULL){
        printf("%d ",a->info);
        PreOrdem(a->esq);
        PreOrdem(a->dir);
    }
}

void EmOrdem(arvore *a){
    //não tem como tirar proveito da ordenação
    if (a!=NULL){
        EmOrdem(a->esq);
        printf("%d ",a->info);
        EmOrdem(a->dir);
    }
}

void PosOrdem(arvore *a){
    //não tem como tirar proveito da ordenação
    if(a!=NULL){
        PosOrdem(a->esq);
        PosOrdem(a->dir);
        printf("%d ",a->info);
    }
}

void ImprimirNivel (arvore *a, int cont, int nivel) {
    //não tem como tirar proveito da ordenação
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
    if (a!=NULL) {//não tem como tirar proveito da ordenação
        int i;
        int h = Altura(a);
        for (i=0; i<h; i++) {
            ImprimirNivel(a, 0, i);
            printf("\n");
        }
    }
}

int Altura(arvore *a){
if(a==NULL){ //não tem como tirar proveito da ordenação
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

int Existe(arvore *a, int x){
//tem como tirar proveito da ordenação
    if(a!=NULL){
        if(a->info == x){
            return 1;
        }else if(a->info <= x){
            return Existe(a->dir,x);
        }else{
            return Existe(a->esq,x);
        }
    }
}

int NivelNo(arvore *a,int x,int count){
    //não tem como tirar proveito da ordenação
    if(a != NULL){
        if(a->info == x){
            return count;
        }else if(x > a->info){
            return NivelNo(a->dir,x,count+1);
        }else{
            return NivelNo(a->esq,x,count+1);
        }
    }else{
        return -1;
    }
}

arvore *Inserir(arvore*a,int x){
    if(a==NULL){
        a=(arvore*)malloc(sizeof(arvore));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
    }else if(x<=a->info){
        a->esq=Inserir(a->esq,x);
    }else{
        a->dir=Inserir(a->dir,x);
    }
return a;

}

arvore *Remover(arvore* a, int x){
	if(a!=NULL){
		if(a->info==x){
			if(a->esq==NULL&&a->dir==NULL){
				free(a);
				return NULL;
			}else if(a->esq==NULL){
				arvore *aux=a->dir;
				free(a);
				return aux;
			}else if(a->dir==NULL){
				arvore *aux=a->esq;
				free(a);
				return aux;
			}else{
				arvore *aux=a->esq;
				while (aux->dir!=NULL){
					aux=aux->dir;
				}
				a->info=aux->info;
				a->esq=Remover(a->esq, aux->info);
			}
		}else if(a->info>x){
			a->esq=Remover(a->esq, x);
		}else{
			a->dir=Remover(a->dir,x);
		}
	}
	return a;
	
}

void ImprimirFolhasMenores(arvore *a, int x){
	if(a!=NULL){
		if(a->info>=x){
			ImprimirFolhasMenores(a->esq, x);
		}else if(a->esq==NULL && a->dir==NULL){
			printf("%d ", a->info);
		}else{
			ImprimirFolhasMenores(a->esq, x);
			ImprimirFolhasMenores(a->dir, x);
		}
	}
}

arvore* Destruir(arvore* a){
	if(a!=NULL){
		a->esq = Destruir(a->esq);
		a->dir = Destruir(a->dir);
		free(a);
	}
	return NULL;
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
    printf("4- Imprimir o nível de um nó x \n");
    printf("5- Imprimir as folhas menores que um valor x \n");
    printf("6- Inserir um nó x na árvore \n");
    printf("7- Remover um nó x da árvore \n");
    printf("8- Sair \n");
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
                        ImprimirLargura(a);
                        break;
                }
                break;
            case 3:
                printf("Digite o numero para saber se o mesmo existe na árvore: ");
                scanf("%d",&num);
                if ((Existe(a,num))==1){
                    printf("O elemento existe na árvore");
                }else{
                    printf("O elemento não existe na árvore");
                }
                break;
            case 4:
                printf("Digite o numero para saber o nível: ");
                scanf("%d",&num);
                if(NivelNo(a,num,0) > -1){
                    printf("O elemento esta no nivel %d ",NivelNo(a,num,0));
                } else{
                    printf("O valor não existe na árvore");
                }
                break;
            case 5:
                printf("Deseja imprimir Folhas menores que : ");
                scanf("%d",&num);
                ImprimirFolhasMenores(a,num);
                break;
            case 6:
                printf("Digite o numero a ser inserido: ");
                scanf("%d",&num);
                Inserir(a,num);
                printf("\n O valor foi inserido na Árvore \n");
                break;
            case 7:
                printf("Digite o numero a ser removido: ");
                scanf("%d",&num);
                Remover(a,num);
                printf("\n O valor foi removido da Árvore \n");
                 break;
            case 8:
            //sair e destruir árvore
                Destruir(a);
                break;
        }
}while(op!=8);
}



