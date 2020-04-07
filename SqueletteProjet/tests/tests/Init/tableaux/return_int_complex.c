 
int main(){
    int a[3];
    a[0]='b';
    a[1]=2+a[0];
    a[2]=2*a[0]+12*a[1];
    char b='a';
    char c =22;
    return 2*(a[2]+a[1])-a[0]+(a[1]+a[0])+2*b-2*c+c+1;
}
