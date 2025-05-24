#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pessoas {
	int ocupacao;
	void *info;
	struct Pessoas *prox;
} Pessoas;

typedef struct Aluno {
	int matricula;
	char nome[50];
	char curso[30];
	int ano_de_ingresso;
} Aluno;

typedef struct Professor {
	int matricula;
	char nome[50];
	float salario;

} Professor;

Pessoas* Inicializar() {
	Pessoas *l=(Pessoas *)malloc(sizeof(Pessoas));
	l->prox=NULL;
	l->ocupacao=0;
	l->info=NULL;
	printf("O vetor foi inicializado\n");
	return l;
}

Pessoas* Inserir(Pessoas *l) {
	Pessoas *Nova=(Pessoas *)malloc(sizeof(Pessoas));
	Nova->prox=l;
	Nova->ocupacao=0;
	Nova->info=NULL;
	return Nova;
}

Pessoas* Remover(Pessoas *vet, int matricula) {
    Pessoas *anterior = NULL;
    Pessoas *atual = vet;

    while (atual != NULL) {
        if (atual->ocupacao == 1) {
            Aluno *a = (Aluno *)atual->info;
            if (a->matricula == matricula) {
                break;
            }
        } else if (atual->ocupacao == 2) {
            Professor *p = (Professor *)atual->info;
            if (p->matricula == matricula) {
                break;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            vet = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual->info); 
        free(atual); 
        printf("Pessoa removida com sucesso.\n");
    } else {
        printf("Pessoa com a matricula %d nao encontrada\n", matricula);
    }
    return vet;
}

void DestruirLista(Pessoas *vet) {
    Pessoas *atual = vet;
    Pessoas *temp;

    while (atual != NULL) {
        temp = atual->prox;
      
        if (atual->info != NULL) {
            free(atual->info);
        }
        free(atual);
        atual = temp;
    }
}

void Buscar(Pessoas *atual,int matricula) {
	while(atual!=NULL) {
		if(atual->ocupacao==1) {
			Aluno *a=(Aluno *)atual->info;
			if(a->matricula=matricula) {
				printf("ALUNO       |Nome:%s Matricula: %d Curso:%s Ano de Ingresso:%d \n",a->nome,a->matricula,a->curso,a->ano_de_ingresso);
				return;
			}
		} else {
			Professor *p=(Professor*)atual->info;
			if(p->matricula=matricula) {
				printf("PROFESSOR   |Nome:%s Matricula: %d salário:%.2f \n",p->nome,p->matricula,p->salario);
				return;
			}
		}
		atual=atual->prox;
	}

	printf("Essa pessoa não foi encontrada\n");

}

int contarAlunos(Pessoas *vet,char *curso) {
	int cont=0;
	Pessoas *lista=vet;
	while(lista!=NULL) {
		if(lista->ocupacao==1) {
			Aluno *a=(Aluno *)lista->info;
			if(strcmp(a->curso,curso)==0) {
				cont++;
			}
		}
		lista=lista->prox;
	}
	return cont;
}

void ImprimirProfMaiorSalario(Pessoas *vet) {
	Pessoas *atual=vet;
	Pessoas *PmaiorSalario=NULL;
	float ValorMaiorSalario=0;
	while(atual!=NULL) {
		if(atual->ocupacao==2) {
			Professor *p=(Professor *)atual->info;
			if(p->salario>ValorMaiorSalario) {
				ValorMaiorSalario=p->salario;
				PmaiorSalario=atual;
			}
		}
		atual=atual->prox;
	}
	if(PmaiorSalario!=NULL) {
		Professor *p=(Professor *)PmaiorSalario->info;
		printf("PROFESSOR DE MAIOR SAlÁRIO*************************\n");
		printf("Nome:%s Matricula: %d salário:%.2f \n",p->nome,p->matricula,p->salario);
	} else {
		printf("A LISTA ESTÁ VAZIA");
	}
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	Pessoas *vet=Inicializar();
	int op;
	int m;//variavel auxiliar
	while(op!=6) {
		op=0;
		printf("\n-----------------------MENU-------------------------");
		printf("\n1. Inserir uma pessoa na lista");
		printf("\n2. Remover uma pessoa pela matrícula");
		printf("\n3. Buscar uma pessoa pela matrícula ");
		printf("\n4. Contar o número de alunos e um determinado curso");
		printf("\n5. Imprimir o professor de maior salário");
		printf("\n6. Sair");
		printf("\n---------------------------------------------------\n");
		scanf("%d",&op);
		switch(op) {
		case 1:
			printf("\n-------------------INSERIR PESSOA-------------------\n");
			printf("1.Inserir Aluno\n");
			printf("2.Inserir Professor\n");
			int op=0;
			scanf("%d",&op);
			switch(op) {
			case 1:
				printf("\n-------------------INSERIR ALUNO--------------------\n");
				Aluno *a;
				a=(Aluno*)malloc(sizeof(Aluno));
				printf("Insira o nome: ");
				scanf("%s",a->nome);
				fflush(stdin);
				printf("\nInsira a matrícula: ");
				scanf("%d",&a->matricula);
				printf("\nInsira o curso: ");
				scanf("%s",a->curso);
				fflush(stdin);
				printf("\nInsira o ano de ingresso do aluno: ");
				scanf("%d",&a->ano_de_ingresso);
				vet=Inserir(vet);
				vet->ocupacao=1;
				vet->info=a;
				printf("%s de matricula %d do curso de %s ingressante em %d foi INSERIDO como ALUNO.\n",a->nome,a->matricula,a->curso,a->ano_de_ingresso);
				break;
			case 2:
				printf("\n------------------INSERIR PROFESSOR------------------\n");
				Professor *p;
				p=(Professor*) malloc (sizeof(Professor));
				printf("Insira o nome: ");
				scanf("%s",p->nome);
				fflush(stdin);
				printf("\nInsira a matrícula: ");
				scanf("%d",&p->matricula);
				printf("\nInsira o salário: ");
				scanf("%f",&p->salario);
				vet=Inserir(vet);
				vet->ocupacao=2;
				vet->info=p;
				printf("%s de matricula %d com o salario de R$ %.2f foi INSERIDO como Professor ",p->nome,p->matricula,p->salario);
				break;
			default:
				printf("\nOpção inválida tente novamente");
				break;
			}
			break;
		case 2:
			printf("\n-------------------REMOVER PESSOA-------------------\n");
			printf("Digite a matricula: ");
			scanf("%d",&m);
			getchar();
			vet=Remover(vet,m);
			break;
		case 3:
			printf("\n-------------------BUSCAR PESSOA-------------------\n");
			printf("Digite a matricula: ");
			scanf("%d",&m);
			getchar();
			Buscar(vet,m);
			break;
		case 4:
			printf("\n--------CONTAR ALUNOS DE UM DETERMINADO CURSO-------\n");
			printf("Digite o curso: ");
			char Stringaux[30];
			scanf("%s",Stringaux);
			fflush(stdin);
			int x=contarAlunos(vet,Stringaux);

			if(x==0) {
				printf("não há alunos nesse curso\n");
			} else {
				printf("%s possui %d aluno(s) \n",Stringaux,x);
			}
			break;
		case 5:
			ImprimirProfMaiorSalario(vet);
			break;
		case 6:
		printf("saindo...");
		DestruirLista(vet);
			break;
		default:
			printf("\nOpção inválida tente novamente");
			break;
		}
	}
}