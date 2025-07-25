nasm -f win64 convert.asm -o convert.obj
gcc -std=c99 -c compare_performance.c -o compare_performance.obj
gcc compare_performance.obj convert.obj -o compare.exe -m64
.\compare.exe