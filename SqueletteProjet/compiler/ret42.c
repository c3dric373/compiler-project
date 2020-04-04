int main() {
    int a = 3;
    int c = 2;
    {
        int d = 1;
        {
            if (d == 4) {
                int f = 5;
                c = f;
            } else {
                int f = 6;
                while (f > 1) {
                    int z = 2;
                    f = f - 1;
                    z = 2 +d;
                }
            }
        }
    }
    return c;
}