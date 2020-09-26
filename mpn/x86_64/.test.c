
        #include <stdint.h>
        #include <stdio.h>
        int main() {
            int64_t x, y;
            asm(".align 4\nx:\n\t" "jmp y\n\t"
                ".align 4\ny:\n\t" "leaq x(%%rip), %0\n\t" "leaq y(%%rip), %1"
                : "=r"(x), "=r"(y) : : );
            printf("%ld", y - x);
            return 0;
        }