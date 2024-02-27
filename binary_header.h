#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>

// Doubly Linked List Structure

typedef struct node{
    int d;
    struct node* next;
    struct node* prev;
}node;

typedef struct list{
    node* head;
    node* tail;
}list;

void init(list*);
int count(list);
void insert_h(list*,int);
void insert_t(list*,int);
void remove_trailling_zeros(list*);
int compare(list,list);
int is_zero(list);
void display(list);
void destroy(list*);

// Number Operation Functions

list add(list,list);
list subtract(list,list);
list multiply(list,list);
list divide(list,list);
list exponent(list,list);
list modulus(list,list);

// Stack Data Structure for PostFix

typedef struct link{
    char d;
    struct link* next;
}link;

typedef struct stack{
    link* top;
}stack;

void init_stack(stack*);
void push(stack*,char);
char pop(stack*);
char peek(stack);
int is_Empty(stack);

// Stack Data Structure for list

typedef struct cell{
    list l;
    struct cell* next;
}cell;

typedef struct num{
    cell* top;
}num;

void init_num_stack(num*);
void push_num(num*,list);
list pop_num(num*);
int is_Empty_num(num);