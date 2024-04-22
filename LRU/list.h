#pragma once 

struct List;
struct ListItem;

struct List* create_list();
struct ListItem* create_listitem();

void destruct_list(struct List*);
void destruct_listitem(struct ListItem*);

void insert_to_list(struct List*, struct ListItem*);
void lift_listitem(struct List*, struct ListItem*);
void print_list(struct List*);

struct ListItem* get_next(struct ListItem*);
struct ListItem* get_prev(struct ListItem*);

struct ListItem* get_head(struct List*);
struct ListItem* get_tail(struct List*);
