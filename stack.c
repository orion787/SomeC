#include <stdio.h>
#include <stdlib.h>

struct stacknode{
    struct stacknode *next;
    void *data;
};

struct stacknode *stack_init(){
    struct stacknode *stack = malloc(1 * sizeof(struct stacknode));
    return stack;
}

void stack_push( struct stacknode **stack, void *node){
    struct stacknode *tmp = calloc(1, sizeof(struct stacknode));
    if(tmp == NULL)
        abort();

    tmp->data = node; tmp->next = *stack;
    *stack = tmp;
}
char is_empty(const struct stacknode *stack){
    if(stack == NULL)
        return 1;
    return 0;
}
struct stacknode *stack_pop(struct stacknode **top){
    void *data = (*top)->data;
    struct stacknode *next = (*top)->next;
    free(*top);
    *top = next;
    return data;
}

void *stack_pic(const struct stacknode **top){
    return (*top)->data;
}

void stack_free(struct stacknode **stack){
    while(!is_empty(*stack)){
        struct stacknode *next = (*stack)->next;
        free(*stack);
        *stack = next;
    }
}
