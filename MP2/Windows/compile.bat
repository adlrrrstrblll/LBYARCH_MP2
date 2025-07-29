nasm -f win64 convert.asm -o convert.obj
gcc -c main.c -o main.obj
gcc main.obj convert.obj -o main.exe -m64
.\main.exe