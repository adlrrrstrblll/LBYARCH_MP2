nasm -f macho64 convert.asm -o convert.o
clang -target x86_64-apple-macos11 -c main.c -o main.o -std=c99
clang -target x86_64-apple-macos11 main.o convert.o -o grayscale
./grayscale
