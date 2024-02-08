#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//typedef struct node node;
struct node{
    struct node *parrent;
    struct node *left;
    struct node *right;
    void *data;
};

struct stacknode{
    struct stacknode *next;
    struct node *data;
};

void stack_push( struct stacknode **stack, struct node *node){
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
    struct node *data = (*top)->data;
    struct stacknode *next = (*top)->next;
    free(*top);
    *top = next;
    return data;
}

void print_preorder(struct node *root){
    if(root == NULL) return;
    printf("%d ", root->data);
    print_preorder(root->left);
    print_preorder(root->right);
}

void iterative_preorder(struct node *root){
    struct stacknode *stack = NULL;
    stack_push(&stack, root);

    while(!is_empty(stack)){
        struct node *n = stack_pop(&stack);
        printf("%d ", n->data);

        if(n->right)
            stack_push(&stack, n->right);

        if(n->left)
            stack_push(&stack, n->left);
    }
    puts("\n");
}

int main ()
{
    struct node *first = calloc(1, sizeof(struct node));
    struct node *second = calloc(1, sizeof(struct node));
    struct node *third = calloc(1, sizeof(struct node));

    first->right = second; first->left = third; first->data = (void *) 8;
    second->data = (void *) 90;
    third->data = (void *) 101;

    iterative_preorder(first);

    return 0;
}
