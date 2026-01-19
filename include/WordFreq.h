#include <iostream>
#include <cstring>
#include "AVL.h"
#define NUM_TOP_ELEMS 20
#define max(a,b) (a>b?a:b)

//highest frequency array element
struct high_freq{
 char *data;
 int freq;
};

void insert_hf(struct node *ptr,struct high_freq arr[],int order);
void extract_elem(struct node*ptr,struct high_freq arr[],int order);
void initialize_arr(struct high_freq arr[]);