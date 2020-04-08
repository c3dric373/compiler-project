int factorielle(int valeur)
{
   if (valeur == 0)
      return 1;
   else
      return valeur * factorielle(valeur - 1);
}

int main(){
    int a=7;
    int b;
    b=factorielle(a);
    return  b;
}
