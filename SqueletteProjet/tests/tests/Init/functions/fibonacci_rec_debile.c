int fibonacci_rec_debile(int n) {
    if (n == 0) {
        return (0);
    }
    if (n == 1) {
        return (1);
    }
    return(fibonacci_rec_debile(n-1)+fibonacci_rec_debile(n-2));
}

int main() {
    int a = 7;
    int b;
    b = fibonacci_rec_debile(a);
    return b;
}

