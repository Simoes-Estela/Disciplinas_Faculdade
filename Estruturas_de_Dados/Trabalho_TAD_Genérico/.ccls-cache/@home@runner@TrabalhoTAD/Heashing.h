typedef struct registro *Registro;
void inserir(char *nomeArq, int chave, void* dados, int tamanhoDados);
void imprimir(char *nomeArq);
int buscar(char *nomeArq, int *chave, void* dados, int tamanhoDados);
void Destruir(char *nomeArq);
void inicializar(char *nomeArq);
