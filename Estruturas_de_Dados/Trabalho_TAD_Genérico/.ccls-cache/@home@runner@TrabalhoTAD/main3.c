/*#include "Heashing.h"
#include <stdio.h>
#include <string.h>

int main() {
  
  struct Carro{
      char id[50];
      char modelo[50];
      char marca[50];   
      int ano;
  }; 

  struct Carro obj;

  struct Carro c;
  strcpy(c.modelo,"Fusca");
  strcpy(c.marca, "Volkswagen");
  strcpy(c.id, "MMQ0822");
  c.ano=1959;
  
  char nomeArq[] = "Registro.bin";
  int chave = c.ano;
  inicializar(nomeArq);
  inserir(nomeArq, c.ano, &c, sizeof(obj));
  imprimir(nomeArq);
  buscar(nomeArq, &chave, &obj, sizeof(obj));
  printf("Chave: %d ID:%s Marca: %s Modelo:%s\n",chave, obj.id, obj.marca, obj.modelo);
  //Função 'remove' da biblioteca stdio.h que apaga o arquivo
    int f = remove("Registro.bin");
    if (f == 0) {
      printf("Arquivo removido");
    }
}*/
