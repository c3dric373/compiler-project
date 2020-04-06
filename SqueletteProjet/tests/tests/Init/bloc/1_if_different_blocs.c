int main(){
    int a = 3;
    int c =2;
    {
        int d =3;
        {
            if(d==3){
                int f = 5;
                c = f;
            }
        }
    }
    return c;
}