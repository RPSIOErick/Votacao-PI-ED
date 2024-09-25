#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "controle.c"

void readStudents(Aluno aluns[]) {
    FILE *fAluno;
    fAluno = fopen("aluno.txt", "r");
    if (fAluno == NULL) {
        printf("Erro na abertura do arquivo\n");
    }

    int numAlunos;

    fscanf(fAluno, "%d", &numAlunos);

    char buffer[256];

    fgets(buffer, sizeof(buffer), fAluno);

    for (int i = 0; i < numAlunos; i++) {
        fgets(buffer, sizeof(buffer), fAluno);
        sscanf(buffer, "%d %d %s %d %[^\n]",
            &formandos[i].matricula,
            &formandos[i].ano,
            formandos[i].depart,
            &formandos[i].alu.idade,
            formandos[i].alu.nome
        );
    }

    fclose(fAluno);

}

void readProfessor(Professor profs[]) {
    FILE *fProf;

    fProf = fopen("professor.txt", "r");

    if (fProf == NULL) {
        printf("Erro na abertura do arquivo\n");
    }

    int numProf;

    fscanf(fProf, "%d", &numProf);

    char buffer[256];

    fgets(buffer, sizeof(buffer), fProf);

    for (int i = 0; i < numProf; i++) {
        fgets(buffer, sizeof(buffer), fProf);
        sscanf(buffer, "%d %s %d %[^\n]",
            &docentes[i].codProf,
            docentes[i].depart,
            &docentes[i].prof.idade,
            docentes[i].prof.nome
        );
    }

    fclose(fProf);

}

void readTg(Tg tgs[]) {

    char *arqs[] = {"AMS", "ADS", "DSM", "CEX", "EMP", "LOG", "POL"};

    int qtdArqs = sizeof(arqs) / sizeof(arqs[0]);

    FILE *fTg;

    char buffer[256];

    for(int i = 0; i < qtdArqs; i++) {
        char nomeArq[256];
        strcpy(nomeArq, "PI_");
        strcat(nomeArq, arqs[i]);
        strcat(nomeArq, ".txt");
        fTg = fopen(nomeArq, "r");

        int qtdArqTg;

        fscanf(fTg, "%d", &qtdArqTg);
        fgets(buffer, sizeof(buffer), fTg);

        for(int j = 0; j < qtdArqTg; j++) {

            fgets(buffer, sizeof(buffer), fTg);

            sscanf(buffer, "%d %d %d %[^\n]",
                &tgs[qtdTGs].codTra,
                &tgs[qtdTGs].codAut,
                &tgs[qtdTGs].codOrie,
                tgs[qtdTGs].titulo
            );

            if(!verifyStudent(tgs[qtdTGs].codAut, arqs[i])) {
                printf("Falha na verificação do arquivo %s\n", nomeArq);
                exit(1);
            }

            if(!verifyProf(tgs[qtdTGs].codOrie)) {
                printf("\nFalha na verificação %s \n", nomeArq);
                exit(1);
            }

            qtdTGs++;

        }

        fclose(fTg);

    }
}

void readVoter(Eleitor eleitores[]) {
    FILE *fVoter;

    fVoter = fopen("comissao.txt", "r");

    if (fVoter == NULL) {
        printf("Erro na abertura do arquivo\n");
    }

    int numVoter;

    fscanf(fVoter, "%d", &numVoter);

    char buffer[256];

    fgets(buffer, sizeof(buffer), fVoter);

    for (int i = 0; i < numVoter; i++) {
        fgets(buffer, sizeof(buffer), fVoter);
        sscanf(buffer, "%s %[^\n]",
            comis[i].cpf
        );
    }

    fclose(fVoter);

}

void main() {

    readStudents(formandos);
    readProfessor(docentes);
    readTg(listaDeTgs);
    readVoter(comis);

    Menu();

}
