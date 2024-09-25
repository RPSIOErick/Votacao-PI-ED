#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isCPFValid(char cpf[]) {

    int car1 = 0, car2 = 0;

    if(strlen(cpf) != 14) {
        printf("O tamanho nao consta.\n");
        return false;
    }

    if(cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') {
        printf("Arrume as puntuacoes.\n");
        return false;
    }

    for(int i = 0; i < 14; i++) {
        if(i == 3 || i == 7 || i == 11) {
            continue;
        }
        if(!isdigit(cpf[i])) {
            printf("Caracteres invalidos.\n");
            return false;
        }
    }

    for(int i = 0, j = 10; i < 12; i++) {
        if(i == 3 || i == 7 || i == 11) {
            continue;
        }
        car1 += (cpf[i] - '0') * j;
        j--;
    }
    car1 = 11 - (car1 % 11);

    if(car1 >= 10) {
        car1 = 0;
    }

    for (int i = 0, j = 11; i < 13; i++) {
        if(i == 3 || i == 7 || i == 11) {
            continue;
        }
        car2 += (cpf[i] - '0') * j;
        j--;
    }
    car2 = 11 - (car2 % 11);

    if(car2 >= 10) {
        car2 = 0;
    }

    if(car1 == cpf[12] - '0' && car2 == cpf[13] - '0') {
        return true;
    } else {
        return false;
    }

}

bool verifyStudent(int matricula, char depart[]) {
    for(int i = 0; i < max; i++) {
        if(formandos[i].matricula == matricula && strcmp(formandos[i].depart, depart) == 0) {
            return true;
        } else if (formandos[i].matricula == matricula && strcmp(formandos[i].depart, depart) != 0) {
            printf("O aluno existe mas o curso esta incorreto: %s e de %s mas esta no curso de %s", formandos[i].alu.nome, formandos[i].depart, depart);
            return false;
        }
    }

    printf("\nAluno nao encontrado.");
    return false;
}

bool verifyProf(int cod) {
    for(int i = 0; i < max; i++) {
        if(docentes[i].codProf == cod) {
            return true;
        }
    }

    printf("\nProfessor nao encontrado");
    return false;
}
