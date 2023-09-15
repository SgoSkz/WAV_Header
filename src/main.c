#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_bits(char data);
int n_bytes_to_int(unsigned char* data, int start, int bytes);

FILE *file;
unsigned char header[44];
long bitstore = 0;

int main(int argc, char **argv) {
    file = fopen("MoV.wav", "r");
    if (file == NULL) {
        return 1;
    }
    printf("Reading header\n");
    fread(header, 44, 1, file);
    fclose(file);
    printf("Finished reading header\n");
    printf("Printing out header data\n");

    // "RIFF"
    for (int i = 0; i < 4; i++) {
        printf("%c", header[i]);
    }
    printf("\n");

    // File size
    for (int i = 4; i < 8; i++) {
        bitstore = bitstore | (header[i] << (8 * (i - 4)));
    }
    bitstore += 8;
    printf("%ld\n", bitstore);

    // "WAVE"
    for (int i = 8; i < 12; i++) {
        printf("%c", header[i]);
    }
    printf("\n");

    // "fmt "
    for (int i = 12; i < 16; i++) {
        printf("%c", header[i]);
    }
    printf("\n");

    // Length of format data
    printf("%d\n", n_bytes_to_int(header, 17, 4));

    // Type of format
    printf("%d\n", n_bytes_to_int(header, 21, 2));

    // Number of Channels
    printf("%d\n", n_bytes_to_int(header, 23, 2));

    // Sample Rate
    printf("%d\n", n_bytes_to_int(header, 25, 4));

    // (Sample Rate * BitsPerSample * Channels) / 8
    printf("%d\n", n_bytes_to_int(header, 29, 4));

    // (BitsPerSample * Channels) / 8.1 - 8 bit mono 2 - 8 bit stereo/ 16 bit mono 4 - 16 bit stereo
    printf("%d\n", n_bytes_to_int(header, 33, 2));

    // Bits per sample
    printf("%d\n", n_bytes_to_int(header, 35, 2));

    // "data"
    for (int i = 36; i < 40; i++) {
        printf("%c", header[i]);
    }
    printf("\n");

    // File size (data)
    printf("%d\n", n_bytes_to_int(header, 41, 4));

    return 0;
}

int n_bytes_to_int(unsigned char* data, int starting, int bytes) {
    long bitstore = 0;
    for (int i = starting-1; i < starting+bytes-1; i++) {
        // Little endian LSB First?
        bitstore |= (header[i] << (8 * (i - (starting - 1))));
    }
    return bitstore;
}

void print_bits(char data) {
    char *HEX = "0123456789ABCDEF";
    printf("HEX: %c", *(HEX + (0xF & (data >> 4))));
    printf("%c\n", *(HEX + (0xF & ((data << 4) >> 4))));
    printf("int: %d\n", data);
    printf("\n");
}
