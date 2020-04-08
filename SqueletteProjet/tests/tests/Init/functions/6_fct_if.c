char f(int i, char c){
    if(i == 0){
        c = 'a'
    } else{
        c = 'b'
    }
    return c;
}

int main(){
    int a=1;
    char b='f';
    b=f(a,b);
    return  b;
}
