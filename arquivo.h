#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 50
#define maxnome 50
#define maxsigla 10

typedef struct pessoa {
    char nome[maxnome];
    int idade;
} Pessoa;

typedef struct professor {
    Pessoa prof;
    int codProf;
    char depart[maxsigla];
} Professor;

typedef struct aluno {
    Pessoa alu;
    int matricula;
    int ano;
    char depart[maxsigla];
} Aluno ;

typedef struct tg {
    int codTra;
    int codAut;
    int codOrie;
    char titulo[maxnome];
    int qtdVot;
} Tg ;

typedef struct eleitor {
    char cpf[15];
    bool votou;
    int codTg;
} Eleitor ;

// Variáveis globais
Professor docentes[max];
int qtdDocen;
Aluno formandos[max];
int qtdFormandos;
Tg listaDeTgs[max];
int qtdTGs = 0;
Eleitor comis[max];
int qtdEleitores;