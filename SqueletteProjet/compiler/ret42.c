int pair(int valeur) {
    int resultat;
    int x = valeur-2;
    if(x==0){
        return 1 ;
    }
    else {
        if (x==1){
            return 0;
        }
        else{
            resultat=pair(x);
            return resultat;
        }
    }

}

int main() {
    int a = 8;
    int b;
    b = pair(a);

    return b;
}
