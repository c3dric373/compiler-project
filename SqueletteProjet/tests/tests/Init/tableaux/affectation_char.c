 
int main(){
    char a[3];
    a[0]='a';
    a[1]='b'+a[0];
    a[2]=2*a[0]+12*a[1];
    return a[2];
}
