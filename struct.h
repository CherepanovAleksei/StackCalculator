#pragma once

typedef struct double_linked_list_node
{
    //value of category 9
    long long int value;
    struct double_linked_list_node *next;
    struct double_linked_list_node *prev;
} dbl_list_node;

typedef struct double_linked_list_number
{
    //long long int size;
    char sign;
    struct double_linked_list_node *head;
    struct double_linked_list_node *tail;
    struct double_linked_list_number *next;
    struct double_linked_list_number *prev;
} dbl_list_num;

typedef struct double_linked_list_up
{
    struct double_linked_list_number *head;
    struct double_linked_list_number *tail;
} dbl_list_up;

dbl_list_up* dbll_up;
