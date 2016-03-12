#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
	char a;
	struct node* r[26];
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
		if(!(root->r[a[0]-97])){
			root->r[(a[0]-97)] = malloc(sizeof(node));
			root->r[(a[0]-97)] -> a = a[0];
		}
		insert(a+1,root->r[(a[0]-97)]);				
	}		
}
void preorder(node* root){
	if(root){
		printf("%c",root -> a);
		int i = 0;
		for(;i<26;i++){
			preorder(root -> r[i]);
		}			
	}
}
