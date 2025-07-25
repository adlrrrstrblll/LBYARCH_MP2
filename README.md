# Grayscale Image Converter (C + x86-64 Assembly)

This project converts an integer-based grayscale image (0–255) into a single-precision float-based grayscale image (0.0–1.0) using SIMD scalar instructions in x86-64 Assembly. It demonstrates C-to-Assembly function calling and data type conversion.

---

## 🔧 How to Run the Code

Run the following commands in your terminal or command prompt:

```bash
nasm -f win64 convert.asm -o convert.obj
gcc -c main.c -o main.obj -m64 -std=c99
gcc main.obj convert.obj -o grayscale.exe -m64
grayscale.exe
