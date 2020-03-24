./ifcc $1 > ret42.s
gcc ret42.s
./a.out
echo $?
