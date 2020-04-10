void f(int i, char c){
    i=i+1;	
    c=c+i;
}



int main(){
    int a=1;
    char b='f';
    f(a,b);
    return  b;
}
