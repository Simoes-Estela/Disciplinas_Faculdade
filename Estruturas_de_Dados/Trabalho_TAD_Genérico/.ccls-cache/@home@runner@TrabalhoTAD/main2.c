/*#include "Heashing.h"
#include <stdio.h>
#include <string.h>

struct Alunos{
    int id;
    char nome[50];
    char curso[30];   
};  

int main() {
  struct Alunos a;
  strcpy(a.nome,"Ana Julia");
  strcpy(a.curso, "Ciências da Computação");
  a.id=1;

  struct Alunos obj;

  char nomeArq[] = "Registro.bin";
  int chave = a.id;
  inicializar(nomeArq);
    inserir(nomeArq, a.id, &a, sizeof(obj));  
  imprimir(nomeArq);
  buscar(nomeArq, &chave, &obj, sizeof(obj));
  printf("Chave: %d Nome:%s Curso: %s Matricula: %d\n",chave, obj.nome, obj.curso, obj.id);
  
  //Função 'remove' da biblioteca stdio.h que apaga o arquivo
    int f = remove("Registro.bin");
    if (f == 0) {
      printf("Arquivo removido");
    }
}*/