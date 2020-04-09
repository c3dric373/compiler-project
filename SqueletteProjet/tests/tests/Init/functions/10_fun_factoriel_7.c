int factorielle(int a, char b, char c, int d, int e, int pp, int valeur )
{
   if (valeur == 0){
      return 1;
   }
   else{
      int nextval=valeur - 1;
      return valeur * factorielle(nextval,b,c,d,e,pp,nextval);
   }
}

int main(){
    int a=7;
    int b;
    char e='e';
    b=factorielle(a,e,e,a,a,a,a);
    return  b;
}
