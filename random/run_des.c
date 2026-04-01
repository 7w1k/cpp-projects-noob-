#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "des.h"
#define CMD_GEN_KEY "-g"
#define CMD_ENCRYPT "-e"
#define CMD_DECRYPT "-d"
#define DES_BLOCK_SIZE 8

FILE *key_fp = NULL;
FILE *input_fp = NULL;
FILE *output_fp = NULL;

int main(int argc, char *argv[]) {
    clock_t start, end;
    double elapsed_time;
    unsigned long file_size;
    unsigned long total_blocks;
    unsigned long block_counter = 0;
    unsigned short padding;
    if(argc < 2) {
        printf("Usage: run_des [ -g | -e | -d ]\n");
        return 1;
    } if(strcmp(argv[1], CMD_GEN_KEY) == 0) {
        if(argc != 3) {
            printf("Usage: run_des -g keyfile.key\n");
            return 1;
        } key_fp = fopen(argv[2], "wb");
        if(!key_fp) {
            printf("Error: Cannot create key file.\n");
            return 1;
        } srand((unsigned int)time(NULL));
        unsigned char key[DES_BLOCK_SIZE];
        generate_key(key);
        fwrite(key, 1, DES_BLOCK_SIZE, key_fp);
        fclose(key_fp);
        printf("Key generated successfully.\n");
        return 0;
    } if(strcmp(argv[1], CMD_ENCRYPT) == 0 || strcmp(argv[1], CMD_DECRYPT) == 0) {
        if(argc != 5) {
            printf("Usage: run_des [-e|-d] keyfile inputfile outputfile\n");
            return 1;
        } key_fp = fopen(argv[2], "rb");
        if(!key_fp) { 
            printf("Error: Cannot open key file.\n");
            return 1;
        } unsigned char des_key[DES_BLOCK_SIZE];
        if(fread(des_key, 1, DES_BLOCK_SIZE, key_fp) != DES_BLOCK_SIZE) {
            printf("Error: Invalid key file.\n");
            fclose(key_fp);
            return 1;
        } fclose(key_fp);
        input_fp = fopen(argv[3], "rb");
        if(!input_fp) {
            printf("Error: Cannot open input file.\n");
            return 1;
        } output_fp = fopen(argv[4], "wb");
        if(!output_fp) {
            printf("Error: Cannot open output file.\n");
            fclose(input_fp);
            return 1;
        } key_set key_sets[17];
        start = clock();
        generate_sub_keys(des_key, key_sets);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        int mode;
        if(strcmp(argv[1], CMD_ENCRYPT) == 0) {
            mode = ENCRYPTION_MODE;
            printf("Starting Encryption...\n");
        } else {
            mode = DECRYPTION_MODE;
            printf("Starting Decryption...\n");
        } fseek(input_fp, 0, SEEK_END);
        file_size = ftell(input_fp);
        rewind(input_fp);
        total_blocks = file_size / DES_BLOCK_SIZE + ((file_size % DES_BLOCK_SIZE) ? 1 : 0);
        unsigned char block[DES_BLOCK_SIZE];
        unsigned char processed[DES_BLOCK_SIZE];
        start = clock();
        while(fread(block, 1, DES_BLOCK_SIZE, input_fp)) {
            block_counter++;
            if(block_counter == total_blocks) {
                if(mode == ENCRYPTION_MODE) {
                    padding = DES_BLOCK_SIZE - (file_size % DES_BLOCK_SIZE);
                    if(padding < DES_BLOCK_SIZE)
                        memset(block + DES_BLOCK_SIZE - padding, padding, padding);
                    process_message(block, processed, key_sets, mode);
                    fwrite(processed, 1, DES_BLOCK_SIZE, output_fp);
                    if(padding == DES_BLOCK_SIZE) {
                        memset(block, padding, DES_BLOCK_SIZE);
                        process_message(block, processed, key_sets, mode);
                        fwrite(processed, 1, DES_BLOCK_SIZE, output_fp);
                    }
                } else {
                    process_message(block, processed, key_sets, mode);
                    padding = processed[7];
                    if(padding < DES_BLOCK_SIZE)
                        fwrite(processed, 1, DES_BLOCK_SIZE - padding, output_fp);
                }
            } else {
                process_message(block, processed, key_sets, mode);
                fwrite(processed, 1, DES_BLOCK_SIZE, output_fp);
            } memset(block, 0, DES_BLOCK_SIZE);
        } end = clock();
        fclose(input_fp);
        fclose(output_fp);
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Processing finished.\n");
        printf("Time taken: %.4f seconds\n", elapsed_time);
        return 0;
    } printf("Invalid option. Use -g, -e, or -d\n");
    return 1;
}