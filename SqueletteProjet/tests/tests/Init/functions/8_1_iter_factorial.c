int iter_fact(int valeur) {
    int res = 1;
    for (int i = 1 ; i <= valeur ; i++) {
        res = res * i;
    }
    return(res);
}

int main() {
    int a = 7;
    int b;
    b = iter_fact(a);
    return b;
}
