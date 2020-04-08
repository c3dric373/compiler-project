int main(){
    int a = ! (3+2);
    int c =2;
    {
        int d =3;
        {
            int f =3;
            d= f+3;
        }
        c = 3+d;
    }
    return c;
}