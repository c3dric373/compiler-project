int f(int i, int c){
    return 2;
}

int h(int i, int c){
    c = f(i,c);
    return c + i  ;
}



int main(){
    int a=1;
    int b=0;
    b = h(a,b);
    return  b;
}
