#pragma once

struct stacknode *stack_init();
char is_empty(const char * stack);
void stack_push( struct stacknode **stack, struct node*);
struct stacknode *stack_pop(struct stacknode **top);
void *stack_pic(const struct stacknode **top);
void stack_free(struct stacknode **stack);
