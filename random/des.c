#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

void generate_key(unsigned char *key) {
    for(int i = 0; i < 8; i++)
        key[i] = rand() % 256;
}

void print_char_as_binary(unsigned char input) {
    for(int i = 7; i >= 0; i--)
        printf("%d", (input >> i) & 1);
}

void print_key(unsigned char *key) {
    for(int i = 0; i < 8; i++) {
        print_char_as_binary(key[i]);
        printf(" ");
    } printf("\n");
}

void shift_left(unsigned char *key_half, int shifts) {
    while(shifts--) {
        unsigned char overflow = (key_half[0] & 0x80) >> 7;
        for(int i = 0; i < 3; i++) {
            key_half[i] <<= 1;
            key_half[i] |= (key_half[i+1] & 0x80) >> 7;
        } key_half[3] <<= 1;
        key_half[3] |= overflow;
    }
}

void generate_sub_keys(unsigned char *main_key, key_set *key_sets) {
    unsigned char permuted_key[7];
    memset(permuted_key, 0, 7);
    for(int i = 0; i < 56; i++) {
        int shift_size = PC1[i] - 1;
        permuted_key[i/8] |= ((main_key[shift_size/8] >> (7 - (shift_size%8))) & 0x01) << (7 - (i%8));
    } unsigned char C[4] = {0};
    unsigned char D[4] = {0};
    memcpy(C, permuted_key, 3);
    memcpy(D, permuted_key+3, 3);
    for(int round = 1; round <= 16; round++) {
        shift_left(C, SHIFTS[round]);
        shift_left(D, SHIFTS[round]);
        unsigned char CD[7];
        memset(CD, 0, 7);
        memcpy(CD, C, 3);
        memcpy(CD+3, D, 3);
        memset(key_sets[round].k, 0, 8);
        for(int j = 0; j < 48; j++) {
            int shift_size = PC2[j] - 1;
            key_sets[round].k[j/8] |= ((CD[shift_size/8] >> (7 - shift_size%8)) & 0x01) << (7 - j%8);
        }
    }
}

void feistel(unsigned char *R, unsigned char *subkey, unsigned char *output) {
    unsigned char expanded[6];
    memset(expanded,0,6);
    for(int i = 0; i < 48; i++) {
        int bit = E[i] - 1;
        expanded[i/8] |= ((R[bit/8] >> (7 - bit%8)) & 0x01) << (7 - i%8);
    } for(int i = 0; i < 6; i++)
        expanded[i] ^= subkey[i];
    unsigned char sbox_output[4];
    memset(sbox_output,0,4);
    for(int i = 0; i < 8; i++) {
        int row = ((expanded[i/6] >> (7 - (i*6)%8)) & 0x02) | ((expanded[i/6] >> (7 - (i*6+5)%8)) & 0x01);
        int col = (expanded[i/6] >> (7 - ((i*6+1)%8))) & 0x0F;
        int val = S[i][row][col];
        sbox_output[i/2] |= val << (4*(1 - i%2));
    } for(int i = 0; i < 32; i++) {
        int bit = P[i] - 1;
        output[i/8] |=
            ((sbox_output[bit/8] >> (7 - bit%8)) & 0x01)
            << (7 - i%8);
    }
}

void process_message(unsigned char *message, unsigned char *processed, key_set *key_sets, int mode) {
    unsigned char permuted[8];
    memset(permuted,0,8);
    for(int i = 0; i < 64; i++) {
        int bit = IP[i] - 1;
        permuted[i/8] |= ((message[bit/8] >> (7 - bit%8)) & 0x01) << (7 - i%8);
    } unsigned char L[4], R[4];
    memcpy(L, permuted,4);
    memcpy(R, permuted+4,4);
    for(int round = 1; round <= 16; round++) {
        unsigned char temp_R[4];
        memcpy(temp_R,R,4);
        unsigned char f_output[4];
        memset(f_output,0,4);
        int key_index = (mode == ENCRYPTION_MODE) ? round : (17-round);
        feistel(R, key_sets[key_index].k, f_output);
        for(int i = 0; i < 4; i++)
            R[i] = L[i] ^ f_output[i];
        memcpy(L,temp_R,4);
    } unsigned char pre_output[8];
    memcpy(pre_output,R,4);
    memcpy(pre_output+4,L,4);
    memset(processed,0,8);
    for(int i = 0; i < 64; i++) {
        int bit = FP[i] - 1;
        processed[i/8] |= ((pre_output[bit/8] >> (7 - bit%8)) & 0x01) << (7 - i%8);
    }
}