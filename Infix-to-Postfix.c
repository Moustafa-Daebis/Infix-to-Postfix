#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

#include <math.h>
/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
Item items[MAX_SIZE];
int top;
} Stack;
/*
*
*/
Stack * initialize()
{
Stack *s= malloc(sizeof(Stack));
s->top=0;
return s;
}
/*
*
*/
int isEmpty(Stack *s)
{
    if(s->top==0)
    return 1;
else
    return 0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->items[s->top-1];
}
/*
*
*/
Item pop(Stack *s)
{
        s->top--;
        return s->items[s->top] ;
    if(isEmpty(s))
    printf("STACK IS EMPTY \n");
}
/*
*
*/
void push(Stack *s, Item val)
{
       if(s->top==MAX_SIZE)
    printf("Stack is full ! \n");
else{
s->items[s->top]=val;
s->top++;
}
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
int priority(char c)
{
switch(c)
{
case '*':
case '/':
return 1;
case '+':
case '-':
return 0;
case '(':
return 3;
case '^':
return 2;
}
}
void infixToPostfix(char* infix, char* postfix)
{
strcpy(postfix,"");
Stack *s= initialize();
char delimiter[2]=" ";
char*tokin=strtok(infix,delimiter);

while(tokin!=NULL)
{

if(isdigit(tokin[0])||isdigit(tokin[1])){
strcat(postfix," ");
strcat(postfix,tokin);


}
else if(tokin[0]==')')
{
while(!isEmpty(s)&&top(s).cData!='(')
{

char add[2];
add[0]=pop(s).cData;
add[1]='\0';
strcat(postfix," ");
strcat(postfix,add);
}
pop(s).cData;
}

else if(isEmpty(s)){

Item sign;

sign.cData=tokin[0];

push(s,sign);

}
else
{


while(!isEmpty(s) &&priority(top(s).cData)>=priority(tokin[0])&& top(s).cData!='('){

char add[2];
add[0]=pop(s).cData;
add[1]='\0';

strcat(postfix," ");
strcat(postfix,add);
}
Item sign;
    sign.cData=tokin[0];
push(s,sign);

}

tokin=strtok(NULL,delimiter);
if(tokin==NULL)break;
}
while(!isEmpty(s)){

char add[2];
add[0]=pop(s).cData;
add[1]='\0';

strcat(postfix," ");
strcat(postfix,add);
}

}


/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluate(char*x, Item num1,Item num2){// function with parameters operator and two operands to perform mathematical operations
   switch (x[0]){
    case '+': return num1.fData+num2.fData;
    case '-': return num1.fData-num2.fData;
   case '*': return num1.fData*num2.fData;
   case '/': return num1.fData/num2.fData;
   case '%': return fmod(num1.fData,num2.fData);
   case '^': return pow(num1.fData,num2.fData);
   }
}
float evaluatePostfix(char* postfix) // function to evaluate the post fix expression and get its value
{  Stack *s=initialize();// to initialize a new stack
 Item answer;
 float f;
 Item x;
 Item y1;
 Item y2;

        char *tok;
        tok=strtok(postfix," ");
       while(tok!=NULL){
      if (isdigit(tok[0])|| tok[0]=='-' &&strlen(tok)>1)// Checks if the element is a number,it is put in the stack

     {
     x.fData=atof(tok);
         push(s,x);
     }

    else{   //if the element is an operator,the first two numbers are popped and sent to evaluate function
             y2=pop(s);
            y1=pop(s);

    answer.fData=evaluate(tok,y1,y2);
    push(s,answer);

   }
    tok=strtok(NULL," ");
   }

answer=pop(s);
return answer.fData;
   }
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main()
{
   char infixExpr[256]="" ;
   char postfixExpr[256]="";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Value: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
strcat(postfixExpr,"h");

    return 0;
}
