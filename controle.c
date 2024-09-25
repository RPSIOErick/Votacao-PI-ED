#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validacoes.c"

void Menu();
void MenuPt2();
bool verifyCPF();
bool verifyTG();
void vote();
void suspendVote();
void concludeVote();
void continueVote();

void MenuPt2() {

    char op2;

    printf("Menu - 2: \n");

    printf("A) Entrar com voto\n");
    printf("B) Suspender votacao\n");
    printf("C) Concluir votacao\n");
    printf("Insira a opcao desejada!");

    scanf(" %c", &op2);

    while (op2 != 'a' && op2 != 'b' && op2 != 'c' && op2 != 'A' && op2 != 'B' && op2 != 'C') {
        printf("Opcao nao identificada\n");
        printf("\nDigite uma opcao valida: ");
        scanf(" %c", &op2);
    }

    if(op2 == 'a' || op2 == 'A') {
        printf("Digite seu CPF: ");
        char cpf[15];
        scanf("%s", cpf);

        while (!verifyCPF(cpf)) {
            printf("\nCPF invalido, digite-o novamente:");
            scanf("%s", cpf);
        }

        printf("Digite o codigo do trabalho de graduacao: ");
        int codTrabalho;
        scanf("%d", &codTrabalho);

        while (!verifyTG(codTrabalho)) {
            printf("Codigo invalido, digite-o novamente:");
            scanf("%d", &codTrabalho);
        }

        vote(cpf, codTrabalho);
        MenuPt2();
    }

    if(op2 == 'b' || op2 == 'B') {
        suspendVote();
    }

    if(op2 == 'c' || op2 == 'C') {
        concludeVote();
    }
}

void Menu() {

    char op;

    printf("Menu - 1: \n");

    printf("A) Iniciar nova votacao \n");
    printf("B) Continuar votacao gravada \n");
    printf("Digite uma das opcoes acima: ");

    scanf(" %c", &op);

    while (op != 'a' && op != 'A' && op != 'b' && op != 'B') {
        printf("Opcao desconhecida.\n");
        printf("\nDigite a opcao novamente: ");
        scanf(" %c", &op);
    }

    if(op == 'a' || op == 'A') {
        MenuPt2();
    }
    else if(op == 'b' || op == 'B') {
        continueVote();
    }
};

bool verifyCPF(char cpf[]) {
    if(!isCPFValid(cpf)) {
        printf("\nO CPF nao e valido!");
        return false;
    }

    for (int i = 0; i < max; i++) {
        if(strcmp(comis[i].cpf, cpf) == 0 && comis[i].votou == true) {
            printf("\nO eleitor %s ja realizou seu voto!\n", cpf);
            return false;
        }
        else if(strcmp(comis[i].cpf, cpf) == 0 && comis[i].votou == false) {
            return true;
        }
    }

    printf("\nO CPF nao foi encontrado!");
    return false;
}

bool verifyTG(int cod) {
    for (int i = 0; i < max; i++) {
        if(listaDeTgs[i].codTra == cod) {
            return true;
        }
    }

    printf("\nTrabalho nao encontrado... \n");
    return false;
}

void vote(char cpf[], int codTrabalho) {
    for(int i = 0; i < max; i++) {
        if(strcmp(comis[i].cpf, cpf) == 0 ) {
            comis[i].votou = true;
            comis[i].codTg = codTrabalho;
        }
    }

    for (int j = 0; j < max; j++) {
        if(listaDeTgs[j].codTra == codTrabalho) {
            listaDeTgs[j].qtdVot++;
            printf("\nVoto armazenado com sucesso!\n");
        }
    }

    qtdEleitores++;
}

void suspendVote() {
    FILE *fVote = fopen("parcial.txt", "w");
    fprintf(fVote, "%d\n", qtdEleitores);
    for (int i = 0; i < max; i++) {
        if(comis[i].votou == true) {
            fprintf(fVote, "%s %d\n", comis[i].cpf, comis[i].codTg);
        }
    }

    fclose(fVote);
    printf("\nVotacao suspensa. \nOs dados do eleitor foram salvos.");
    exit(0);
}

void concludeVote() {
    FILE *fFinal = fopen("resultado.txt", "w");

    int maior = 0;
    int vencedor = -1;

    for(int i = 0; i < qtdTGs; i++) {
        if(listaDeTgs[i].qtdVot > maior) {
            maior = listaDeTgs[i].qtdVot;
        }
    }

    fprintf(fFinal, "\nOs PIs que venceram sao: \n");
    for (int i = 0; i < qtdTGs; i++) {
        if(listaDeTgs[i].qtdVot == maior) {
            int estudante;
            for(int j = 0; j < max; j++) {
                if(formandos[j].matricula == listaDeTgs[i].codAut) {
                    estudante = j;
                }
            }

            int orientador;
            for(int j = 0; j < max; j++) {
                if(docentes[j].codProf == listaDeTgs[i].codOrie) {
                    orientador = j;
                    break;
                }
            }

            fprintf(fFinal, "\nCodigo do trabalho: %d\n", listaDeTgs[i].codTra);
            fprintf(fFinal, "Titulo: %s\n", listaDeTgs[i].titulo);
            fprintf(fFinal, "Aluno: %s\n", formandos[estudante].alu.nome);
            fprintf(fFinal, "Curso: %s\n", formandos[estudante].depart);
            fprintf(fFinal, "Orientador: %s\n", docentes[orientador].prof.nome);
            fprintf(fFinal, "Curso do Orientador: %s\n", docentes[orientador].depart);
            fprintf(fFinal, "Votos no total: %d\n", listaDeTgs[i].qtdVot);
        }
    }

    fprintf(fFinal, "\nEleitores presentes: \n");
    for(int i = 0; i < max; i++) {
        if(comis[i].votou) {
            fprintf(fFinal, "%s\n", comis[i].cpf);
        }
    }

    fprintf(fFinal, "\nEleitores ausentes: \n");
    for(int i = 0; i < max; i++) {
        if(!comis[i].votou) {
            fprintf(fFinal, "%s\n", comis[i].cpf);
        }
    }

    fclose(fFinal);
    printf("\nVotacao concluida. \nO resultado foi armazenado no arquivo: resultado.txt");
    exit(0);
}

void continueVote() {
    FILE *fParcial = fopen("parcial.txt", "r");
    if(fParcial == NULL) {
        printf("\nO arquivo de votos parciais nao foi encontrado!");
        Menu();
    }

    int aux;
    fscanf(fParcial, "%d", &aux);

    printf("\nQuantidade de Eleitores: %d\n", aux);

    char buffer[100];
    char cpf[15];
    int codTrabalho = 0;

    fgets(buffer, sizeof(buffer), fParcial);
    for(int i = 0; i < aux; i++) {
        fgets(buffer, sizeof(buffer), fParcial);
        sscanf(buffer, "%s %d", cpf, &codTrabalho);

        for(int j = 0; j < max; j++) {
            if(strcmp(comis[i].cpf, cpf) == 0) {
                vote(cpf, codTrabalho);
            }
        }
    }

    fclose(fParcial);
    qtdEleitores = aux;

    printf("\nVotacao retomada");
    MenuPt2();
}
