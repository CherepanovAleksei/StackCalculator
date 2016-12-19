#pragma once

#include "struct.h"


dbl_list_up* up_create();
void up_pop();

dbl_list_num* num_create();
dbl_list_num* num_push_after(dbl_list_num* num_base);
void num_pop(dbl_list_num* num_del);

dbl_list_node* node_create();
void node_push_head(long long int fragment_of_num, dbl_list_num* dbll_num);
void node_push_tail(long long int fragment_of_num, dbl_list_num* dbll_num);
void node_pop_head(dbl_list_num* dbll_num);
void node_pop_tail(dbl_list_num* dbll_num);

void print_resalt();
