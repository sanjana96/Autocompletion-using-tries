/*spell checking, sentence completion*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <locale.h>
#define SIZE 128
#define LASCI 97	//lowerASCII	
#define MAXL 10
typedef struct node{
	char* a;
	struct node* r[SIZE];
	bool end;
}node;
char* stack[100];	
int top = -1;
void insert(char* a,node* root);
void traverse(char* pre,node* root,int n);
//char* changeToLowerCase(char* a);
void next(node* root);
char* substringThree(char* a,int off);

//Stack functions
char* pop(){	
	return stack[top--];
}
void push(char* a){
	stack[++top] = a;
	stack[top+1] = "";
}
bool isEmpty(){
	return top==-1;
}

int main(){
   char ch, *file_name;
   FILE *fp;
   file_name = "kannadaWords.txt";
   fp = fopen(file_name,"r"); // read mode
   node* root = malloc(sizeof(node));	
   char word[100];int j = 0;
   for(j=99;j>=0;j--)	word[j] = '\0';
   j = 0;
   while( fscanf(fp, "%100s", word) == 1)
		insert(word,root);
	next(root);
	fclose(fp);
	return 0;
}

void next(node* root){
	printf("Enter word: ");
	char* w = malloc(sizeof(char)*50);int i = 0;
	scanf("%s",w);
	char* b = substringThree(w,i);
	for(;strcmp(b,"a")!=0;i+=3,b=substringThree(w,i)){
		if(root->r[strcmp(b,"\u0c80")])	root = root->r[strcmp(b,"\u0c80")];
		else return;
	}
	traverse(w,root,0);
}

void insert(char* a,node* root){
	int len = strlen(a);
	if(len>0){
		int t = strcmp(a,"\u0c80");
		if(!(root->r[t])){
			root->r[t] = malloc(sizeof(node));
			root->r[t] -> a = substringThree(a,0);
		}
		if(len == 3){
			root->r[t]->end = true;	
		}
		insert(a+3,root->r[t]);				
	}		
}

void traverse(char* pre,node* root,int n){
//	push(root->a);
	if(root->end){
		printf("%s",pre);
		int i = 0;
		for(i=0;i<=top;i++)		printf("%s",stack[i]);
		printf("\n");
		n++; 
//		if(n>5)	return;	
	}
//	if(n<5){
	int i;
	for(i=0;i<SIZE;i++){
		if(root->r[i]){
//			printf("%s",root->r[i]->a);
			push(root->r[i]->a);
			traverse(pre,root->r[i],n);
		}
	}
//	}
	pop();	//Count isnt done 
//	printf("Stack contents: %s \n",stack);
}


char* substringThree(char* a,int off){
//	printf("length of string : %d %s\n",strlen(a),a);
	char* b = malloc(sizeof(char)*4);
	if(strlen(a)-off<3){
		b[0] = 'a';
//		printf("YES was less than 3   %s\n",b);
		return b;
	}
	int i = 0;int j = off;
	for(i =0;i<3;i++,j++){
		b[i] = a[j];
	}
	b[i] = '\0';
	return b;
}

int toNumber(char* a){
		
}
//Converts the string to lowerCase, Terminates if the letter is not in a-z or A-Z
//Eg: A's - Taken as A
/*char* changeToLowerCase(char* a){
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
}*/
