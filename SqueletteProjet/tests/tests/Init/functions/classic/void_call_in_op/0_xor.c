int y(int b) {
    return 7;
}

void z(int a) { int b = 4; }

int main() {
    int a = 5;
    int f = y(a) ^5 ^z(a);
    char d = 2;
    return d;
}