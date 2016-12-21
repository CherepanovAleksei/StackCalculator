#pragma once

#include "struct.h"


dbl_list_up* up_create();
void up_pop();

dbl_list_num* num_create();
void num_read(char*str_in, int count);
dbl_list_num* num_push_head(dbl_list_up *dbll_base);
void num_pop(dbl_list_up *up_del, dbl_list_num* num_del);
void num_sign_change();

dbl_list_node* node_create();
void node_push_head(long long int fragment_of_num, dbl_list_num* dbll_num);
void node_push_tail(long long int fragment_of_num, dbl_list_num* dbll_num);
void node_pop_head(dbl_list_num* dbll_num);
void node_pop_tail(dbl_list_num* dbll_num);
void node_pop_zeros(dbl_list_up *del_up);

int comparison(dbl_list_num* first, dbl_list_num* second);
void print_resalt();
