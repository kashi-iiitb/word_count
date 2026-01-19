#ifndef AVL_H
#define AVL_H

//BST node
struct node {
 char *data;
 int freq;
 struct node *left;
 struct node *right;
 struct node *parent;
 int height;
};

int height(struct node *root);
struct node * create_node(char *str);
void print_ancestors(struct node* temp);
void update_ht_ancestors(struct node* temp);
int balance(struct node *temp);
int left_rotate(struct node** root,struct node* x);
int right_rotate(struct node** root,struct node* x);
void insert_bst(struct node**root, char *str);
int balance_factor(struct node *root);
int nodes(struct node *root);

#endif