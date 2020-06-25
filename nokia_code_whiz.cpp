/*****************************************************************************************
AUTHOR:	KASHINATH CHILLAL
DATE:	30TH MAY 2016 (NOKIA CODE WHIZ CONTEST)
AIM:	THE PROGRAM EXTRACTS TOP 20 HIGHEST REPEATED WORDS
DESCRIPTION:
	1.Data Structure used is Binary Search Tree to store WORDS and FREQUENCY of occurance
	2.Binary Search Tree is built with every word read.
	3.If word is not present in BST,a new node is created and inserted with frequency =1
	  If word already present in BST then its frequency is incremented by 1
	4.At the end BST is traversed in inorder fashion and an array of size 20 
	  is maintained to keep count of highest frequency words.
	5.At the end contents of this array are displayed (words & corresponding frequency)
Compilation Process:
	g++ -o nokia_code_whiz nokia_code_whiz.cpp
	
	./nokia_code_whiz Input.txt Highest
	Input file name(Input.txt), Highest/Least are passed as command line arguments
Note:
	input text file is assumed to be ASCII text
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstring>
#define NUM_TOP_ELEMS 20
#define max(a,b) (a>b?a:b)

using namespace std;

//BST node
struct node {
 char *data;
 int freq;
 struct node *left;
 struct node *right;
 struct node *parent;
 int height;
};

//highest frequency array element
struct high_freq{
 char *data;
 int freq;
};

int height(struct node *root);
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
//This function extracts 20 highest or lowest occuring words from Binary Search Tree
void insert_hf(struct node *ptr,struct high_freq arr[],int order)
{
//cout << "INsert called with freq " << freq << endl;
static int maxlen=0;
int i=0;

//order= 1 for highest occuring words
if(order == 1)
{
if(maxlen < NUM_TOP_ELEMS)
{
  while((i<maxlen) && (ptr->freq < arr[i].freq))
	i++;
  if(i==maxlen)
  {
	arr[i].data = ptr->data;
	arr[i].freq = ptr->freq;
  }
  else
  {
	int j=0;
	for(j=maxlen;j>i; j--)
	{
		arr[j].data = arr[j-1].data;
		arr[j].freq = arr[j-1].freq;
	} 
	arr[j].data = ptr->data;
	arr[j].freq = ptr->freq;
  }
  maxlen++;
}
else
  if(maxlen ==NUM_TOP_ELEMS)
  {  
	   while((i<maxlen) && (ptr->freq < arr[i].freq))
		i++;
	  if(i==maxlen)
	  {
		//do nothing
	  }
	  else
	  {
		int j=0;
		for( j=maxlen-1;j>i; j--)
		{
			arr[j].data = arr[j-1].data;
			arr[j].freq = arr[j-1].freq;
		} 
		arr[j].data = ptr->data;
		arr[j].freq = ptr->freq;
	  }
	
  }
}
else
//order=2 for lowest occuring words
if(order==2)
{
if(maxlen < NUM_TOP_ELEMS)
{
  while((i<maxlen) && (ptr->freq > arr[i].freq))
	i++;
  if(i==maxlen)
  {
	arr[i].data = ptr->data;
	arr[i].freq = ptr->freq;
  }
  else
  {
	int j=0;
	for(j=maxlen;j>i; j--)
	{
		arr[j].data = arr[j-1].data;
		arr[j].freq = arr[j-1].freq;
	} 
	arr[j].data = ptr->data;
	arr[j].freq = ptr->freq;
  }
  maxlen++;
}
else
  if(maxlen ==NUM_TOP_ELEMS)
  {  
	   while((i<maxlen) && (ptr->freq > arr[i].freq))
		i++;
	  if(i==maxlen)
	  {
		//do nothing
	  }
	  else
	  {
		int j=0;
		for( j=maxlen-1;j>i; j--)
		{
			arr[j].data = arr[j-1].data;
			arr[j].freq = arr[j-1].freq;
		} 
		arr[j].data = ptr->data;
		arr[j].freq = ptr->freq;
	  }
	
  }

}
}

//inorder traversal of the binary search tree to extract highest 20 frequency elements
void extract_elem(struct node*ptr,struct high_freq arr[],int order)
{
	if(ptr==NULL)
		return;
	else
		extract_elem(ptr->left,arr,order);
		insert_hf(ptr,arr,order);
		extract_elem(ptr->right,arr,order);
}

//initialize the array used to store highest/lowest frequency words
void initialize_arr(struct high_freq arr[])
{
	for(int i=0; i<NUM_TOP_ELEMS; i++)
	{
		arr[i].data = NULL;
		arr[i].freq = 0;
	}	
}

int main(int argc, char*argv[])
{
	struct node *root=NULL;
	string str;

	//The following are delimiters and excluded from forming words
    	char delimiters[100] =  "\\/,.:;'\"-\t=+_{}[]? ~!@#$%^*()1234567890|";
	struct high_freq arr[NUM_TOP_ELEMS];
	
	initialize_arr(arr);
	
	ifstream infile;
	infile.open(argv[1]);
	if(infile.is_open())
	{
		//Read a string
		while(infile>>str)
		{
			//Extract words from string for e.g. string cross-functional will give 2 words "cross" and "functional"
			string::size_type len=str.length();
			char * temp_str = (char*)malloc(len+1);
			if(!temp_str)
			{
				perror("Failed to allocate memory!!");
				exit(1);
			}
			string::size_type j=0;
			//Convert all the characters to lower case before comparing
			for( j=0; j<len; j++)
				temp_str[j] = tolower(str[j]);
			temp_str[j] = '\0';
			char * token = (char *)malloc(len+1);
			if(!token)
			{
				perror("Failed to allocate memory!!");
				exit(1);
			}
			//Extract words seperated by delimiters
			//For every word-> insert word into binary search tree and increase its count if already present
			token = strtok(temp_str,delimiters);
			while(token!=NULL)
			{
				if(strlen(token)>1)
				{
					insert_bst(&root,token);	
				}
				//read next word from the string
				token = strtok(NULL,delimiters);
			}
		}
		printf("Balance at root = %d\n",balance_factor(root));
		//check the user option highest/lowest
		if(strcmp(argv[2], "Highest")==0)
		{	
			extract_elem(root,arr,1);
			//printf("Right choice\n");
		}
		else
			if(strcmp(argv[2], "Least")==0)
			{	
				extract_elem(root,arr,2);
				//printf("Right choice\n");
			}
		//output the words in freq_array	
		for(int k=0; k<NUM_TOP_ELEMS; k++)
			printf("%s %d\n",arr[k].data, arr[k].freq);
	}
	else
	{
		cout << "Error opening input file" <<endl;
		exit(1);
	}

	printf("Height of BST is %d\n", height(root));
	printf("No. of nodes in BST is %d\n", nodes(root));
	infile.close();
return 0;

}
