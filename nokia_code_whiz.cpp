/*****************************************************************************************
AUTHOR:	KASHINATH CHILLAL
DATE:	30TH MAY 2016 (NOKIA CODE WHIZ CONTEST)
AIM:	THE PROGRAM EXTRACTS TOP 20 HIGHEST REPEATED WORDS
DESCRIPTION:
	1.Data Structure used is Binary Search Tree (AVL tree) to store WORDS and FREQUENCY of occurance
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
#include "AVL.h"
#include "WordFreq.h"

using namespace std;

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
