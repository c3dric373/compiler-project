char f(int i, char c){
    return 2;
}

char h(int i, char c){
    c = f(i,c);
   return c + i  ;
}



int main(){
    int a=1;
    char b='f';
    b = h(a,b);
    return  b;
}
