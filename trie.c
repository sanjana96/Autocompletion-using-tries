#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 26
#define LASCI 97	//lowerASCII	
#define MAXL 10
typedef struct node{
	char a;
	struct node* r[SIZE];
	bool end;
}node;
char stack[100];	
int top = -1;
void insert(char* a,node* root);
void traverse(node* root);
char* changeToLowerCase(char* a);

//Stack functions
char pop(){	
	return stack[top--];
}
void push(char a){
	stack[++top] = a;
	stack[top+1] = '\0';
}
bool isEmpty(){
	return top==-1;
}

int main(){
	node* root = malloc(sizeof(node));	
	char w;
	char word[100];
	while(scanf("%s", word) != EOF)
		insert(changeToLowerCase(word),root);
	while(scanf("%c",&w)!= EOF){
		root = root->r[w-97];
		traverse(root);
	}
	return 0;
}
void insert(char* a,node* root){
	int len = strlen(a);
	if(len>0){
		int t = a[0] - LASCI;
		if(!(root->r[t])){
			root->r[t] = malloc(sizeof(node));
			root->r[t] -> a = a[0];
		}
		if(len == 1){
			root->r[t]->end = true;	
		}
		insert(a+1,root->r[t]);				
	}		
	
}
void traverse(node* root){
	if(root->end)	printf("%s\n",stack);	
	int i;
	for(i=0;i<SIZE;i++){
		if(root->r[i]){
			push(root->r[i]->a);
			traverse(root->r[i]);
		}
	}
	pop();	//Count isnt done 
}

//Converts the string to lowerCase, Terminates if the letter is not in a-z or A-Z
//Eg: A's - Taken as A
char* changeToLowerCase(char* a){
	char* new = malloc(sizeof(char)*(strlen(a)+1));	
	int i;int j;
	for(i=0,j=0;i<strlen(a);i++){
		if(a[i]>=65 && a[i]<=90)		
			new[j++] = a[i]+32;
		else if(a[i]>=97 && a[i]<=122)
			new[j++] = a[i]; 
		else 
			break;
	}	
	new[j] = '\0';
	return new;
}
