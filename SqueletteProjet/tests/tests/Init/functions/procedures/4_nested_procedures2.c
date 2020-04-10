void f(int i, char c){
    i=i+1;	
    c=c+i;
}

void g(int j){
    j=j+2;
}

void h(int i, char c){
    f(i,c);	
    c=c+i+3;
}



int main(){
    int a=1;
    char b='f';
    h(a,b);
    return  b;
}
