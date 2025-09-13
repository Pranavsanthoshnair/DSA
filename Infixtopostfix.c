#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
char stack[MAX]; int top = -1;
void push(char c){ if(top>=MAX-1)exit(1); stack[++top]=c; }
char pop(){ if(top==-1)exit(1); return stack[top--]; }
int precedence(char op){ return op=='+'||op=='-'?1:op=='*'||op=='/'?2:op=='^'?3:0; }
int isOp(char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'; }
int isVar(char c){ return isalpha(c); }
void infixToPostfix(const char*in,char*out){
    int i=0,k=0; top=-1;
    while(in[i]){
        char c=in[i];
        if(isspace(c)){i++;continue;}
        if(isdigit(c)||c=='.'){
            while(isdigit(in[i])||in[i]=='.')out[k++]=in[i++];
            out[k++]=' ';
        }else if(isVar(c)){ out[k++]=c; out[k++]=' '; i++; }
        else if(c=='('){ push(c); i++; }
        else if(c==')'){
            while(top!=-1&&stack[top]!='(') out[k++]=pop(),out[k++]=' ';
            if(top==-1)exit(1); pop(); i++;
        }else if(isOp(c)){
            if(c=='-'&&(i==0||in[i-1]=='('||isOp(in[i-1]))){
                out[k++]='0'; out[k++]=' '; push('-'); i++; continue;
            }
            while(top!=-1&&stack[top]!='('){
                char t=stack[top]; int pt=precedence(t),pc=precedence(c);
                if(pt>pc||(pt==pc&&c!='^')) out[k++]=pop(),out[k++]=' ';
                else break;
            }
            push(c); i++;
        }else exit(1);
    }
    while(top!=-1){ if(stack[top]=='(')exit(1); out[k++]=pop(),out[k++]=' '; }
    out[k]=0;
}
float power(float b,int e){ float r=1; int n=e<0?-e:e; for(int i=0;i<n;i++)r*=b; return e<0?1.0f/r:r; }
int containsVar(const char*s){ while(*s) if(isVar(*s++)) return 1; return 0; }
float evaluatePostfix(const char*p){
    float st[MAX]; int t=-1; char buf[32]; int i=0,j;
    while(p[i]){
        if(isspace(p[i])){i++;continue;}
        if(isdigit(p[i])||p[i]=='.'||(p[i]=='-'&&(isdigit(p[i+1])||p[i+1]=='.'))){
            j=0; if(p[i]=='-')buf[j++]=p[i++]; 
            while(isdigit(p[i])||p[i]=='.')buf[j++]=p[i++]; buf[j]=0;
            st[++t]=atof(buf);
        }else if(isOp(p[i])){
            if(t<1)exit(1);
            float b=st[t--],a=st[t--];
            switch(p[i]){
                case '+':st[++t]=a+b;break;
                case '-':st[++t]=a-b;break;
                case '*':st[++t]=a*b;break;
                case '/':if(b==0)exit(1);st[++t]=a/b;break;
                case '^':if(b==(int)b)st[++t]=power(a,(int)b);else exit(1);break;
            } i++;
        }else exit(1);
    }
    if(t!=0)exit(1); return st[t];
}
int main(){
    char in[3*MAX],post[3*MAX];
    printf("Enter infix expression: ");
    if(!fgets(in,sizeof(in),stdin))return 1;
    size_t len=strlen(in); if(len&&in[len-1]=='\n')in[len-1]=0;
    infixToPostfix(in,post);
    printf("Infix  : %s\n",in);
    printf("Postfix: %s\n",post);
    if(containsVar(in)) printf("Expression contains variables, evaluation skipped.\n");
    else { float r=evaluatePostfix(post); printf("Evaluation Result: %.6f\n",r); }
    return 0;
}
