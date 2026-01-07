#include <iostream>
#include <cstring>
#include "AVL.h"

using namespace std;

//create node for BST
struct node * create_node(char *str)
{
	char *temp_str = (char*)malloc(strlen(str)+1);
	strcpy(temp_str,str);
	
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->data=temp_str;
	temp->freq = 1;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;
	temp->height=0;
  return temp;
}

void print_ancestors(struct node* temp){
	while(temp){
		printf("%s\t",temp->data);
		temp=temp->parent;
	}
	printf("\n");
}
void update_ht_ancestors(struct node* temp){

	while(temp){
		if(temp->left && temp->right){
			printf("left,right non NULL\n");
			temp->height = max(temp->left->height,temp->right->height)+1;
		}
		else if(!temp->left){
				printf("left is NULL\n");
				temp->height = temp->right->height+1;
			}
			 else{
			printf("right is NULL\n");
				temp->height = temp->left->height+1;
			}
		temp=temp->parent;
	}
}

int balance(struct node *temp){
	int left_ht=0,right_ht=0;
	if(temp==NULL)
		return -1;
	left_ht = height(temp->left);
	right_ht = height(temp->right);
	return left_ht-right_ht;
}

int left_rotate(struct node** root,struct node* x){
	struct node*y=NULL;
	int left_ht=0,right_ht=0;
	y = x->right;
	x->right = y->left;
	if(y->left!=NULL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		*root=y;
	else if(x==x->parent->left)
			x->parent->left=y;
		else
			x->parent->right = y;
	y->left = x;
	x->parent = y;
	//x->height = max(height(x->left),height(x->right)+1;
	//y->height = max(height(y->left),height(y->right)+1;
	left_ht = height(x->left);
	right_ht = height(x->right);
	x->height = max(left_ht,right_ht)+1;
	left_ht = height(y->left);
	right_ht = height(y->right);
	y->height = max(left_ht,right_ht)+1;
}

int right_rotate(struct node** root,struct node* x){
	struct node*y=NULL;
	int left_ht=0,right_ht=0;
	y = x->left;
	x->left = y->right;
	if(y->right!=NULL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		*root=y;
	else if(x==x->parent->left)
			x->parent->left=y;
		else
			x->parent->right = y;
	y->right = x;
	x->parent = y;
	//x->height = max(height(x->left),height(x->right)+1;
	//y->height = max(height(y->left),height(y->right)+1;
	left_ht = height(x->left);
	right_ht = height(x->right);
	x->height = max(left_ht,right_ht)+1;
	left_ht = height(y->left);
	right_ht = height(y->right);
	y->height = max(left_ht,right_ht)+1;
}
//Insert node for BST
void insert_bst(struct node**root, char *str)
{
	//printf("inserting %s\n",str);
	struct node *temp = create_node(str);
	struct node *x=NULL,*y=NULL,*z=NULL;
	int balance_fact=0;
	int left_ht=0,right_ht=0;
	struct node *ptr=NULL;
	struct node *prev=NULL;
	int flag = 0;
	if(*root==NULL)
	{
		*root=temp;
		return;
	}
	else
	{
		ptr=*root;
		while(ptr!=NULL && flag != 1)
		{
			prev = ptr;
			if(strcmp(str,ptr->data)<0)
			{
				//printf("%s traversing to left of %s\n",str,ptr->data);
				ptr=ptr->left;
				
			}
			else
				if(strcmp(str,ptr->data)>0)
				{
				//printf("%s traversing to right of %s\n",str,ptr->data);
					ptr=ptr->right;
				}
				else
					if(strcmp(str,ptr->data)==0)
					{
						flag=1;
						ptr->freq++;
					}
		}
		if( flag==0) {
			if(strcmp(str,prev->data)<0)
			{
				//printf("%s is being set at left of %s\n",temp->data, prev->data);
				fflush(stdout);
				prev->left=temp;
				temp->parent=prev;
			}
			else
			{
				//printf("%s is being set at right of %s\n",temp->data,prev->data);
				fflush(stdout);
				prev->right=temp;
				temp->parent=prev;
			}
			//print_ancestors(temp);
			//update_ht_ancestors(temp->parent);
			y=prev;
			z=temp;
			/*if(temp->parent!=NULL)
				if(temp->parent->parent!=NULL){
					x = temp->parent->parent;
					y = temp->parent;
				}*/
			while(y!=NULL){
				left_ht= height(y->left);
				right_ht=height(y->right);
				y->height = 1+max(left_ht,right_ht);
				//printf("y: Height updated for %s, height is %d\n",y->data,y->height);
				x = y->parent;
				if(x!=NULL){
					//printf("x: is %s, height is %d\n",x->data,x->height);
					balance_fact=0;
					balance_fact = balance(x);
				//	printf("balance is %d\n",balance_fact);
				}//else
				//	printf("grandparent is NULL\n");
				if(balance_fact <=-2 || balance_fact >=2){
					if(y==x->left){
						if(z==x->left->left){
				//			printf("Right rotate\n");
							right_rotate(root,x);
						}
						else if(z==x->left->right){
				//				printf("Left-Right rotate\n");
								left_rotate(root,y);
								right_rotate(root,x);
							}
					}
					else if(y==x->right) {
						if(z==x->right->right){
				//			printf("Left rotate\n");
							left_rotate(root,x);
						}
						else if(z==x->right->left){
				//				printf("Right-Left rotate\n");
								right_rotate(root,y);
								left_rotate(root,x);
							}
					}
					break;
				}
				y=y->parent;
				z=z->parent;
				
			}
		}
	}
}

int height(struct node *root){
	int ht_left=0,ht_right=0;
	if(root==NULL)
		return -1;
	return root->height;
/*	if(!root->left && !root->right)
		return 0;
	ht_left = height(root->left);
	ht_right = height(root->right);
	if(ht_left>ht_right)
		return ht_left+1;
	else
		return ht_right+1;
*/
}

int balance_factor(struct node *root){
	int left = height(root->left);
	int right = height(root->right);
	printf("left height=%d right height=%d\n",left, right);
	return left-right;
}

int nodes(struct node *root){
	int nodes_left=0,nodes_right=0;
	if(root==NULL)
		return 0;
	if(root->left==NULL and root->right==NULL)
		return 1;
	nodes_left=nodes(root->left);
	nodes_right=nodes(root->right);
	return nodes_left+nodes_right+1;
}