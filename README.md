/*****************************************************************************************
AUTHOR:	KASHINATH CHILLAL
DATE:	30TH MAY 2016 (NOKIA CODE WHIZ CONTEST)
AIM:	THE PROGRAM EXTRACTS TOP 20 HIGHEST/LEAST REPEATED WORDS
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
To execute:	
	./nokia_code_whiz Input.txt Highest

	Input file name(Input.txt), Highest/Least are passed as command line arguments
Note:
	input text file is assumed to be ASCII text
*******************************************************************************************/
