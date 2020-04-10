int f(int i, int c){
    i=i+1;	
    c=c+i;
    return c;
}

int main(){
    int a=1;
    int b=3;
    b=f(a,b);
    return  b;
}
