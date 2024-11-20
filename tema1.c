/*BUDURAN CATALINA-ANDREEA, 311 CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "Operatii.h"
#include "Stack.h"

int main () {
    int nr;
    FILE *inputfile;
    inputfile = fopen("tema1.in", "r");
    FILE *outputfile;
    outputfile = fopen("tema1.out", "w");
    char op[20];
    TBanda banda = initBanda(); //creez banda
    TQueue queue = createQueue(); //creez coada
    // TStack s_redo = createStack(); //creez stiva redo
    // TStack s_undo = createStack(); //creez stiva undo
    fscanf(inputfile, "%d", &nr); //citesc numarul de operatii
    fgets(op, 20, inputfile);
    for(int i = 0; i< nr; i++) {
        fgets(op, 20, inputfile); //citesc fiecare operatie
        op[strcspn(op, "\n")] = '\0'; //pas pentru a trece la urmatoarea operatie citita
        if(strcmp(op, "EXECUTE") != 0 && strcmp(op, "SHOW") != 0 && strcmp(op, "SHOW_CURRENT") != 0) { //adaug in coada doar operatiile de tip UPDATE
            enqueue(&queue, strdup(op)); 
        }
        if (strcmp(op, "SHOW_CURRENT") == 0) //daca operatia citita este SHOW_CURRENT, apelez functia
            SHOW_CURRENT(banda, outputfile);
        if (strcmp(op, "SHOW") == 0) { //daca operatia citita e SHOW, apelez functia
            SHOW(banda, outputfile);
        }
        if (strstr(op, "EXECUTE") != NULL) { //daca operatia citita e EXECUTE, verific ce operatie se afla pe primul nod din coada si o apelez
            if (strstr(queue->front->data, "WRITE")) {
                // freeStack(&s_undo);
                WRITE(&banda, queue->front->data[6]);
            }
        else 
            if (strstr(queue->front->data, "MOVE_LEFT_CHAR")) {
                MOVE_LEFT_CHAR(banda, queue->front->data[15], outputfile);
            }
        else
            if (strstr(queue->front->data, "MOVE_RIGHT_CHAR")) {
                MOVE_RIGHT_CHAR(&banda, queue->front->data[16]);
            }
        else
            if (strstr(queue->front->data, "MOVE_LEFT")) {
                TList temp = banda->nod_curent;
                // push(&s_undo, temp);
                MOVE_LEFT(banda);
            }
        else 
            if (strstr(queue->front->data, "MOVE_RIGHT")) {
                TList temp = banda->nod_curent; //retin adresa nodului curent\
                push(&s_undo, temp); //adaug in undo adresa initiala a nodului curent
                MOVE_RIGHT(banda);
            }
        else
            if (strstr(queue->front->data, "INSERT_RIGHT")) {
                INSERT_RIGHT(banda, queue->front->data[13]);
            }
        else
            if (strstr(queue->front->data, "INSERT_LEFT")) {
                INSERT_LEFT(banda, queue->front->data[12], outputfile);
            }
        else
            if (strstr(queue->front->data, "UNDO")) { //am pus in stiva undo
                TStack p;
                // p = pop2(s_undo); //extrag si retin adresa nodului din varful stivei undo
                // push(&s_redo, banda->nod_curent); //introduc adresa nodului curent in redo
                // banda->nod_curent = p->nod_curent; //modific pozitia nodului curent
            }
        else 
            if (strstr(queue->front->data, "REDO")) {
                TStack r;
                // r = pop2(s_redo); //extrag si retin adresa nodului din varful stivei redo
                // push(&s_undo, banda->nod_curent); //introduc adresa nodului curent in undo
                // banda->nod_curent = r->nod_curent; //modific pozitia nodului curent
            }
        dequeue(&queue); //elimin operatia citita din coada
        }
    }
    fclose(outputfile);
    fclose(inputfile);
    destroyQueue(queue);
    destroyBanda(banda);
    // freeStack(s_redo);
    // freeStack(s_undo);
    return 0;
}