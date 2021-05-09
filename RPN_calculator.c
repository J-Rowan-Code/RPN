
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node{
	int data;
	Node *next;
};

class Stack {
	private:
		Node *lst_ptr;
	public:
		Stack();
		~Stack();
		void Push(int num);
		void Pop();
		int Top();
		bool isEmpty();
};


int main(int argc, char **argv){
	Stack RPN;
	int result, op1, op2, num, opcnt, numcnt;
	char oper;
	char expression[100], file_name[100];
	
	opcnt = 0;
	numcnt = 0;
	
	FILE *f = NULL;
	/*if(argc==2){
		strcpy(file_name, argv[1]);
	}else{
		exit(1);
	}*/
	
	/*DELETE THIS!!!*/
	strcpy(file_name, "RPN1.txt");
	
	
	f = fopen(file_name, "r");
	if(f==NULL){
		printf("Cannot open file %s. Exiting.\n", file_name);
		exit(2);
	}
	
	while(!(feof(f))){
		fgets(expression, 90, f);
		if(feof(f)){
			break;
		}
		
		if(isdigit(expression[0])){
			num=atoi(expression);
			printf("reading number %d\n", num);
			RPN.Push(num);
			numcnt++;
		}else{
			if((expression[0]=='+')||(expression[0]=='-')||(expression[0]=='*')||(expression[0]=='/')){
				sscanf(expression, "%c", &oper);
				printf("reading operator %c\n", oper);
				op2 = RPN.Top();
				RPN.Pop();
				op1 = RPN.Top();
				RPN.Pop();
				switch(oper){
					case '+': result = op1 + op2;
						break;
					case '-': result = op1 - op2;
						break;
					case '*': result = op1 * op2;
						break;
					case '/': result = op1 / op2;
						break;
				}
				
				RPN.Push(result);
				opcnt++;
			}/*else{
				printf("Operator not recognised. Closing program.\n");
				exit(4);
			}*/
		}
	}
	if(numcnt<(opcnt+1)){
		printf("too many operators\n");
		exit(6);
	}
	if(numcnt>(opcnt+1)){
		printf("too many numbers\n");
		exit(7);
	}
	printf("The result is %d\n", result);
}

Stack::Stack(){
	lst_ptr=NULL;
}

Stack::~Stack(){
	return;
}

void Stack::Push(int num){
	Node *temp;
	temp = new Node;
	temp->data = num;
	temp->next = lst_ptr;
	lst_ptr=temp;
}

void Stack::Pop(){
	Node *p;
	p = lst_ptr;
	if (lst_ptr!=NULL){
		lst_ptr = lst_ptr->next;
		delete p;
	}
}

int Stack::Top(){
	if(lst_ptr!=NULL){
		return lst_ptr->data;
	}else{
		printf("too many operators\n");
		exit(3);
	}
}

bool Stack::isEmpty(){
	if(lst_ptr == NULL){
		return true;
	}
	return false;
}
