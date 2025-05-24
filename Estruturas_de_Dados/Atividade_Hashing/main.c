/******************************************************************************

Exercício Classroom-Implemente um programa para "Hashingem Arquivo" - tratamento 
de colisão: próxima posição livre - que apresenta na tela o seguinte menu de opções:
1. Inserir um novo aluno (matrícula, nome, curso)
2. Imprimir as informações de um determinado aluno (busca pela matricula)
3. Imprimir a tabela de dispersão (tabela hash)
4. Sair
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int N;

typedef struct aluno{
    char nome[50];
    int matricula;
    char curso[30];
    int disponibilidade;
}Aluno;

void inicializar(char *nomeArq){
    FILE *arq=fopen(nomeArq,"wb"); //binário
    Aluno a;
    int i;
    a.disponibilidade=1; //disponibilidade de cada posição
    for (i=0;i<N;i++){
        fwrite(&a,sizeof(Aluno),1,arq); //em cada posição de 'a', alocamos o valor da struct 'Aluno' é e inserido o valor 1
    } //cria as N posições 
fclose(arq);
printf("\n------------------------------------------------------------------------\n");
printf("A tabela Hashing foi criada com %d posições/posição",N);
printf("\n------------------------------------------------------------------------\n");
}

void Inserir(char *NomeArq,char *NomeAluno,int Matricula, char *Curso){
    int pos=AcharPosicao(NomeArq,Matricula);
    FILE *arq = fopen(NomeArq, "r+b");
    Aluno a;
    strcpy(a.curso,Curso);
    strcpy(a.nome,NomeAluno);
    a.disponibilidade = 0;
    a.matricula= Matricula;
    fseek (arq, pos*sizeof(Aluno), SEEK_SET);
    fwrite (&a, sizeof(Aluno), 1, arq);
    fclose(arq);
    printf("O aluno %s foi inserido",NomeAluno);
}

int hash(int key,int size){
    key=key%size;
    return key;
}

int AcharPosicao (char *nomeArq, int matricula) {
    int pos = hash(matricula,N);
    Aluno a;
    FILE *arq = fopen(nomeArq, "rb");
    fseek (arq, pos*sizeof(Aluno), SEEK_SET);
    fread (&a, sizeof(Aluno), 1, arq);
    while (a.disponibilidade == 0) {
        pos = (pos+1)%N;
        fseek (arq, pos*sizeof(Aluno), SEEK_SET);
        fread (&a, sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void ImprimirTabela(char *NomeArq){
    FILE *arq = fopen(NomeArq,"rb");
    Aluno a;
    int pos;
     printf("%-15s %-15s %-50s %-20s\n", "Posição", "Matrícula", "Nome", "Curso");
    for(pos=0;pos<=N;pos++){
      fseek(arq, pos * sizeof(Aluno),SEEK_SET);
      fread(&a, sizeof(Aluno),1,arq);
      
      if(a.disponibilidade==1){
          printf("%-15d%-15s %-50s %-20s \n", pos, "*****", "*****", "*****");
      }else{
          printf("%-15d %-15d %-50s %-20s \n", pos, a.matricula, a.nome, a.curso);
      }
    }
fclose(arq);
}

int busca(char *NomeArq, int key){
    Aluno a;
    int pos=hash(key,N);
    FILE *arq= fopen(NomeArq,"rb");
    fseek(arq, pos * sizeof(Aluno),SEEK_SET);
    fread(&a, sizeof(Aluno),1,arq);
    
    while(a.matricula!= key && a.disponibilidade!= 1){
        pos=hash(key+1,N);
        fseek(arq, pos * sizeof(Aluno),SEEK_SET);
        fread(&a, sizeof(Aluno),1,arq);
    }
fclose(arq);
return pos;
}

void ImprimirDeterminado (char* NomeArq){
    int key;
    printf("Digite a matrícula do aluno: ");
    scanf("%d",&key);
 
  key= busca("hashing.bin",key);
  FILE *arq=fopen(NomeArq,"rb");
  Aluno a;
  fseek(arq, key * sizeof(Aluno),SEEK_SET);
  fread(&a,sizeof(Aluno),1,arq);
  printf("Aluno: %s \n",a.nome);
  printf("Matrícula: %d \n",a.matricula);
  printf("Curso: %s \n",a.curso);
  fclose(arq);
}

int main(){
setlocale(LC_ALL, "Portuguese");
int op;    
printf("Insira a quantidade de posições da tabela de dispersão: ");
scanf("%d",&N);
inicializar("hashing.bin"); //Iniciando a tabela 

do{
printf("\n                                 Menu                                 \n");
printf("1. Inserir um novo aluno (matrícula, nome, curso)\n");
printf("2. Imprimir as informações de um determinado aluno (busca pela matricula)\n");
printf("3. Imprimir a tabela de dispersão (tabela hash)\n");
printf("4. Sair\n");
printf("\n------------------------------------------------------------------------\n");
scanf("%d",&op);
switch(op){
    case 1:
    int Matricula;
    char Nome[50],curso[30];
    printf("Nome do aluno: ");
    scanf("%s",&Nome);
    printf("Matricula do aluno: ");
    scanf("%d",&Matricula);
    printf("Curso do Aluno: ");
    scanf("%s",&curso);
    Inserir("hashing.bin",Nome,Matricula,curso);
    break;
    case 2:
    ImprimirDeterminado("hashing.bin");
    break;
    case 3:
    ImprimirTabela("hashing.bin");
    break;
}

}while(op!=4);
}



