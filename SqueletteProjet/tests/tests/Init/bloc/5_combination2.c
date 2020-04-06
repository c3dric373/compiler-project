int main() {
    int a = 6;
    int b = 8 | a;
    int d = 2 * a + b;
    int e, f;
    while (a <= 11) {
        if (b == 0) {
            a = a + 1;
        } else {
            b = 8 | a;
            a = 1 + a;
            e = 0;
        }
    }
    f = (a + b) * e + d + 1;
    return f;
}
