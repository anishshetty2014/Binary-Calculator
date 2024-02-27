#include"binary_header.h"

// List Functions

void init(list* l){
    l->head=NULL;
    l->tail=NULL;
    return ;
}

int count(list l){
    if(l.head==NULL) return 0;
    int count=0;
    node* p=l.head->next;
    while(p) {
        count++;
        p=p->next;
    }
    return count;
}

void insert_h(list* l,int data){
    node* n;
    n=(node*)malloc(sizeof(node));
    if(n){
        n->d=data;
        n->prev=NULL;
        n->next=NULL;
    }
    else return;
    if(l->head==NULL){
        l->head=n;
        l->tail=n;
        return ;
    }
    l->head->prev=n;
    n->next=l->head;
    l->head=n;
    return ;
}

void insert_t(list* l,int data){
    node* n;
    n=(node*)malloc(sizeof(node));
    if(n){
        n->d=data;
        n->prev=NULL;
        n->next=NULL;
    }
    else return;
    if(l->head==NULL){
        l->head=n;
        l->tail=n;
        return ;
    }
    l->tail->next=n;
    n->prev=l->tail;
    l->tail=n;
    return ;    
}

int compare(list l1,list l2){
    if(count(l1)>count(l2)) return 1;
    else if(count(l1)<count(l2)) return -1;
    node *p=l1.tail;
    node *q=l2.tail;
    if(p==NULL && q==NULL) return 0;
    else if(p==NULL) return -1;
    else if(q==NULL) return 1;
    while(p->prev){
        if(p->d>q->d) return 1;
        else if(p->d<q->d) return -1;
        p=p->prev;
        q=q->prev;
    }
    return 0;
}

int is_zero(list l){
    if(l.head==NULL) return 0;
    node *p=l.tail;
    while(p->prev){
        if(p->d==0) p=p->prev;
        else return 0;
    }
    return 1;
}

void remove_trailling_zeros(list* l){
    if(l->head==NULL) return ;
    node* p=l->tail;
    while(p->d==0 && p->prev){
        l->tail=p->prev;
        l->tail->next=NULL;
        free(p);
        p=l->tail;
    } 
}

list add(list l1,list l2){
    int sign=0;
    if(l1.head->d==1 && l2.head->d==1) sign=1;
    else if(l1.head->d==1 || l2.head->d==1){
        if(l1.head->d==1){
            l2.head->d=1;
            return subtract(l1,l2);
        }
        else{
            l2.head->d=0;
            return subtract(l1,l2);
        }
    }
    node* p=l1.head->next;
    node* q=l2.head->next;
    list sum;
    init(&sum);
    int data;
    int carry=0;
    while(p || q){
        if(p && q){
            data=p->d+q->d+carry;
            if(data>=10){
                data-=10;
                carry=1;
            }
            else carry=0;
            insert_t(&sum,data);
            p=p->next;
            q=q->next;
        }
        else if(p){
            data=p->d+carry;
            if(data>=10){
                data-=10;
                carry=1;
            }
            else carry=0;
            insert_t(&sum,data);
            p=p->next;
        }
        else if(q){
            data=q->d+carry;
            if(data>=10){
                data-=10;
                carry=1;
            }
            else carry=0;
            insert_t(&sum,data);
            q=q->next;
        }
    }
    if(carry) insert_t(&sum,1);
    remove_trailling_zeros(&sum);
    insert_h(&sum,sign);
    return sum;
}

list subtract(list l1,list l2){
    int sign=0;
    if(l1.head->d==1 && l2.head->d==0){
        l2.head->d=1;
        return add(l1,l2);
    }
    else if(l1.head->d==0 && l2.head->d==1){
        l2.head->d=0;
        return add(l1,l2);
    }
    node *p,*q;
    list sub;
    init(&sub);
    if(compare(l1,l2)==1) {
        if(l1.head->d) sign=1;
        else sign=0;
        p=l1.head->next;
        q=l2.head->next;
        }
    else if(compare(l1,l2)==-1){
        if(l1.head->d) sign=0;
        else sign=1;
        p=l2.head->next;
        q=l1.head->next;
    }
    else{
        insert_h(&sub,0);
        insert_h(&sub,0);
        return sub;
    }
    int data;
    int borrow=0;
    while(p || q){
        if(p&&q){
            data=p->d-q->d-borrow;
            if(data<0){
                data+=10;
                borrow=1;
            }
            else borrow=0;
            insert_t(&sub,data);
            p=p->next;
            q=q->next;
        }
        else if(p){
            data=p->d-borrow;
            if(data<0){
                data+=10;
                borrow=1;
            }
            else borrow=0;
            insert_t(&sub,data);
            p=p->next;
        }
    }
    remove_trailling_zeros(&sub);
    insert_h(&sub,sign);
    return sub;
}

list multiply(list l1,list l2){
    int sign=0;
    list product,temp;
    init(&product);
    if(is_zero(l1) || is_zero(l2)){
        insert_h(&product,0);
        insert_h(&product,0);
        return product;
    }
    if(l1.head->d==1 && l2.head->d==1) sign=0;
    else if(l1.head->d==1 || l2.head->d==1) sign=1;
    insert_h(&product,0);
    node *p,*q;
    if(compare(l1,l2)>=0){
        p=l1.head->next;
        q=l2.head->next;
    }
    else{
        p=l2.head->next;
        q=l1.head->next;
    }
    int data;
    int carry=0;
    int i=0;
    while(q){
        carry=0;
        init(&temp);
        for(int k=0;k<i;k++){
            insert_h(&temp,0);
        }
        while(p){
            data=(p->d*q->d)+carry;
            if(data>=10){
                carry=data/10;
            }
            else carry=0;
            insert_t(&temp,data%10);
            p=p->next;
        }
        if(carry) insert_t(&temp,carry);
        insert_h(&temp,0);
        product=add(product,temp);
        q=q->next;
        destroy(&temp);
        i++;
        if(compare(l1,l2)>=0) p=l1.head->next;
        else p=l2.head->next;
    }
    remove_trailling_zeros(&product);
    product.head->d=sign;
    return product;
    }

list divide(list l1,list l2){
    int sign=0;
    list quotient;
    init(&quotient);
    if(is_zero(l2)){
        printf("Error: Division by Zero");
        return quotient;
    }
    if(is_zero(l1) || compare(l1,l2)==-1){
        insert_h(&quotient,0);
        insert_h(&quotient,0);
        return quotient;
    }
    if(l1.head->d==1 && l2.head->d==1) sign=0;
    else if(l1.head->d==1 || l2.head->d==1) {
        if(l1.head->d) l1.head->d=0;
        else l2.head->d=0;
        sign=1;
    }
    int num;
    list temp;
    init(&temp);
    insert_h(&temp,0);
    node* p=l1.tail;
    while(p->prev){
        num=0;
        while(compare(l2,temp)!=-1 && compare(l2,temp)!=0){
            node* nn;
            nn=(node*)malloc(sizeof(node));
            if(nn){
                nn->d=p->d;
                nn->prev=NULL;
                nn->next=NULL;
            }
            else return quotient;    
            if(temp.head->next==NULL){
                temp.head->next=nn;
                nn->prev=temp.head;
                temp.tail=nn;
            }
            else{
                nn->next=temp.head->next;
                temp.head->next->prev=nn;
                nn->prev=temp.head;
                temp.head->next=nn;
            }
            p=p->prev;
        }
        while(!is_zero(temp) && compare(temp,l2)!=-1){
            temp=subtract(temp,l2);
            num+=1;
        }
        insert_h(&quotient,num);
        remove_trailling_zeros(&temp);
    }
    destroy(&temp);
    insert_h(&quotient,sign);
    return quotient;
}

list exponent(list l1,list l2){
    list result;
    init(&result);
    if(is_zero(l1) || l2.head->d==1){
        insert_h(&result,0);
        insert_h(&result,0);
        return result;
    }
    if(is_zero(l2) || l1.head->next->d==1){
        insert_h(&result,1);
        insert_h(&result,0);
        return result;
    }
    insert_h(&result,1);
    insert_h(&result,0);
    int sign=0;
    if(l1.head->d==1) if(l2.head->next->d%2!=0) sign=1;
    list unity;
    init(&unity);
    insert_h(&unity,1);
    insert_h(&unity,0);
    while(!is_zero(l2)){
        l2=subtract(l2,unity);
        result=multiply(l1,result);
    }
    result.head->d=sign;
    return result;
}

list modulus(list l1,list l2){
    list q,remainder;
    init(&q);
    init(&remainder);
    int sign=0;
    if(l1.head->d==1 && l2.head->d==0) sign=1;
    else if(l1.head->d==0 && l2.head->d==1) sign=1;
    l1.head->d=0;
    l2.head->d=0;
    q=divide(l1,l2);
    remainder=subtract(l1,multiply(l2,q));
    remainder.head->d=sign;
    return remainder;      
}

void display(list l){
    if(l.head==NULL) return;
    if(l.head->d==1) printf("-");
    node* p=l.tail;
    while(p->prev){
        printf("%d",p->d);
        p=p->prev;
    }
    printf("\n");
    return ;
}

void destroy(list* l){
    if(l->head==NULL) return ;
    node *p=l->head,*q;
    q=p->next;
    while(q){
        free(p);
        p=q;
        q=q->next;
    }
    free(p);
    l->head=NULL;
    l->tail=NULL;
    return;
}

//Stack Functions

void init_stack(stack* s){
    s->top=NULL;
    return ;
}

int is_Empty(stack s){
    if(s.top==NULL) return 1;
    else return 0;
}

void push(stack* s,char c){
    link* n;
    n=(link*)malloc(sizeof(link));
    if(n){
        n->d=c;
        n->next=NULL;
    }
    else return;
    if(is_Empty(*s)){
        s->top=n;
        return;
    }
    n->next=s->top;
    s->top=n;
    return ;
}

char pop(stack* s){
    if(is_Empty(*s)) return CHAR_MIN;
    char d=s->top->d;
    link* p=s->top;
    s->top=p->next;
    free(p);
    return d;
}

char peek(stack s){
    if(is_Empty(s)) return CHAR_MIN;
    return s.top->d;
}

// Number Stack Functions

void init_num_stack(num* n){
    n->top=NULL;
    return ;
}

int is_Empty_num(num n){
    if(n.top==NULL) return 1;
    else return 0;
}

void push_num(num* n,list number){
    cell *nn;
    nn=(cell*)malloc(sizeof(cell));
    if(nn){
        nn->l=number;
        nn->next=NULL;
    }
    else return ;
    if(is_Empty_num(*n)){
        n->top=nn;
        return ;
    }
    nn->next=n->top;
    n->top=nn;
    return;
}

list pop_num(num* n){
    list data;
    init(&data);
    if(is_Empty_num(*n)) return data;
    data=n->top->l;
    cell* p=n->top;
    n->top=p->next;
    free(p);
    return data;
}