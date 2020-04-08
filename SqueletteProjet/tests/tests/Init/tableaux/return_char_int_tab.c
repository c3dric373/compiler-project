 
int main(){
    char b[14];
    b[11]='a';
    b[9]=4;
    int a[3];
    a[0]='b';
    a[1]=2+a[0];
    a[2]=2*a[0]+12*b[9];
    return 2*a[1]-4*b[9]+b[11];
}
