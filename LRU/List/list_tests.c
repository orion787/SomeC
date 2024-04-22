#include <stdio.h>
#include "list.h"

typedef struct List List;
typedef struct ListItem ListItem;

void test1(){
  List* list = create_list();
  ListItem* item = create_listitem(8);
  insert_to_list(list, item);
  destruct_list(list);
}


void test2(){
  List* list = create_list();
  ListItem* item = create_listitem(8);
  insert_to_list(list, item);
  
  ListItem* item2 = create_listitem(10);
  insert_to_list(list, item2);
  
  print_list(list);
  destruct_list(list);
}

void test3(){
  List* list = create_list();
  ListItem* tmp;
  
  for(int i = 0; i < 10; i++){
    ListItem* elem = create_listitem(i);
    insert_to_list(list, elem);
  }
  print_list(list);
  
  tmp = get_head(list);
  for(int i = 0; i < 10; i++){
    ListItem* next = get_next(tmp);
    lift_listitem(list, tmp);
    tmp = next;
  }
  print_list(list);
  
  destruct_list(list);
}
void test4(){}

int main(){
  test1();
  test2();
  test3();
}
