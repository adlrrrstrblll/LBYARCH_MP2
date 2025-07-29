# Grayscale Image Converter (C + x86-64 Assembly)

This project converts an integer-based grayscale image (0–255) into a single-precision float-based grayscale image (0.0–1.0) using SIMD scalar instructions in x86-64 Assembly. It demonstrates C-to-Assembly function calling and data type conversion.

---

# 🔧 How to Run the Code

Run the following commands in your terminal or command prompt:

```bash
compile.bat

```
---
# 📊 Performance Comparison: C vs Assembly

By contrasting a C implementation with x86-64 Assembly, the performance of grayscale conversion is assessed. Utilizing the clock() function, the main metric is the average execution time over a number of iterations (eg. 30).

🔁 Setup
- Input: A m×n matrix of int pixel values (0–255)
- Output: A m×n matrix of float pixel values (0.0–1.0)
- Iterations: Each stage is executed 30 times to reduce runtime noise.
- Platform: Measured by using <time.h> to measure the CPU's wall-clock time.

🧪 Measured Functions

imgCvtGrayInttoFloat(): A C function that uses a loop to convert data to grayscale:
```bash
floatPixels[i] = (float)intPixels[i] / 255.0f
```
imgCvtGrayInttoFloat():
The x86-64 Assembly implementation uses scalar SIMD instructions:
  - CVTSI2SS: Converts a 32-bit integer to a scalar single-precision float
  - DIVSS: Performs scalar float division (by 255.0f)
  - Registers like xmm0–xmm1 are used

⚠️ Can Both Execution Times Sometimes Be Zero?

In our performance test runs, both the C and Assembly versions often report average execution times of:
```bash
  C Version     : 0.00000000 seconds  
  Assembly      : 0.00000000 seconds
```
The results do not suggest that the speeds of the two implementations are the same. Rather, this finding underscores the limitations of our benchmarking setup and is expected due to the following factors:
1. 🧮 Very Small Input Size - The test image consists of only 12 pixels, arranged in a 3x4 matrix format. Given that the resolution of the clock() function typically operates in milliseconds, the completion time for each function is often too brief to be accurately measured in nanoseconds.

2. 🛠️ Modern Compiler Optimizations - The performance of hand-written Assembly for this fundamental task is nearly comparable to that of the C compiler, particularly when optimization flags are employed. This is attributable to its ability to inline the grayscale loop, minimize arithmetic overhead, and generate efficient machine instructions.

3. ⚡ CPU Caching and Pipelining - The entirety of the input and output is accommodated within the L1 cache, given the diminutive size of the dataset. Additionally, the absence of cache misses, along with the benefits of branch prediction and instruction pipelining, proves advantageous for both implementations. Consequently, execution times are significantly reduced, rendering them virtually instantaneous.

4. ⏱️ Wall-Clock Granularity Limits - The function Clock() from the <time.h> library, which tracks CPU time with limited resolution, is employed in our timing methodology. This clock's granularity is inadequate for rapid operations, which accounts for the observed zero values.

---

# 💭 Bonus Feature (Compatible in MacOS)

### Step 1: Install Dependencies

Install the required tools using Homebrew:

```bash
brew install nasm
brew install gcc
```

### Step 2: Check Terminal Architecture

Ensure your terminal is running under x86_64 architecture:

```bash
arch -x86_64 /System/Applications/Utilities/Terminal.app/Contents/MacOS/Terminal
uname -m  # Should output: x86_64
```

### Step 3: Create and Run the Compilation Script
#### 3.1) Create the shell script:

```bash
nano compile.sh
```

#### 3.2) Copy the following script content:

```bash
#!/bin/bash
nasm -f macho64 convert.asm -o convert.o
clang -target x86_64-apple-macos11 -c main.c -o main.o -std=c99
clang -target x86_64-apple-macos11 main.o convert.o -o grayscale
./grayscale
```

Save and exit 

#### 3.3) Make the script executable:

```bash
chmod +x compile.sh
```

#### 3.4) Run the script:

```bash
./compile.sh
```

---

## ⚙️ Platform-Specific Assembly Considerations

### Register Usage Differences

Both macOS and Windows can run on x86-64 CPUs, but they differ in the organization of registers for function calls:

| Argument # | macOS/Linux | Windows |
|------------|-------------|---------|
| 1          | RDI         | RCX     |
| 2          | RSI         | RDX     |
| 3          | RDX         | R8      |
| 4          | RCX         | R9      |
| 5+         | Stack       | Stack   |
| Return     | RAX         | RAX     |

### Function Naming Conventions

**macOS:** Function names in assembly require a leading underscore (e.g., `_imgCvtGrayInttoFloat`) due to conventions from older linkers like Mach-O. This is different from Windows and Linux, where function names are typically not prefixed. The underscore helps the macOS linker find the correct function during the linking phase.

**Windows:** Function names do not require a leading underscore in the assembly code.

# 👥 Authors

- **Evan Andrew J. Pinca**  
- **Adler Clarence E. Strebel**  
- **Section:** S14
