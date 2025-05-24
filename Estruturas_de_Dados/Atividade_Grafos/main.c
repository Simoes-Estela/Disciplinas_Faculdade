#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int destino;
    int custo;
    struct lista *prox;
}lista;

void inicializar(lista **g,int n){
    int i;
    for ( i = 0; i<=n ; i++)
    {
        g[i]=NULL;
    }
    
} 

lista *InserirLista(lista *l,int d,int c){
    lista *no=(lista*)malloc(sizeof(lista));
    no->destino=d;
    no->custo=c;
    no->prox=l;
    return no;
}

void InserirAresta(lista **g,int origem,int destino,int custo){
    g[origem]=InserirLista(g[origem],destino,custo);
    printf("\nA aresta foi inserida no grafo");
}

void imprimirGrafo(lista **g,int n){
    int i;
    printf("Grafo: ");
    for(i=1;i<=n;i++){
        printf("\n \t%d",i);
        imprimirLista(g[i]);
    }
}

void imprimirLista(lista *l){
    if(l !=NULL){
        printf("-(%d %d)",l->destino,l->custo);
        imprimirLista(l->prox);
    }
}

lista *RemoverLista(lista *l,int d,int c,int o){
    if(l==NULL){
        printf("A aresta não foi encontrada");
        return NULL;
    }else if (l->destino==d && l->custo==c){
        lista *aux;
        aux=l->prox;
        l->destino=NULL;
        l->custo=NULL;
        l->prox=NULL;
        free(l);
        printf("A aresta %d->(%d|%d) foi REMOVIDA",o,d,c);
        return aux;
    }else{
        l->prox=RemoverLista(l->prox,d,c,o); 
        return l;
    }
    
}

int RemoverAresta(lista **g,int destino,int custo, int origem){
    g[origem]=RemoverLista(g[origem],destino,custo,origem);
}

int Entrada(lista *l,int v){
    if(l==NULL){
        return 0;
    }else if(l->destino==v){
        return 1+Entrada(l->prox,v);
    }else{
        return Entrada(l->prox,v);
    }
}

void auxEntrada(lista **g,int vertice,int n){
int i=0,aux=0;
    for(i=1;i<=n;i++){
       aux+=Entrada(g[i],vertice); 
    }
    printf("\nGrau de Entrada: %d ",aux);
}

int Saida(lista *l){
    if(l==NULL){
        return 0;
    }else{
        return 1+Saida(l->prox);
    }
}

int GrauMaximo(lista **g,int n){
    int i,a;
    for(i=1;i<=n;i++){
        for(a=1;a<=n;a++){
            if(i!=a){
                
                if(Completo(g[i],a)==0){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int Completo(lista *l,int aresta){
    if(l==NULL){
        return 0;
    }else if (l->destino==aresta){
        return 1;
    }else {
        Completo(l->prox,aresta);
    }
}

lista *DestruirLista(lista *l){
    free(l);
    return l;
}

int DestruirGrafo(lista **g,int n){
    printf("\nDestruindo grafo");
    int i=0;
    for(i=0;i<=n;i++){
      g[i]=DestruirLista(g[i]);
    }
    printf("\nO grafo foi destruido");
}

int Existe(int *vet,int valor,int n){//Função que retorna 1 caso o vetor tenha chegado no destino, ou caso o contrário 0;
    for(int i=0;i<n;i++){
        if(vet[i]==valor){
            return 1;
        }
    }
    return 0;
}

void Caminhos(lista **g,int d,int *vet,int pos){
    if(vet[pos-1]==d){ //Se o vetor chegou no destino o vetor é impresso
        for(int i=0;i<pos;i++){
            printf("%d ",vet[i]);
        }
        printf("\n");

    }else{
        lista *p=g[vet[pos-1]];//cria-se uma lista p que recebe o grafo(o grafo recebe o indice de vetor indice pos-1);
        while (p!=NULL){ //enquanto o valor não for NULL
            if(!Existe(vet,p->destino,pos)){//Se o vetor for diferente do destino, ainda tem chamada recursiva
                vet[pos]=p->destino;
                Caminhos(g,d,vet,pos+1);
            }
            p=p->prox;
        }
        
    }
}

int CaminhoMenor(lista **g,int d,int *vet,int pos,int *tam,int *menor){
    if(vet[pos-1]==d){ //Se o vetor chegou no destino o vetor é impresso
        if(pos<*tam){
            for(int i=0;i<pos;i++){
                 menor[i]=vet[i];
            }
            *tam=pos;
        }
        
        
    }else{
        lista *p=g[vet[pos-1]];//cria-se uma lista p que recebe o grafo(o grafo recebe o indice de vetor indice pos-1);
        while (p!=NULL){ //enquanto o valor não for NULL
            if(!Existe(vet,p->destino,pos)){//Se o vetor for diferente do destino, ainda tem chamada recursiva
                vet[pos]=p->destino;
                 CaminhoMenor(g,d,vet,pos+1,tam,menor);
            }
            p=p->prox;
        }
        
    }
}

void MenorCustoCaminho(lista **g, int d, int *vet, int pos, int *menorCaminho, int *CustoMenor, int AtualCusto) {
    if (vet[pos-1] == d) {
        if (AtualCusto < *CustoMenor) {
            *CustoMenor = AtualCusto;
            for (int i=0; i<pos;i++) {
                menorCaminho[i]=vet[i];
            }
        }
    } else {
        lista *p = g[vet[pos-1]];
        while (p!=NULL) {
            if (!Existe(vet, p->destino, pos)) {
                vet[pos] = p->destino;
                int novoCusto = AtualCusto + p->custo;
                MenorCustoCaminho(g, d, vet, pos + 1, menorCaminho, CustoMenor, novoCusto);
            }
            p = p->prox;
        }
    }
}

int main(){
    int op=0,n=0;
    printf("Digite a quantidade de posições do grafo:");
    scanf("%d",&n);
    lista**g;
    g=(lista**)malloc((n+1)*sizeof(lista*));

    while (op!=9){
        printf("\nMenu de opções \n");
        printf("1. Inserir uma aresta no grafo\n");
        printf("2. Remover uma aresta do grafo\n");
        printf("3. Imprimir grafo\n");
        printf("4. Imprimir os graus de entrada e saída de um vértice\n");
        printf("5. Verificar se um grafo é completo\n");
        printf("6. Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7. Imprimir o caminho mais curto (com menor número de arestas)\n");
        printf("8. Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n");
        printf("9. Sair\n");

        scanf("%d",&op);
        switch (op){
            int des=0,cus=0,ori=0,*vet;
            
            case 1:
                printf("Digite a origem do grafo, o destino e o custo: ");
                scanf("%d %d %d",&ori,&des,&cus);
                InserirAresta(g,ori,des,cus);
                break; 
            case 2 :
                printf("Digite a origem do grafo, o destino e o custo: ");
                scanf("%d %d %d",&ori,&des,&cus);
                RemoverAresta(g,des,cus,ori);
                break;
            case 3:
                imprimirGrafo(g,n);
                break;
            case 4:
                int v;
                printf("Digite o vértice: ");
                scanf("%d",&v);
                printf("\nGrau de Saida: %d ",Saida(g[v]));
                auxEntrada(g,v,n);
                break;
            case 5:
                if(GrauMaximo(g,n)==1){
                    printf("\nO grafo É completo");
                }else{
                    printf("\nO grafo NÃO É completo");
                }
                break;
            case 6:
                vet=(int *)malloc(n+1*sizeof(int));
                printf("--TODOS OS CAMINHOS ENTRE UMA ORIGEM E UM DESTINO--\n");
                printf("Digite a origem e o destino: ");
                scanf("%d %d",&ori,&des);
                vet[0]=ori;
                Caminhos(g,des,vet,1);
                free(vet);
                break;
            case 7:
                
                int Menortam=n,*MaisCurto;
                MaisCurto=(int *)malloc(n+1*sizeof(int));
                vet=(int *)malloc(n+1*sizeof(int));
                printf("\n--MENOR CAMINHOS ENTRE UMA ORIGEM E UM DESTINO--\n");
                printf("Digite a origem e o destino: ");
                scanf("%d %d",&ori,&des);
                vet[0]=ori;
                CaminhoMenor(g,des,vet,1,&Menortam,MaisCurto);
                printf("\nO menor caminho é: ");
                for(int i=0;i<Menortam;i++){
                    printf("%d ",MaisCurto[i]);
                }
                printf("\n");
                break;
            case 8:
                int MenorCusto,*CaminhoCustoMenor;
                CaminhoCustoMenor=(int *)malloc(n+1*sizeof(int));
                vet=(int *)malloc(n+1*sizeof(int));
                printf("--CAMINHO DE MENOR CUSTO--\n");
                printf("Digite a origem e o destino: ");
                scanf("%d %d",&ori,&des);
                vet[0]=ori;
                MenorCustoCaminho(g,des,vet,1,CaminhoCustoMenor,&MenorCusto,0);
                printf("Caminho de menor custo: ");
                for(int i=0;CaminhoCustoMenor[i]!=0 && i<n;i++){
                    printf("%d ",CaminhoCustoMenor[i]);
                }
                printf("\nCusto: %d\n",MenorCusto);
                free(vet);
                free(CaminhoCustoMenor);
                break;
            case 9:
                break;
            default:
                printf("\nOpção inválida\n");
        }
        

    }
    
    DestruirGrafo(g,n);
    printf("\nFechando programa");

   
}