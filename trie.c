/*spell checking, sentence completion*/
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
void traverse(char* pre,node* root,int n);
char* changeToLowerCase(char* a);
void next(node* root);

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
   char ch, *file_name;
   FILE *fp;
   file_name = "Words.txt";
   fp = fopen(file_name,"r"); // read mode
   node* root = malloc(sizeof(node));	
   char word[50];int j = 0;
   for(j=49;j>=0;j--)
		word[j] = '\0';
   j = 0;
   while( ( ch = fgetc(fp) ) != EOF ){
//	  printf("Inside loop ch: %c %d\n",ch,ch=='\n');
	  if(ch == '\n'){
//		printf("word: %s\n",word);
//		printf("letter at 0: %c",word[0]);
		insert(changeToLowerCase(word),root);
		for(;j>=0;j--){
			word[j] = '\0';
		}
		j = 0;
	  }
	  else 
	  	word[j++] = ch;
   }
	next(root);
	fclose(fp);
	return 0;
}

void next(node* root){
	printf("Enter word:");
	char* w = malloc(sizeof(char)*50);int i = 0;
	scanf("%s",w);
	for(i=0;w[i]!='\0';i++){
		if(root->r[w[i]-97])	root = root->r[w[i]-97];
		else return;
	}
//	String words[];
	traverse(w,root,0);
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
void traverse(char* pre,node* root,int n){
//	push(root->a);
	if(root->end){
		printf("%s%s\n",pre,stack);
		n++; 
//		if(n>5)	return;	
	}
	if(n<5){
	int i;
	for(i=0;i<SIZE;i++){
		if(root->r[i]){
			push(root->r[i]->a);
			traverse(pre,root->r[i],n);
		}
	}
	}
	pop();	//Count isnt done 
//	printf("Stack contents: %s \n",stack);
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
