int main() {
    int a = 1;
    int b = 0;
    int d = 2;
    while (a == 1) {
        if (b == 0) {
            a = 2;
        }
        while (b < 3) {
            int c = 1;
            b = b + c;
        }
        d = b + d;
    }
    return d;
}
