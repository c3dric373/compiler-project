void f(int i, char c){
    i=i+1;	
    c=c+i;
}

void g(int j){
    j=j+2;
}



int main(){
    int a=1;
    char b='f';
    f(g(a),b);
    return  b;
}
