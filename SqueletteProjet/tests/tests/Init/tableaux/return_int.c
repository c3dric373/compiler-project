 
int main(){
    int a[3];
    a[0]='b';
    a[1]=2+a[0];
    a[2]=2*a[0]+12*a[1];
    return a[2]+a[1]-a[0]+(a[1]+a[0]);
}
