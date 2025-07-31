nasm -f win64 convert.asm -o convert.obj
gcc -c main_big.c -o main_big.obj
gcc main_big.obj convert.obj -o main_big.exe -m64
.\main_big.exe