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
    struct stacknode *tmp = malloc(1 * sizeof(struct stacknode));
    if(tmp == NULL)
        abort();

    tmp->data = node->data; tmp->next = *stack;
    assert(*stack != NULL);
    *stack = tmp;
}
char is_empty(const struct stacknode *stack){
    if(stack->next == NULL)
        return 0;
    return 1;
}
struct stacknode *stack_pop(struct stacknode **top){
    struct node *data = (*top)->data;
    struct stacknode *next = (*top)->next;
    *top = next;
    free(*top);
    return data;
}

void print_preorder(struct node *root){
    struct node *node = NULL;
    if(root == NULL)
        return;

    printf("%d", node->data);
    print_preorder(root->left);
    print_preorder(root->right);
}

void iterative_preorder(struct node *root){
    struct stacknode *stack = NULL;

    stack_push(&stack, root);

    while(!is_empty(&stack)){
        struct stacknode *tmp = stack_pop(&stack);//pop item
        fprintf(stdout, "%d", tmp->data->data);//print item
        stack_push(&stack,tmp->data->left);//push it`s left child
        stack_push(&stack, tmp->data->right);//push it`s right child
    }
    puts("\n");
}

int main ()
{
    return 0;
}
