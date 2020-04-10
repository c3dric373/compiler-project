int main(){
    int a = 3;
    int c =2;
    {
        int d =3;
        {
            if(d==4){
                int f = 5;
                c = f;
            }else{
                int f = 3;
                while(f>1){
                    c = c + d ;
                    f = f-1;
                }

            }
        }
    }
    return c;
}