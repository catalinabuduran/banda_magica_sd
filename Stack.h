/*BUDURAN CATALINA-ANDREEA, 311 CD*/
#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

#include "Operatii.h"

typedef char T;
typedef struct stack {
    TList nod_curent;
    struct stack *next;
}Stack, *TStack;

TStack createStack () { //functie care creeaza o stiva
    TStack stack = malloc(sizeof(struct stack));
	stack->next = NULL;
	return stack; 
}

TStack initStack(TList node) {
    TStack stack = malloc(sizeof(struct stack));
    stack->nod_curent = node;
	stack->next = NULL;
	return stack; 
}

int isEmptyStack(TStack stack) { //functie care verifica daca o stiva este goala sau nu
    return stack == NULL;
}

void push(TStack *stack, TList node) { //functie care adauga un nod intr-o stiva
    TStack top;
    top = initStack(node);
    top->next = *stack;
    *stack = top;
}

TStack pop(TStack stack) { //functie care elimina un nod dintr-o stiva 
    Stack *tmp;
    if (isEmptyStack(stack))
        return NULL;
    tmp = stack;
    stack = stack->next;
    return stack;
    free(tmp);
}

TStack pop2(TStack stack) { //functie care elimina un nod dintr-o stiva si-l returneaza
    Stack *tmp;
    if (isEmptyStack(stack))
        return NULL;
    tmp = stack;
    stack = stack->next;
    return tmp;
}

void freeStack(TStack *stack) { //eliberez memoria alocata stivei
    while(!isEmptyStack(*stack))
        *stack = pop(*stack);
}

#endif