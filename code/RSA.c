#include "RSA.h"

/***************************************************************
 --------------  Partie arithmétique, purement RSA  ------------
 ***************************************************************
* - fonction de chiffrement d'un bloc (étant donné clé publique)
* - fonction de déchiffrement d'un bloc (étant donné clé privée)
* - génération d'un système de clés
*/

uint32_t cypher(uint32_t block, public_key key){

    return 0;
}


uint32_t decypher(uint32_t block, RSA_key key){

    return 0;
}

RSA_key gen_key(int k_p, int k_q, float eps){

    RSA_key key = {0};
    return key;
}

void cypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, public_key key){

}

void decypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, RSA_key key){

}


/***************************************************************
 --------------       Chiffrement d'un fichier      ------------
 ***************************************************************
 */

uint8_t* file_to_bytes(char* file_name, size_t* nb_bytes){

    return NULL;  
}

uint32_t* bytes_to_blocks(uint8_t* bytes_seq, size_t nb_bytes, size_t* nb_blocks){

    return NULL;     
}

uint32_t* cypher_file(char* file_name, size_t* nb_blocks, public_key key){

    return NULL;  
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

    return NULL;  
}