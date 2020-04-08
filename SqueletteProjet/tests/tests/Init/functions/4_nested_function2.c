char f(int i, char c) {
    i = i + 1;
    return c + i;
}

int g(int j) {
    return j + 2;
}

char h(int i, char c) {
    c = f(i, c);
    return c + i + 3;
}


int main() {
    int a = 1;
    char b = 'f';
    b = h(a, b);
    return b;
}
