int u(int valeur){
    if(valeur==0){
        return 2;
    }
    else{
        int a = valeur-1;
        int resultat = 3 * v(a) + 2 * u(a);
        return resultat;
    }
}

int v(int valeur){
    if(valeur==0){
        return 1;
    }
    else{
        int a = valeur-1;
        int resultat = 2 * u(a) + 5 * v(a);
        return resultat;
    }
}

int main() {
    int a = 8;
    int b;
    b = v(a);
    return b;
}