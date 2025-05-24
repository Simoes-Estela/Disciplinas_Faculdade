#include "Heashing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100


struct registro {
    int disponibilidade;// 0-Disponível , 1-Indisponível
    int chave; // serve também para a inserção/busca na hash table
    void *obj; 
};

int hash(int key) {
    return key % N;
}

int AcharPosicao(char *nomeArq, int x) {
    int pos = hash(x);
    
    Registro a = malloc(sizeof(struct registro));
    //alocando memoria para o registro
    
    FILE *arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return 0;
    }
    //procura uma posição livre no arquivo partindo do inicio
    fseek(arq, pos * sizeof(struct registro), SEEK_SET);
    fread(a, sizeof(struct registro), 1, arq);
    while (a->disponibilidade == 0) {
        pos = (pos + 1) % N;
        fseek(arq, pos * sizeof(struct registro), SEEK_SET);
        fread(a, sizeof(struct registro), 1, arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *nomeArq, int chave, void * dados, int tamanhoDados) {
    int pos = AcharPosicao(nomeArq, chave); // Acha a posição onde o registro deve ser inserido
    
    FILE *arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
    }
    
    Registro a = malloc(sizeof(struct registro)); 
    a->disponibilidade = 0;
    a->chave = chave;
    a->obj = (void*) malloc(tamanhoDados);
    memcpy(a->obj, dados, tamanhoDados);
    fseek(arq, pos * sizeof(struct registro), SEEK_SET);
    fwrite(a, sizeof(struct registro), 1, arq);
    fclose(arq);
    free(a);
}


int buscar(char *nomeArq, int *chave,void * dados,int tamanhoDados) {
    int pos = hash(*chave);
    
    Registro a = (Registro) malloc(sizeof(struct registro));
    //aloca memorio para o registro
    
    FILE *arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    //procura a posição da chave no arquivo partindo do inicio
    fseek(arq, pos * sizeof(struct registro), SEEK_SET);
    fread(a, sizeof(struct registro), 1, arq);
    while (a->disponibilidade == 0 && a->chave != *chave) {
        pos = (pos + 1) % N;
        fseek(arq, pos * sizeof(struct registro), SEEK_SET);
        fread(a, sizeof(struct registro), 1, arq);
    }if(a->chave == *chave){
        printf("Chave encontrada.\n");
        memcpy(dados, a->obj, tamanhoDados);
        //copia o objeto encontrado para a variavel dados
        fclose(arq);
        free(a);
        return 1;
    }else{
        printf("Chave não existe");
        fclose(arq);
        free(a);
        return 0;    
    }
    fclose(arq);
    return 1;
}

void imprimir(char *nomeArq) {
    Registro a = malloc(sizeof(struct registro));
    
    FILE *arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
      printf("Erro ao abrir o arquivo.\n");
        free(a);
    }

    printf("Tabela:\n");
    printf("Posicao\tChave\tDisponibilidade\n");
    for (int i = 0; i < N; i++) {
        fseek(arq, i * sizeof(struct registro), SEEK_SET);
        fread(a, sizeof(struct registro), 1, arq);
        printf("%-10d\t%-10d\t%-10d\n", i, a->chave, a->disponibilidade);
    }
    fclose(arq);
    free(a);
}

void inicializar(char *nomeArq){
    FILE *arq = fopen(nomeArq, "wb");
    if (arq == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
  }
    Registro a = (Registro) malloc(sizeof(struct registro));
    a->disponibilidade = 1;
    a->obj = NULL;
    a->chave = -1;
    
    for (int i = 0; i < N; i++){
        fwrite(a, sizeof(struct registro), 1, arq);
    }
    fclose(arq);
    free(a);
}

void Destruir(char *nomeArq){ //Função 'remove' da biblioteca stdio.h que apaga o arqui
    int f = remove("Registro.bin");
    if (f == 0) {
        printf("Arquivo removido");
    }
}
