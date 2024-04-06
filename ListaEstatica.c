#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int maxFuncionarios = 15;
int add = 0;

typedef struct funcionario {
    char nome[50], cargo[20], sexo;
    int idade, nMatricula;
} Funcionario;

void criarVetor(Funcionario vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i].nMatricula = 0;
        strcpy(vet[i].nome, "");
        strcpy(vet[i].cargo, "");
        vet[i].sexo = '\0';
        vet[i].idade = 0;
    }
}
void lerCSV(const char* arquivo, Funcionario vet[], int* numPessoas) {
    FILE* file = fopen(arquivo, "r");
    char linha[100];
    char nome[50], cargo[20], sexo;
    int idade, nMatricula;
    //
    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo - Arquivo inexistente.\n");
        return;
    }

    // Ignora o cabeçalho
    fgets(linha, 100, file);

    // Lê e armazena cada linha do arquivo CSV no vetor de structs
    *numPessoas = 0;
    int nMatriculaAnterior = -1;
    while (fgets(linha, 100, file) != NULL) {
        // Extrai os dados da linha
        sscanf(linha, "%[^,],%[^,],%c,%d,%d", nome, cargo, &sexo, &idade, &nMatricula);
        if((nMatricula != 0) && (nMatricula != nMatriculaAnterior)){
          strcpy(vet[*numPessoas].nome, nome);
          strcpy(vet[*numPessoas].cargo, cargo);
          vet[*numPessoas].sexo = sexo;
          vet[*numPessoas].idade = idade;
          vet[*numPessoas].nMatricula = nMatricula;
          (*numPessoas)++;
          nMatriculaAnterior = nMatricula;
          add++;
        }
    }

    // Fecha o arquivo
    fclose(file);
}
void adicionarColaborador(Funcionario vet[], int tamanho) {
    printf("---------------------------------------------------------------\n");
    printf("\n");
    printf("INFORME O NOME:");
    scanf(" %s", vet[add].nome);
    printf("INFORME O CARGO:");
    scanf(" %s", vet[add].cargo);
    printf("INFORME O SEXO:");
    scanf(" %c", &vet[add].sexo);
    fflush(stdin);
    printf("INFORME A IDADE:");
    scanf(" %d", &vet[add].idade);
    printf("INFORME A MATRICULA:");
    scanf(" %d", &vet[add].nMatricula);
    add++;
    system("cls");
}

void imprimirFuncionarios(Funcionario vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("---------------------------------------------------------------\n");
        if (vet[i].nMatricula != 0) {
            printf("Funcionario %d\n", i + 1);
            printf("Nome: %s\n", vet[i].nome);
            printf("Cargo: %s\n", vet[i].cargo);
            printf("Sexo: %c\n", vet[i].sexo);
            printf("Idade: %d\n", vet[i].idade);
            printf("Matricula: %d\n", vet[i].nMatricula);
        }
        printf("---------------------------------------------------------------\n");
    }
}

void removerFuncionario(Funcionario vet[], int tamanho) {
    imprimirFuncionarios(vet, tamanho);
    int indice;
    printf("Informe o funcionario que deseja remover:");
    scanf(" %d", &indice);
    indice--; // Ajuste para o índice do vetor
    vet[indice].nMatricula = 0; // Removendo o funcionário

    // Realocando os funcionários posteriores
    for (int k = indice; k < tamanho - 1; k++) {
        strcpy(vet[k].nome, vet[k + 1].nome);
        strcpy(vet[k].cargo, vet[k + 1].cargo);
        vet[k].sexo = vet[k + 1].sexo;
        vet[k].idade = vet[k + 1].idade;
        vet[k].nMatricula = vet[k + 1].nMatricula;
    }

    // Zerando os dados do último funcionário
    strcpy(vet[tamanho - 1].nome, "");
    strcpy(vet[tamanho - 1].cargo, "");
    vet[tamanho - 1].sexo = '\0';
    vet[tamanho - 1].idade = 0;
    vet[tamanho - 1].nMatricula = 0;
    add--;
    system("cls");
}

void escreverCSV(const char* arquivo, Funcionario colaboradores[], int numPessoas) {
    FILE* file = fopen(arquivo, "w");

    // Verifica se o arquivo foi aberto corretamente
    if (!file) {
        fprintf(stderr, "Erro ao criar o arquivo.\n");
        return;
    }

    // Escreve o cabeçalho no arquivo CSV
    fprintf(file, "Nome,Cargo,Sexo,Idade,Matricula\n");

    // Escreve os dados das pessoas no arquivo CSV
    for (int i = 0; i < numPessoas; ++i) {
        fprintf(file, "%s,%s,%c,%d,%d\n", colaboradores[i].nome, colaboradores[i].cargo, colaboradores[i].sexo, colaboradores[i].idade, colaboradores[i].nMatricula);
    }

    // Fecha o arquivo
    fclose(file);
}



int main() {
    Funcionario colaboradores[maxFuncionarios];
    const char* arquivo = "dados.csv";
    // Supondo um máximo de 100 pessoas
    int numFuncionarios;

    criarVetor(colaboradores, maxFuncionarios);
    // Lê os dados do arquivo CSV e os armazena no vetor de structs
    lerCSV(arquivo, colaboradores, &numFuncionarios);
  
    int opcao;
    do {
        printf("\n1-Adicionar colaborador\n2-Remover colaborador\n3-Imprimir colaboradores\n0-Sair\n\nDigite a opcao:");
        scanf("%d", &opcao);
        printf("\n");
    if(opcao==1){
      adicionarColaborador(colaboradores, add);
    }
    else if(opcao==2){
      removerFuncionario(colaboradores, add);
    }
    else if(opcao==3){
      imprimirFuncionarios(colaboradores, add);
    }
    else if (opcao==0){
      printf("Programa Encerrado ¯\\_(ツ)_/¯");
    }
  }while(opcao!=0);
  
  int numPessoas = sizeof(colaboradores) / sizeof(colaboradores[0]);

  // Gera o arquivo CSV
  escreverCSV("dados.csv", colaboradores, numPessoas);
  return 0;
}