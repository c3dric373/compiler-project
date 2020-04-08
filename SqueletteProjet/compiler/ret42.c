char f(int i, char c){
    i=i+1;
    c=c+i;
    return c;
}

int main(){
    int a=1;
    char b='f';
    b=f(a,b);
    return  b;
}
