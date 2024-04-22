#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

struct ListItem{
  struct ListItem *next;
  struct ListItem *prev;
  int data;
};


struct List{
  struct ListItem *head;
  struct ListItem *tail;
  
  int counter;
  int capacity;
};


struct List* create_list(){
  struct List *list;
  list = (struct List*) calloc(1, sizeof(struct List));
  assert(list);
  return list;
}

struct ListItem* create_listitem(int data){
  struct ListItem *item;
  item = (struct ListItem*) calloc(1, sizeof(struct ListItem));
  item->data = data;
  assert(item);
  return item;
}

void destruct_list(struct List* list){
  struct ListItem* tmp;
  assert(list);
  tmp = list->head;

  for(;tmp != NULL;){
    struct ListItem *next = tmp->next;
    destruct_listitem(tmp);
    tmp=next;
  }
  free(list);
}

void destruct_listitem(struct ListItem* item){
  free(item);
}




void insert_to_list(struct List* list, struct ListItem* item){
  struct ListItem* head, *tail;
  assert(list);
  assert(item);
  
  head = list->head;
  tail = list->tail;
  
  if(head == NULL){
    list->head = item;
    list->tail = item;
    return;
  }

  assert(tail);
  if(head == tail){
    item->next = head;
    head->prev = item;
    list->head = item;
    return;
  }

  assert(head);
  head->prev = item;
  item->next = head;
  list->head = item;
  return;
}
      
void lift_listitem(struct List* list, struct ListItem* item){
  struct ListItem* next, *prev;

  assert(list);
  assert(item);
  assert(list->head);

  if(list->head == item)  return;

  if(list->tail == item)
    list->tail = item->prev;
    
  next = item->next;
  prev = item->prev;

  if(prev)
    prev->next=next;

  if(next)
    next->prev=prev;

  insert_to_list(list, item);
  return;
}

struct ListItem* get_next(struct ListItem* item)  { return item->next; }

struct ListItem* get_prev(struct ListItem* item)  { return item->prev; }

struct ListItem* get_head(struct List* list)  { return list->head; }
struct ListItem* get_tail(struct List* list)  { return list->tail; }

void print_list(struct List* list){
  struct ListItem* tmp;
  assert(list);
  tmp = list->head;

  for(;tmp != NULL;){
    struct ListItem *next = tmp->next;
    printf("%d ", tmp->data);
    tmp=next;
  }
  puts("\n");
}
