int somme(int valeur){
    if(valeur!=0){
        int a = valeur-1;
        return (valeur + somme(a));
    }
    else{
        return valeur;
    }
}

int main() {
    int a = 8;
    int b;
    b = somme(a);
    return b;
}
