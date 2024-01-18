#include "RSA.h"

/***************************************************************
 --------------  Partie arithmétique, purement RSA  ------------
 ***************************************************************
* - fonction de chiffrement d'un bloc (étant donné clé publique)
* - fonction de déchiffrement d'un bloc (étant donné clé privée)
* - génération d'un système de clés
*/

#include "RSA.h"
#include "algo.h"

uint32_t cypher(uint32_t block, public_key key){
    return fast_exp(block, key.e, key.n);
}

uint32_t decypher(uint32_t block, RSA_key key){
    return fast_exp(block, key.d, key.p);
}

RSA_key gen_key(int k_p, int k_q, float eps){
    RSA_key key;
    key.p = MR_prime(k_p, eps);
    key.q = MR_prime(k_q, eps);
    key.pub_key.n = key.p * key.q;
    uint32_t phi = (key.p - 1) * (key.q - 1);
    key.pub_key.e = 3; // choose e = 3 for simplicity
    key.d = modular_inv(key.pub_key.e, phi);
    return key;
}

void cypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, public_key key){
    for (size_t i = 0; i < nb_blocks; i++) {
        blocks_seq[i] = cypher(blocks_seq[i], key);
    }
}

void decypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, RSA_key key){
    for (size_t i = 0; i < nb_blocks; i++) {
        blocks_seq[i] = decypher(blocks_seq[i], key);
    }
}


/***************************************************************
 --------------       Chiffrement d'un fichier      ------------
 ***************************************************************
 */

uint8_t* file_to_bytes(char* file_name, size_t* nb_bytes){
    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    size_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    uint8_t* bytes_seq = malloc(file_size * sizeof(uint8_t));
    if (bytes_seq == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ssize_t read_bytes = read(fd, bytes_seq, file_size);
    if (read_bytes == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    *nb_bytes = read_bytes;
    return bytes_seq;
}

uint32_t* bytes_to_blocks(uint8_t* bytes_seq, size_t nb_bytes, size_t* nb_blocks){
    size_t nb_blocks_tmp = nb_bytes / 4;
    if (nb_bytes % 4 != 0) {
        nb_blocks_tmp++;
    }
    uint32_t* blocks_seq = malloc(nb_blocks_tmp * sizeof(uint32_t));
    if (blocks_seq == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < nb_blocks_tmp; i++) {
        blocks_seq[i] = 0;
        for (size_t j = 0; j < 4; j++) {
            if (i * 4 + j < nb_bytes) {
                blocks_seq[i] += bytes_seq[i * 4 + j] << (8 * (3 - j));
            }
        }
    }
    *nb_blocks = nb_blocks_tmp;
    return blocks_seq;
}

uint32_t* cypher_file(char* file_name, size_t* nb_blocks, public_key key){
    // Step 1: Read the file into a byte sequence
    size_t nb_bytes;
    uint8_t* bytes_seq = file_to_bytes(file_name, &nb_bytes);

    // Step 2: Convert the byte sequence into a block sequence
    uint32_t* blocks_seq = bytes_to_blocks(bytes_seq, nb_bytes, nb_blocks);

    // Step 3: Encrypt each block in the block sequence
    for (size_t i = 0; i < *nb_blocks; i++) {
        blocks_seq[i] = cypher(blocks_seq[i], key);
    }

    // Step 4: Convert the encrypted block sequence back into a byte sequence
    uint8_t* cyphered_bytes_seq = blocks_to_bytes(blocks_seq, *nb_blocks);

    // Clean up
    free(bytes_seq);

    return blocks_seq;
}

void blocks_to_file(char* file_name, uint32_t* blocks_seq, size_t nb_blocks){
}

uint8_t*  blocks_to_bytes(uint32_t* blocks_seq, size_t nb_blocks)
{
    return NULL;  
}

void bytes_to_file(char* file_name, uint8_t* bytes_seq, size_t nb_bytes){

}

uint8_t* decypher_file(char* file_name, RSA_key key, size_t* nb_bytes){
    // Step 1: Read the file into a byte sequence
    uint8_t* bytes_seq = file_to_bytes(file_name, nb_bytes);

    // Step 2: Convert the byte sequence into a block sequence
    size_t nb_blocks;
    uint32_t* blocks_seq = bytes_to_blocks(bytes_seq, *nb_bytes, &nb_blocks);

    // Step 3: Decrypt each block in the block sequence
    for (size_t i = 0; i < nb_blocks; i++) {
        blocks_seq[i] = decypher(blocks_seq[i], key);
    }

    // Step 4: Convert the decrypted block sequence back into a byte sequence
    uint8_t* decyphered_bytes_seq = blocks_to_bytes(blocks_seq, nb_blocks);

    bytes_to_file("decyphered_file", decyphered_bytes_seq, *nb_bytes);

    // Clean up
    free(bytes_seq);
    free(blocks_seq);

    return decyphered_bytes_seq;
}