int main() {
    int a = 3;
    int c = 2;
    {
        int d = 3;
        {
            if (d == 4) {
                int f = 5;
                c = f;
            } else {
                int f = 6;
                while (f > 1) {
                    int z = 2;
                    c = c + z +d;
                    f = f - 1;
                    d = 1;
                }

            }
        }
    }
    return c;
}