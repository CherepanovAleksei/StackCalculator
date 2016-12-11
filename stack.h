#pragma once

#include "struct.h"

int comparison(dbl_list *dbll);
void change_sign(dbl_list *dbll);
node* node_create();
void node_add(dbl_list *dbll, int c, int flag, char minus);
void node_del(dbl_list *dbll);
void number_delete(dbl_list *dbll);
dbl_list* create_dbl_list();
void delete_dbl_list(dbl_list **dbll);
void print_resalt(dbl_list *dbll);
void buff_to_dbll(dbl_list *dbll_buff, dbl_list *dbll);
void roll(dbl_list *dbll);
