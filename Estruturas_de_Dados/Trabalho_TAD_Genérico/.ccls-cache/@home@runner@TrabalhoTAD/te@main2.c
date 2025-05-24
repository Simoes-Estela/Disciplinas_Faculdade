#include "Heashing.h"
#include <stdio.h>
#include <string.h>

struct Alunos{
    int matricula;
    char nome[50];
    char curso[30];   
};  

int main() {
  struct Alunos a;
  strcpy(a.nome,"Ana Julia");
  strcpy(a.curso, "Ciências da Computação");
  a.matricula=1;

  struct Alunos obj;

  char nomeArq[] = "alunos.bin";
  int chave = a.matricula;
  inicializar(nomeArq);
  inserir(nomeArq, a.matricula, &a, sizeof(obj));
  imprimir(nomeArq);
  buscar(nomeArq, &chave, &obj, sizeof(obj));
  printf("Chave: %d Nome:%s Curso: %s Matricula: %d\n",chave, obj.nome, obj.curso, obj.matricula);

}