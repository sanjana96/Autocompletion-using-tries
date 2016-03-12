#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 26
#define LASCI 96	//lowerASCII
typedef struct node{
	char a;
	struct node* r[SIZE];
}node;
void insert(char* a,node* root);
void preorder(node* root);
int main(){
	node* root = malloc(sizeof(node));	
	insert("abc",root);
	insert("app",root);
	preorder(root);
}
void insert(char* a,node* root){
	int i = 0;
	int len = strlen(a);
	if(len>0){
		int t = a[0] - LASCI;
		if(!(root->r[t])){
			root->r[t] = malloc(sizeof(node));
			root->r[t] -> a = a[0];
		}
		insert(a+1,root->r[t]);				
	}		
}
void preorder(node* root){
	if(root){
		printf("%c",root -> a);
		int i = 0;
		for(;i<SIZE;i++){
			preorder(root -> r[i]);
		}			
	}
}
