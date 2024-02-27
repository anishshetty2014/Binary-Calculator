#include"binary_function.c"

list calculate(char*,list*);
list operate(list,list,char);
int precedance(char);
void postfix(char*,char*);
int operator_count(char*);

int operator_count(char expr[]){
    char c;
    int count=0;
    int i=0;
    while(expr[i]!='\0'){
        c=expr[i];
        if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^') count++;
        i++;
    }
    return count;
}

int precedance(char c){
    switch(c){
        case '(':
            return 5;
            break;
        case '+':
            return 10;
            break;
        case '-':
            return 10;
            break;
        case '*':
            return 15;
            break;
        case '%':
            return 15;
            break;
        case '/':
            return 15;
            break;
        case '^':
            return 20;
            break;
    }
    return 0;
}

void postfix(char infix[],char postfix[]){
    int i=0;
    int j=0;
    char c;
    stack s;
    init_stack(&s);
    while(infix[i]!='\0'){
        c=infix[i];
        if(isdigit(c)){
            postfix[j++]=c;
            if(!isdigit(infix[i+1])){
                postfix[j++]=' ';
            }
        }
        else if(c=='('){
            push(&s,'(');
        }
        else if(c==')'){
            while(!is_Empty(s) && peek(s)!='('){
                postfix[j++]=pop(&s);
                postfix[j++]=' ';
            }
            if(peek(s)=='(') pop(&s);
        }
        else{
            if( c == '+' || c =='-' || c == '*'|| c == '/' || c=='^' || c=='%'){
                if(is_Empty(s)) push(&s,c);
                else{
                    while(precedance(peek(s))>=precedance(c) && !is_Empty(s)){
                        postfix[j++]=pop(&s);
                        postfix[j++]=' ';
                    }
                    push(&s,c);
                }
            }
            
        }
        i++;
    }
    while(!is_Empty(s)){
        postfix[j++]=pop(&s);
        postfix[j++]=' ';
    }
    return ;
}

list operate(list l1,list l2,char c){
    list temp;
    init(&temp);
    insert_h(&temp,0);
    switch(c){
        case '+':
            destroy(&temp);
            return add(l1,l2);
        case '-':
            destroy(&temp);
            return subtract(l1,l2);
        case '*':
            destroy(&temp);
            return multiply(l1,l2);
        case '/':
            destroy(&temp);
            return divide(l1,l2);
        case '^':
            destroy(&temp);
            return exponent(l1,l2);
        case '%':
            destroy(&temp);
            return modulus(l1,l2);
    }
    return temp;
}

list calculate(char e[],list array[]){
    list l1,l2;
    int i=0,number;
    int j=0;
    num n;
    init_num_stack(&n);
    while(e[i]!='\0'){
        init(&array[j]);
        if(isdigit(e[i])){
            while(isdigit(e[i])){
                number=(int)e[i]-'0';
                insert_h(&array[j],number);
                i++;
            }
            insert_h(&array[j],0);
            push_num(&n,array[j]);
            j++;
        }
        else if(e[i]=='+'||e[i]=='-'||e[i]=='*'||e[i]=='/'||e[i]=='%'||e[i]=='^'){
            init(&l1);
            init(&l2);
            l2=pop_num(&n);
            l1=pop_num(&n);
            push_num(&n,operate(l1,l2,e[i]));
            i++;
            destroy(&l1);
            destroy(&l2);
        }
        else if(e[i]==' ') i++;
        else return l1;
    }
    return pop_num(&n);
}

int main(){
    printf("BINARY CALCULATOR: \n\n");
    printf("Important Points:\n");
    printf("1. The exponent function works only for small values of power upto 500.\n");
    printf("2. Do not put a minus sign before a number like (-5+8).\n");
    printf("3. Division gives result in Integer form.\n");
    printf("4. All operations and results are in Integer Form.\n");
    printf("5. Dont use non-mathematical symbols it will print nothing.\n\n");
    char infix[100];
    char expr[100];
    printf("Enter the expression: ");
    scanf("%s",infix);
    postfix(infix,expr);
    list array[operator_count(expr)];
    list result;
    init(&result);
    result=calculate(expr,array);
    display(result);
    destroy(&result);
    return 0;

}