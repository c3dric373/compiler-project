char f(int i, char c) {
    i = i + 1;
    return c + i;
}

int g(int j) {
    return j + 2;
}

char h(int i, char c) {
    f(i, c);
    int d = 2;
    return c + i +d  + 3;
}


int main() {
    int a = 1;
    char b = 'f';
    g(a);
    b = h(a, b);
    return b;
}
