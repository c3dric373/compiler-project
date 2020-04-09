#include<iostream>
#include<string>
#include <regex>

using namespace std;

int main() {

    string var = "first second third forth";

    const std::regex r("movl (%eax), (-[d]*\\(%rbp\\))*");
    smatch sm;

    if (regex_search(var, sm, r)) {
        for (int i = 1; i < sm.size(); i++) {
            cout << sm[i] << endl;
        }
    }
    std::string prog = " movl -8(%rbp) , %eax\n"
                       "  10     addl -13(%rbp), %eax # i + !tmp13\n"
                       "  11     movl %eax, -17(%rbp)\n"
                       "  12     movl -17(%rbp), %eax\n"
                       "  13     movl %eax , -8(%rbp) # i\n"
                       "  14     movl -9(%rbp) , %eax\n"
                       "  15     addl -8(%rbp), %eax # c + i\n"
                       "  16     movl %eax, -21(%rbp)\n"
                       "  17     movl -21(%rbp), %eax\n"
                       "  18     addq $21, %rsp\n"
                       "  19     popq %rbp\n"
                       "  20     ret";
    (regex_search(prog, sm, r));
    cout << sm << endl;
    return 1;
}