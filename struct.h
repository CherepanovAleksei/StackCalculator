#pragma once

typedef struct node
{
    int value; //значение
    int category;//разряд(сколько цифр до начала)
    char minus;
    struct node *next;
    struct node *prev;
    struct node *first;
} node;

typedef struct double_linked_list
{
    int size;
    node *head;
    node *tail;
} dbl_list;
