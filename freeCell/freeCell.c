#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

typedef struct stCarta {
    short int numero;
    char naipe;
    struct stCarta* prox;
}tCarta;
tCarta** primMesa;
tCarta** primNaipe;
tCarta** temp;
tCarta* primMonte = NULL;
void criaLista() {
    int i;
    primMesa = (tCarta**)malloc(sizeof(tCarta*) * 8);
    primNaipe = (tCarta**)malloc(sizeof(tCarta*) * 4);
    temp = (tCarta**)malloc(sizeof(tCarta*) * 4);
    for (i = 0; i < 8; i++)
    {
        primMesa[i] = NULL;

    }
    for (i = 0; i < 4; i++)
    {
        primNaipe[i] = NULL;
        temp[i] = NULL;
    }
}
void geraBaralho() {
    int i;
    char j;
    tCarta* novo;
    for (i = 1; i < 14; i++) {
        for (j = 3; j < 7; j++) {
            novo = (tCarta*)malloc(sizeof(tCarta));
            novo->numero = i;
            novo->naipe = j;
            novo->prox = primMonte;
            primMonte = novo;
        }
    }

}
void embaralhaBaralho() {
    tCarta* ant;
    tCarta* novo;
    ant = primMonte;
    int i, j, sort;
    srand(time(NULL));
    for (i = 0; i < 200; i++) {
        sort = rand() % 52;
        novo = (tCarta*)malloc(sizeof(tCarta));
        novo = primMonte;
        if (sort != 0) {
            for (j = 0; j < sort; j++) {
                ant = novo;
                novo = novo->prox;
            }
            ant->prox = novo->prox;
            novo->prox = primMonte;
            primMonte = novo;
        }
    }

}
void distribuiMesa() {
    int i, j;
    tCarta* novo;
    tCarta* aux;
    for (i = 0; i < 4; i++) {
        novo = primMonte;
        for (j = 0; j < 6; j++) {
            primMonte = primMonte->prox;
            aux = primMonte;
        }
        primMonte = primMonte->prox;
        aux->prox = NULL;
        primMesa[i] = novo;
    }
    for (i = 4; i < 8; i++) {
        novo = primMonte;
        for (j = 0; j < 5; j++) {
            primMonte = primMonte->prox;
            aux = primMonte;
        }
        primMonte = primMonte->prox;
        aux->prox = NULL;
        primMesa[i] = novo;
    }
}
void apagaBaralho() {
    tCarta* apaga = primMonte;
    while (apaga != NULL) {
        primMonte = primMonte->prox;
        free(apaga);
        apaga = primMonte;
    }
}
void imprimeBaralho() {
    tCarta** aux = primMesa;
    tCarta* aux2;
    int i;
    printf("[TEMP]: ");
    for (i = 0; i < 4; i++) {
        if(temp[i] != NULL) printf("%d-[%02d/%c]", i, temp[i]->numero, temp[i]->naipe);
        else printf("%d-[  ]", i);
    }
    printf("\n\n");
    
    for (i = 0; i < 4; i++) {
        printf("[NAPE %d] = ", i);

        if (primNaipe[i] != NULL) {
            aux2 = primNaipe[i];
            while (aux2 != NULL)
            {
                printf(" [%02d/%c] ", aux2->numero, aux2->naipe);
                aux2 = aux2->prox;
            }
        }
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < 8; i++) {
        
        printf("MESA %d:", i);
        if (primMesa[i] != NULL) {
            aux2 = aux[i];
            while (aux2 != NULL) {
                printf(" [%02d/%c] ", aux2->numero, aux2->naipe);
                aux2 = aux2->prox;
            }
        }
        printf("\n");
    }
}

void moveMesaTemp() {
    int  mesaPlace, tempPlace;
    bool disponivel = false;
    tCarta* aux, * ant;

    printf("De qual mesa deseja mover?: ");
    scanf_s("%d", &mesaPlace);
    if (primMesa[mesaPlace] != NULL && (mesaPlace < 8)) disponivel = true;
    else {
        printf("Erro, selecione uma mesa com cartas\n.");
        disponivel = false;}

    printf("Para qual posicao deseja mover?: ");
    scanf_s("%d", &tempPlace);
    if (temp[tempPlace] == NULL && (tempPlace < 4)) disponivel = true;
    else {
        printf("Erro, selecione uma posicao que nao contenha cartas\n.");
        disponivel = false;}

    if (disponivel == true) {
        if (primMesa[mesaPlace]->prox == NULL) {
            temp[tempPlace] = primMesa[mesaPlace];
            primMesa[mesaPlace] = NULL;
        }
        else {
            aux = primMesa[mesaPlace];
            ant = aux;
            while (aux->prox != NULL) {
                ant = aux;
                aux = aux->prox;
            }
            temp[tempPlace] = aux;
            ant->prox = NULL;
        }
        system("cls");
        imprimeBaralho();
    }
}
bool ehVermelho(tCarta* carta) {
    if ((carta->naipe == 3) || (carta->naipe == 4)) {
        return true;
    }
    else return false;
}
bool ehPreto(tCarta* carta) {
    return !(ehVermelho(carta));
}
bool movimentoValido(tCarta* carta, tCarta* cartaDest) {
    if (((ehPreto(carta) && ehVermelho(cartaDest)) ||
        (ehVermelho(carta) && ehPreto(cartaDest)) ||
        (cartaDest == NULL))) {
        if (carta->numero < cartaDest->numero) return false;
        else return true;
    }
}
void moveTempMesa() {
    int mesaPlace, tempPlace;
    bool disponivel;
    tCarta* aux;

    printf("De que posicao em temp deseja mover a carta?: ");
    scanf_s("%d", &tempPlace);
    if (tempPlace > 3) {
        disponivel = false;
        printf("Erro! \nEsta posicao nao existe!\n");
    }
    else disponivel = true;

    printf("Para qual mesa movera: ");
    scanf_s("%d", &mesaPlace);
    if (mesaPlace > 7) {
        disponivel = false;
        printf("Erro! \nEsta posicao nao existe!\n");
    }else disponivel == true;

    aux = primMesa[mesaPlace];
    if (aux != NULL) {
        while (aux->prox != NULL) {
            if (aux == NULL) break;
            aux = aux->prox;
        }
    }
    if (primMesa[mesaPlace] != NULL) {
        if (temp[tempPlace] != NULL && (movimentoValido(temp[tempPlace], aux))) disponivel = true;
        else {
            disponivel = false;
            printf("Erro! \nTente mover para posicoes onde ha cores diferentes e numero menor\n\n");
        }
    }else disponivel = true;

    if (disponivel == true) {
        if ( primMesa[mesaPlace] == NULL) primMesa[mesaPlace] = temp[tempPlace];
        else {
            aux->prox = temp[tempPlace];
            aux->prox->prox = NULL;
        }
        temp[tempPlace] = NULL;
        system("cls");
        imprimeBaralho();
    }
}
void moveMesaNaipe() {
    int naipePlace, mesaPlace;
    tCarta* aux, * aux2, *ant;
    ant = NULL;
    bool disponivel;

    printf("De qual mesa deseja mover cartas?: ");
    scanf_s("%d", &mesaPlace);
    if (mesaPlace > 7) disponivel = false;
    else disponivel = true;

    printf("Em qual naipe deseja colocar?: ");;
    scanf_s("%d", &naipePlace);
    if (mesaPlace > 7) disponivel = false;
    else disponivel = true;
    
    aux = primMesa[mesaPlace];
    if (primMesa[mesaPlace] != NULL) {
        while (aux->prox != NULL) {
            ant = aux;
            aux = aux->prox;
        }
    }

    aux2 = primNaipe[naipePlace];
    if (primNaipe[naipePlace] == NULL && aux->numero == 1) disponivel = true;
    else disponivel = false;
    if(primNaipe[naipePlace] != NULL){
        while (aux2->prox != NULL ) {
            aux2 = aux2->prox;
        }
        if ((aux->naipe == aux2->naipe) && (aux->numero == aux2->numero + 1)) disponivel = true;
        else disponivel = false;
    }
    if (disponivel == true) {
        
        if (aux2 != NULL) aux2->prox = aux;
        else primNaipe[naipePlace] = aux;
        if (primMesa[mesaPlace]->prox == NULL) primMesa[mesaPlace] = NULL;
        else ant->prox = NULL;
        system("cls");
        imprimeBaralho();
    }


}
int main(int argc, char* argv[]) {
    system("color 27");
    int op;
    criaLista();
    geraBaralho();
    embaralhaBaralho();
    distribuiMesa();
    imprimeBaralho();
    do {
        printf("0 - sair.\n"
               "1 - mover para temp.\n"
               "2 - mover de temp para mesa.\n" 
               "3 - mover para naipe.\n"
               "Sua escolha: ");
        scanf_s("%d", &op);
            switch (op)
            {
            case 0:
                break;
            case 1:
                moveMesaTemp();
                
                break;
            case 2:
                moveTempMesa();
                
                break;
            case 3:
                moveMesaNaipe();
                
                break;
                default:
                    break;
            }
    } while (op != 0);
    free(primMesa);
    free(temp);
    free(primMonte);
    free(primNaipe);
    return 0;
}