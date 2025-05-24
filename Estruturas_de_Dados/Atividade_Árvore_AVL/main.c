
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
//Struct da Árvore AVL

typedef struct avl{
   int info;
   int FB;
   struct avl *esq;
   struct avl *dir;
}AVL;

void AjustarFB(AVL *a){
   if(a!=NULL){
      int he=Altura(a->esq);
      int hd=Altura(a->dir);
      a->FB=hd-he;
      
      AjustarFB(a->esq);
      AjustarFB(a->dir);
   }
}

int Altura(AVL* a){
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

void PreOrdem(AVL *a){
    //não tem como tirar proveito da ordenação
    if(a!=NULL){
        printf("%d ",a->info);
        PreOrdem(a->esq);
        PreOrdem(a->dir);
    }
}

void EmOrdem(AVL *a){
    //não tem como tirar proveito da ordenação
    if (a!=NULL){
        EmOrdem(a->esq);
        printf("%d ",a->info);
        EmOrdem(a->dir);
    }
}

void PosOrdem(AVL *a){
    //não tem como tirar proveito da ordenação
    if(a!=NULL){
        PosOrdem(a->esq);
        PosOrdem(a->dir);
        printf("%d ",a->info);
    }
}

void ImprimirNivel (AVL *a, int cont, int nivel) {
    //não tem como tirar proveito da ordenação
    if (a != NULL) {
        if (cont == nivel){
           printf ("%d (%d)", a->info,a->FB);
        }else{
            ImprimirNivel(a->esq, cont+1, nivel); //Subesq
            ImprimirNivel(a->dir, cont+1, nivel); //Subdir
        }
    }
}

void ImprimirLargura (AVL *a) {
    if (a!=NULL) {//não tem como tirar proveito da ordenação
        int i;
        int h = Altura(a);
        for (i=0; i<h; i++) {
            ImprimirNivel(a, 0, i);
            printf("\n");
        }
    }
}

AVL *LerArqArvore(FILE *arq){
    char c; //tipo char para ler os '()'
    int num;

    fscanf(arq,"%c",&c); //lê '('
    fscanf(arq,"%d",&num); //ler os nós ou raizes


    if(num==-1){
        fscanf(arq,"%c",&c);
        return NULL;
    }else{
        AVL *a=(AVL*)malloc(sizeof(AVL));
        a->info=num;
        a->esq=LerArqArvore(arq); //Sub Esquerda
        a->dir=LerArqArvore(arq);//Sub Direita
        fscanf(arq,"%c",&c); //Lê ')'
        return a;
        
    }

}

AVL* Destruir(AVL* a){
	if(a!=NULL){
		a->esq = Destruir(a->esq);
		a->dir = Destruir(a->dir);
		free(a);
	}
	return NULL;
}

int Existe(AVL *a, int x){
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

int NivelNo(AVL *a,int x,int count){
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

void ImprimirFolhasMenores(AVL *a, int x){
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

//Rotação a esquerda simples
AVL *RotacaoEsqSimples (AVL *r)
{
	//Os nós a e b serão aqueles com FB modificados.
	AVL *a = r;
	AVL *b=a->dir;
	a->dir = b->esq;
	b->esq = a;
	if (b->FB == 1)
	{
		a->FB = 0;
		b->FB = 0;
	}
	else
	{
		a->FB = 1;
		b->FB = -1;
	}
	r=b;
	return r;
}

AVL *RotacaoEsqDupla(AVL *r)
{
	//Os nós a, b, c serão aqueles com FBs modificados
	AVL *a = r;
	AVL *c = a->dir;
	AVL *b = c->esq; //O nó b será a nova raiz
	c->esq = b->dir;
	a->dir = b->esq;
	b->esq = a;
	b->dir = c;
	//Setando os valores dos FBs de acordo
	//com FB da nova raiz.
	switch(b->FB)
	{
		case -1:
			a->FB = 0;
			c->FB = 1;
		break;
		case 0:
			a->FB = 0;
			c->FB = 0;
		break;
		case 1:
			a->FB = -1;
			c->FB = 0;
		break;
	}
	b->FB = 0;
	r = b;
	return r;
}

AVL *RotacaoEsq (AVL *r)
{
	if (r->dir->FB == -1)
		r = RotacaoEsqDupla(r);
	else
		r = RotacaoEsqSimples(r);
	return r;
}

//Rotação a direita simples
AVL *RotacaoDirSimples (AVL *r)
{
	//Os nós a e b serão aqueles com FB modificados.
	AVL *a = r->esq;
	AVL *b = r;
	b->esq = a->dir;
	a->dir = b;
	if (a->FB == -1)
	{
		a->FB = 0;
		b->FB = 0;
	}
	else
	{
		a->FB = 1;
		b->FB = -1;
	}
	r = a;
	return r;
}

AVL *RotacaoDirDupla(AVL *r)
{
	//Os nós a, b, c serão aqueles com FBs modificados
	AVL *c = r;
	AVL *a = c->esq;
	AVL *b = a->dir;
	c->esq = b->dir;
	a->dir = b->esq;
	b->esq = a;
	b->dir = c;
	//Setando os valores dos FBs de acordo
	//com FB da nova raiz.
	switch(b->FB)
	{
		case -1:
			a->FB = 0;
			c->FB = 1;
		break;
		case 0:
			a->FB = 0;
			c->FB = 0;
		break;
		case +1:
			a->FB = -1;
			c->FB = 0;
		break;
	}
	b->FB = 0;
	r = b;
	return r;
}

//Rotação a direita geral
AVL *RotacaoDir (AVL *r)
{
	if (r->esq->FB == 1){
		r = RotacaoDirDupla(r);
	}
	else{
		r = RotacaoDirSimples(r);
	}
	return r;
}

AVL *LerAVL(FILE *arq){
	AVL *a = LerArqArvore(arq);
	AjustarFB(a);
	return a;
}

AVL *Inserir(AVL *r, int x, int *hMudou)
{
	if (r == NULL) //Momento de inserir
	{
		r = (AVL*) malloc (sizeof(AVL));
		r->info = x;
		r->esq = NULL;
		r->dir = NULL;
		r->FB = 0;
		*hMudou = 1;
	}
	else
	{
		if (x <= r->info)
		{
			r->esq = Inserir (r->esq,x,hMudou);
			if (*hMudou == 1)
			{
				switch (r->FB)
				{
					case -1:
						r = RotacaoDir(r);
						*hMudou = 0;
					break;
					case 0:
						r->FB = -1;
						*hMudou = 1;
					break;
					case +1:
						r->FB = 0;
						*hMudou = 0;
					break;
				}
			}
		}
		else
		{
			r->dir = Inserir (r->dir,x,hMudou);
			if (*hMudou == 1)
			{
				switch (r->FB)
				{
					case -1:
						r->FB = 0;
						*hMudou = 0;
					break;
					case 0:
						r->FB = +1;
						*hMudou = 1;
					break;
					case +1:
						r = RotacaoEsq (r);
						*hMudou = 0;
					break;
				}
			}
		}
	}
	return r;
}

AVL *Remover (AVL *r, int x, int *hMudou)
{
	if (r != NULL)
	{
	if (r->info == x)
		{
			//Verificar se é folha
			if (r->esq == NULL && r->dir == NULL)
			{
				free (r);
				*hMudou = 1;
				return NULL;
			}
			//Verificar se um dos filhos é nulo
			else if (r->esq == NULL || r->dir == NULL)
			{
				AVL *aux;
				if (r->esq == NULL)
				aux = r->dir;
				else
				aux = r->esq;
				free(r);
				*hMudou = 1;
				return aux;
			}
			//Nenhum filho nulo
			else
			{
				AVL *maiorEsq = r->esq;
				while (maiorEsq->dir != NULL){
					maiorEsq = maiorEsq->dir;
				}
				
				r->info = maiorEsq->info;
				r->esq = Remover(r->esq,r->info,hMudou);
				
				if (*hMudou == 1)
				{
					switch(r->FB)
					{
						case -1:
							r->FB = 0;
							*hMudou = 1;
						break;
						case 0:
							r->FB = 1;
							*hMudou = 0;
						break;
						case +1:
							
							int aux = r->dir->FB;
							r = RotacaoEsq(r);
							if (aux == 0)
							*hMudou = 0;
							else
							*hMudou = 1;
						break;
					}
				}
			}
		}
		else if (x < r->info)
		{	
			r->esq = Remover(r->esq, x, hMudou);
			if (*hMudou == 1)
			{
				switch(r->FB)
				{
					case -1:
						r->FB = 0;
						*hMudou = 1;
					break;
					case 0:
						r->FB = 1;
						*hMudou = 0;
					break;
					case +1:
						int aux = r->dir->FB;
						r = RotacaoEsq(r);
						if (aux == 0){
							*hMudou = 0;
						}
						else{
							*hMudou = 1;
						}
					break;
				}
			}
	
		}
		else
		{
			r->dir = Remover(r->dir, x, hMudou);
			if (*hMudou == 1)
			{
				switch(r->FB)
				{
					case +1:
						r->FB = 0;
						*hMudou = 1;
					break;
					case 0:
						r->FB = -1;
						*hMudou = 0;
					break;
					case -1:
						int aux = r->esq->FB;
						r = RotacaoDir(r);
						if (aux == 0){
							*hMudou = 0;
						}
						else{
							*hMudou = 1;
						}
					break;
				}
			}
		}
	}
	return r;
}



int main(){
setlocale(LC_ALL, "Portuguese");
AVL *a;
int op=0,num=0,hMudou=0;//Opção do menu escolhida pelo usuario
    
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
                FILE *arq=fopen("AVL.txt","rt");
                a=LerArqArvore(arq);
                fclose(arq);
                printf("A arvore do arquivo foi lida\n");
                AjustarFB(a);
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
                Inserir(a,num,&hMudou);
                printf("\n O valor foi inserido na Árvore \n");
                break;
            case 7:
                printf("Digite o numero a ser removido: ");
                scanf("%d",&num);
                Remover(a,num,&hMudou);
                printf("\n O valor foi removido da Árvore \n");
                 break;
            case 8:
            //sair e destruir árvore
                Destruir(a);
                break;
        }
}while(op!=8);
}


