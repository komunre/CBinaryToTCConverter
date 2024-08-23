#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void print_usage() {
    printf("cbinarytotccoverter [input_file] [bit_count]\n");
}

unsigned char* hexset = "0123456789ABCDEF";

void print_hex(unsigned char* buffer, __uint32_t bytesCount) {
    printf("0x");
    for (__uint32_t i = 0; i < bytesCount; i++) {
        __uint32_t f = buffer[i] / 16;
        __uint32_t l = buffer[i] - f*16;
        __uint32_t fh = hexset[f];
        __uint32_t lh = hexset[l];
        putc(fh, stdout);
        putc(lh, stdout);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage();
        return 0;
    }

    if (argc < 3) {
        printf("No bit count specified!\n");
        return 0;
    }

    __uint32_t bytesPerInstruction = 1;
    __uint32_t bitsCount = 0;
    sscanf(argv[2], "%d", &bitsCount);
    switch (bitsCount) {
        case 8:
            bytesPerInstruction = 1;
            break;
        case 16:
            bytesPerInstruction = 2;
            break;
        case 32:
            bytesPerInstruction = 4;
            break;
        case 64:
            bytesPerInstruction = 8;
            break;
        case 128:
            bytesPerInstruction = 16;
            break;
        default:
            printf("Unsupported bit count");
            return 1;
    }
    
    FILE* input = fopen(argv[1], "rb");

    //printf("Starting conversion.\n");

    unsigned char* buffer = (char*)malloc(bytesPerInstruction);

    while (fread(buffer, 1, bytesPerInstruction, input) != NULL) {
        switch (bytesPerInstruction) {
            case 1:
                print_hex(buffer, 1);
                break;
            case 2:
                print_hex(buffer, 2);
                break;
            case 4:
                print_hex(buffer, 4);
                break;
            case 8:
                print_hex(buffer, 8);
                break;
            case 16:
                print_hex(buffer, 16);
                break;
        }
    }

    fclose(input);
}