```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
    char data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *make_tree(char **p)
{
    Tree *node;

    if (**p == '\0')
        return NULL;

    if (**p == '(')
        (*p)++;

    if (**p == ')')
        return NULL;

    if (**p == ',') {
        (*p)++;
        return NULL;
    }

    node = malloc(sizeof(Tree));
    node->data = **p;
    node->left = NULL;
    node->right = NULL;
    (*p)++;

    if (**p == '(') {
        (*p)++;
        node->left = make_tree(p);

        if (**p == ',')
            (*p)++;

        node->right = make_tree(p);

        if (**p == ')')
            (*p)++;
    }

    return node;
}

void print_tree(Tree *tree, int level)
{
    if (tree == NULL)
        return;

    print_tree(tree->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%c\n", tree->data);

    print_tree(tree->left, level + 1);
}

void preorder(Tree *tree)
{
    Tree *stack[100];
    int top = -1;

    if (tree != NULL)
        stack[++top] = tree;

    while (top >= 0) {
        Tree *node = stack[top--];

        printf("%c ", node->data);

        if (node->right != NULL)
            stack[++top] = node->right;

        if (node->left != NULL)
            stack[++top] = node->left;
    }

    printf("\n");
}

void inorder(Tree *tree)
{
    Tree *stack[100];
    int top = -1;
    Tree *node = tree;

    while (node != NULL || top >= 0) {
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }

        node = stack[top--];
        printf("%c ", node->data);
        node = node->right;
    }

    printf("\n");
}

void postorder(Tree *tree)
{
    Tree *stack[100];
    int top = -1;
    Tree *node = tree;
    Tree *last = NULL;

    while (node != NULL || top >= 0) {
        if (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }
        else {
            node = stack[top];

            if (node->right != NULL && last != node->right)
                node = node->right;
            else {
                printf("%c ", node->data);
                last = node;
                top--;
                node = NULL;
            }
        }
    }

    printf("\n");
}

int main()
{
    char input[200];
    char *p;
    Tree *tree;

    printf("Input: ");
    scanf("%199s", input);

    p = input;
    tree = make_tree(&p);

    if (tree == NULL || *p != '\0') {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    printf("\nTree:\n");
    print_tree(tree, 0);

    printf("\nPreorder : ");
    preorder(tree);

    printf("Inorder  : ");
    inorder(tree);

    printf("Postorder : ");
    postorder(tree);

    return 0;
}
