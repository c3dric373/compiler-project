int main() {
    int a = 0;
    int c = 0;
    for (int i = 0; i < 10; i = i + 1) {
        while (a > 3) {
            a = a + c;
        }
        c = c + 1;
    }
    return a + c;
}
