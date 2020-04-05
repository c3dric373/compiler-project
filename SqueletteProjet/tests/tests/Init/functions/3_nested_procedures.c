char f(int i, char c){
    i=i+1;	
    c=c+i;
    return c;
}

int g(int j){
    return j+2;
}



int main(){
    int a=1;
    char b='f';
    b=f(g(a),b);
    return  b;
}
