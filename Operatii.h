/*BUDURAN CATALINA-ANDREEA, 311 CD*/
#ifndef OPERATII_H_
#define OPERATII_H_

#include <stdio.h>
#include <stdlib.h>

typedef char T;
typedef struct list {
    T value;
    struct list *prev;
    struct list *next;
} Node, *TList;

typedef struct banda{
    TList sentinel;
    TList nod_curent; 
}Punct, *TBanda;

Node *createNode(T value) { //functie care creeaza un nod
    Node *node = malloc(sizeof(struct list));
    node->value = value;
    node->next = NULL;
    return node;
}

TList createList(T value) { //functie care creeaza o lista 
    TList lista = (TList) malloc(sizeof(struct list));
    lista->value = value;
    lista->prev = NULL;
    lista->next = NULL;
    return lista;
}

TBanda initBanda() { //functie care creeaza si initializeaza banda, o lista dublu inlantuita cu santinela
        TBanda banda = malloc(sizeof(struct banda));
        banda->sentinel = calloc(1, sizeof(Node));
        TList next = calloc(1, sizeof(Node));
        banda->sentinel->next = next;
        banda->sentinel->prev = NULL;
        next->value = '#'; //pun # pe caracterul imediat urmator santinelei
        next->next = NULL;
        next->prev = banda->sentinel->next;
        banda->nod_curent = next;
        return banda;      
}

void destroyBanda(TBanda banda) { //functie care dezaloca memoria pentru banda creata anterior
    TList node = banda->sentinel->next;
    TList iter;
    while (node != NULL) {
        iter = node;
        node = node->next;
        free(iter);
    }
    free(banda->sentinel);
    free(banda);
}

void MOVE_LEFT(TBanda banda) { //functie care deplaseaza pozitia nodului curent spre stanga; daca nodul curent repretinva primul nod din banda, cel de dupa santinela, nu se poate efectua operatia
    if (banda->nod_curent == banda->sentinel->next )
                        return;
    else {
        banda->nod_curent = banda->nod_curent->prev;
    }
}

void MOVE_RIGHT(TBanda banda) { //functie care muta nodul curent cu o pozitie la dreapta, daca acesta reprezinta ultimul nod din banda, se insereaza un nod nou pe care se pune # si se modifica pozitia degetului
    if (banda->nod_curent->next == NULL) {
        TList head = banda->sentinel; 
        while(head->next != NULL) { //aici se parcurge banda si cand se iasa din while, head pointeaza catre ultimul nod din banda
            head = head->next;
        }
        Node *node = createNode('#');
        head->next = node; //aici se fac legaturile intre noul nod inserat si nodul curent
        node->prev = head;
        banda->nod_curent = node;
    }
    else {
        banda->nod_curent = banda->nod_curent->next;
    }
}

void MOVE_LEFT_CHAR (TBanda banda, char caracter, FILE *outputfile) { //functie care cauta la stanga un anumit caracter, insa eu am scris codul in asa fel incat se parcurge banda de la stanga la dreapta si se cauta ultima aparitie a caracterului cautat
    int p = 0;
    TList pozitie = malloc(sizeof(struct list));
    TList pozitie_noua = malloc(sizeof(struct list));
    pozitie = banda->nod_curent;
    TList node = banda->sentinel->next;
    while(node != banda->nod_curent->next){ //parcurg banda de la stanga la dreapta
        if (node->value == caracter) {
            pozitie_noua = node; //se retine ultima pozitie unde a aparut caracterul cautat
            p = 1;
        }
        node = node->next;
    }
    if (p == 0) { //daca variabila nu s-a modificat, inseamna ca nu s-a gasit caracterul cautat si se afiseaza ERROR, iar pozitia degetului nu se modifica, ramanand cea initiala pe care am salvat-o intr-o variabila la inceputul functiei
        fprintf(outputfile, "ERROR\n");
        banda->nod_curent = pozitie;
    }
    else {
        banda->nod_curent = pozitie_noua; //aici se modifica pozitia degetului daca s a gasit caracterul
    }
}

void MOVE_RIGHT_CHAR (TBanda *banda, char caracter) { //functie care cauta la dreapta un caracter dat
    TList pozitie = malloc(sizeof(struct list));
    pozitie = (*banda)->nod_curent; //retin pozitia initiala a nodului curent
    while ((*banda)->nod_curent != NULL) { //parcurg banda de la stanga la dreapta pana cand se ajunge la ultimul nod daca nu se gaseste caracterul pana atunci
        if ((*banda)->nod_curent->value == caracter) {
                    return; //ies din while daca s a gasit caracterul
        }
    (*banda)->nod_curent = (*banda)->nod_curent->next; 
    }
    
       TList head = (*banda)->sentinel;
        while(head->next != NULL) { //parcurg banda si cand ies din while, pos va pointa catre ultimul nod din lista
            head = head->next;
        }
        Node *node = createNode('#'); //daca nu se gaseste caracterul si se ajunge la ultimul nod din banda, inserez un caracter pe care pun #
        head->next = node; //fac legaturile intre noduri
        node->prev = head;
        (*banda)->nod_curent = node; //modific pozitia nodului curent
} 

int INSERT_LEFT (TBanda banda, T value, FILE *outputfile) { //functie care insereaza un caracter la stanga, atata timp cat nodul curent nu reprezinta primul nod din banda
    TList pos = banda->sentinel;
    while(pos->next != banda->nod_curent) { //parcurg banda si pos va fii nodul situat inaintea nodului curent 
            pos = pos->next;
    }
    if (banda->nod_curent == banda->sentinel->next){ //daca nodul curent e primul nod din lista, nu se realizeaza operatia si se afiseaza ERROR
            fprintf(outputfile, "ERROR\n");
            return 0;}
    else {
        Node *node = createNode(value); // creez nodul pe care il inserez
        node->next = banda->nod_curent; //fac legaturile intre nodul adaugat si nodul curent
        node->prev = pos;
        pos->next = node;
        banda->nod_curent->prev = node; 
        banda->nod_curent = node;
        return 1;
    } 
}

void WRITE(TBanda *banda, char caracter) { //pune caracterul dat pe pozitia pe care se afla nodul curent
    (*banda)->nod_curent->value = caracter;
}

int INSERT_RIGHT (TBanda banda, T value) { //insereaza la dreapta un nod
    Node *node = createNode(value);
    if (banda->nod_curent->next == NULL) { //daca nodul curent e ultimul nod din banda, se adauga noul nod si se fac legaturile intre cele 2 noduri
        node->prev = banda->nod_curent;
        banda->nod_curent->next = node;
        banda->nod_curent = node;
    }
    else {
        Node *iter = banda->nod_curent->next; //retin nodul imediat urmator nodului curent
        node->next = iter; //fac legaturile intre noul nod si nodul de dupa nod curent
        iter->prev = node;
        node->prev = banda->nod_curent;
        banda->nod_curent->next = node;
        banda->nod_curent = node;
    }
    return 1;
}

void SHOW_CURRENT(TBanda banda, FILE *outputfile) { //afiseaza valoarea nodului curent
    fprintf(outputfile, "%c\n", banda->nod_curent->value);
}

void SHOW (TBanda banda, FILE *outputfile) { //afiseaza fiecare nod din banda, rezultand banda in cele din urma
    Node *head = banda->sentinel;
    while( head != NULL) { //parcurg banda
        if (head == banda->nod_curent) {
            fprintf(outputfile, "|%c|", head->value);
        }
        else {
            if(head != banda->sentinel){
                fprintf(outputfile, "%c", head->value);
            }
        }
    head = head->next;
    }
    fprintf(outputfile, "\n");
}

#endif