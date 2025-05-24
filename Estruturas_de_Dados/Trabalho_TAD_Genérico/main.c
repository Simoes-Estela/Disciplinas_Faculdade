#include "Heashing.h"
#include <stdio.h>
#include <string.h>

typedef struct alunos{
    int id;
    char nome[50];
    char curso[30];   
}Alunos; 

typedef struct carro{
    char id[50];
    char modelo[50];
    char marca[50];   
    int ano;
}Carro; 

int main() {
  int op = 0;
  int op2 = 0;
  char nomeArq[] = "Registro.bin";
  inicializar(nomeArq);

  while(op!=4){
    printf("MENU\n");
    printf("1 - Inserir elemento\n");
    printf("2 - Buscar elemento\n");
    printf("3 - Imprimir elementos\n");
    printf("4 - Sair\n");
    scanf("%d",&op);
    switch(op){
      case 1:
        printf("Inserir elemento\n");
        printf("1-Inserir Aluno\n");
        printf("2-inserir Carro\n");
        printf("3-Inserir Inteiro\n");
        scanf("%d", &op2);
        switch(op2){
          case 1:{
            Alunos obj;
            printf("Insira o nome do aluno: ");
            scanf("%s",obj.nome);
            printf("Insira o curso do aluno: ");
            scanf("%s",obj.curso);
            printf("Insira a matricula do aluno: ");
            scanf("%d",&obj.id);
            inserir(nomeArq,obj.id, &obj, sizeof(obj));
            printf("Elemento inserido\n");
            break;
            }
          case 2:{
            Carro c;
            printf("Insira a placa do carro:");
            scanf("%s", c.id);
            printf("Insira o nome do carro: ");
            scanf("%s", c.modelo);
            printf("Insira a marca do carro: ");
            scanf("%s", c.marca);
            printf("Insira o ano do carro: ");
            scanf("%d", &c.ano);
            inserir(nomeArq, c.ano, &c, sizeof(c));
            printf("Elemento inserido\n");
            break;
            }
          case 3:{
            int inteiro;
            printf("Insira o inteiro: ");
            scanf("%d", &inteiro);
            inserir(nomeArq, inteiro, &inteiro, sizeof(int));
            break;
          }
          default:
            printf("Opção inexistente,tente novamente\n");
        }
        break;
      case 2:{
        
        printf("Buscar elemento\n");
        printf("1-Buscar Aluno\n");
        printf("2-Buscar Carro\n");
        printf("3-Buscar Inteiro\n");
        scanf("%d", &op2);
        switch(op2){
          case 1:
            printf("Digite a matricula do aluno: \n");
            int id;
            scanf("%d", &id);
            Alunos obj;
            buscar(nomeArq, &id, &obj, sizeof(obj));
            printf("Matrícula: %d Nome: %s Curso: %s\n",obj.id,obj.nome, obj.curso);
            break;
          case 2:{
            printf("Digite o ano do carro: \n");
            int ano;
            scanf("%d", &ano);
            Carro obj;
            buscar(nomeArq, &ano, &obj, sizeof(obj));
            printf("Placa: %s Modelo: %s Marca: %s Ano: %d\n",obj.id, obj.modelo, obj.marca, obj.ano);
            break;
          }
          case 3:
            printf("Digite o inteiro: \n");
            int inteiro;
            scanf("%d", &inteiro);
            buscar(nomeArq, &inteiro, &inteiro, sizeof(int));
            printf("Inteiro: %d\n", inteiro);
            break;
        }
        break;
        }
      case 3:
        printf("Imprimir elementos\n");
        imprimir(nomeArq);
        break;
      case 4:
        Destruir(nomeArq);
        break;
      default:
        printf("Opção inválida, tente novamente\n");
        break;
    }
  }
  return 0;
}
