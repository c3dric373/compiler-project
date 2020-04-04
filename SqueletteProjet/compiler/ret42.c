int main() {
    int a = 3;
    int c = 2 > 3;
    {
        int d = a + c;
        {
            if (d == 4) {
                int f = 5;
                c = f - 1;
            } else {
                int f = 6;
                while (f > 1) {
                    int z = 2 - 1;
                    c = c + z + d;
                    f = f * 2;
                    d = 1;
                }

            }
        }
    }
    return c;
}