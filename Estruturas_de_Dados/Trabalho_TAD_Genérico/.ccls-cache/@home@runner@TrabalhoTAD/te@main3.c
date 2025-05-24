#include "Heashing.h"
#include <stdio.h>
#include <string.h>

int main() {
  
  struct Professor{
      int matricula;
      char nome[50];
      float salario;   
      char curso[30];
  }; 

  struct Professor obj;

  struct Professor p;
  strcpy(p.nome,"Fabio");
  strcpy(p.curso, "Calculo");
  p.salario=10000.00;
  p.matricula=102528965;
  
  char nomeArq[] = "alunos.bin";
  int chave = p.matricula;
  inicializar(nomeArq);
  inserir(nomeArq, p.matricula, &p, sizeof(obj));
  imprimir(nomeArq);
  buscar(nomeArq, &chave, &obj, sizeof(obj));
  printf("Chave: %d Nome:%s Curso: %s Salario:%f Matricula: %d\n",chave, obj.nome, obj.curso, obj.salario, obj.matricula);

}