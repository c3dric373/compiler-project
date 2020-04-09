int factorielle(int valeur) {
    if (valeur == 0) {
        return 1;
    } else {
        int b = valeur -1;
        return (valeur * factorielle(b));
    }
}

int main() {
    int a = 7;
    int b;
    b = factorielle(a);
    return b;
}
