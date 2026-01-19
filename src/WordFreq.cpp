#include <iostream>
#include <cstring>
#include "AVL.h"
#include "WordFreq.h"

using namespace std;

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