char f(int i, char c) {
    i = i + 1;
    return c + i;
}

int g(int j) {
    return j + 2;
}

char h(int i, char c, int z, int x , int y, char l) {
    c = f(i, c);
    int d = g(c);
    return c + i + 3;
}


int main() {
    int a = 1;
    int z,x,y;
    char l = 'c';
    char b = 'f' + 2 + 'a';
    b = h(a, b,z,x,y,l);
    return b;
}
