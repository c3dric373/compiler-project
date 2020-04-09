int fibonacci_iter_tab() {
    int t[14];
    int i;

    t[0] = 0;
    t[1] = 1;

    for (i = 2; i <= 13; i++)
    {
        t[i] = t[i-1] + t[i-2];
    }

    return t[13];
}

int main() {
    int b = fibonacci_rec_debile();
    return b;
}//
// Created by Roxane on 09/04/2020.
//

