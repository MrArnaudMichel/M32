#ifndef RSA_h
#define RSA_h

#include "algo.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h> //open, ...
#include<unistd.h> //lseek()

/***********************************
* Gestion  des clés de chiffrement *
************************************/

typedef struct {
    uint32_t  n;// module public
    uint32_t  e; //exposant de chiffrement
    } public_key;

typedef struct {
    uint32_t  p;// p et q sont les facteurs premiers du module n
    uint32_t  q;
    uint32_t  d;// exposant de déchiffrement
    public_key pub_key;
    } RSA_key;

/*
* Fonction de génération d'un système de clés RSA tel que
* - le module se factorise en deux entiers p et qs'écrivant 
* respectivement avec k_p et k_q chiffres binaires
* - on demande que le produit n = p*q s'écrive avec k_p+k-q
* chiffres binaires exactement
* - eps contrôle le risque de non primalité de p et q
*/
RSA_key gen_key(int k_p, int k_q, float eps);

/**************************************
* Chiffrement/Déchiffrement des blocs *
***************************************/ 

/*
* Fonction de chiffrement d'un uint32_t, étant donné la clé publique 
*/
uint32_t cypher(uint32_t block, public_key key);
/*
* Fonction de déchiffrement d'un uint32_t, étant donné la clé privée 
*/
uint32_t decypher(uint32_t block, RSA_key key);
/*
* Fonction de chiffrement d'une suite de  nb_blocks uint32_t, 
* étant donné la clé publique 
*/
void cypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, public_key key);
/*
* Fonction de déchiffrement d'une suite de nb_blocks uint32_t, 
* étant donné la clé publique 
*/
void decypher_blocks(uint32_t* blocks_seq, size_t nb_blocks, RSA_key key);

/****************************
* Chiffrement d'un fichier  *
*****************************/ 

/*
* Fonction de chiffrement du fichier file_name au moyen de la clé key.
* La fonction renvoie l'adresse de la suite de blocs contenant le chiffré
* après avoir déterminé la taille de cette suite dans nb_blocks.
*/
uint32_t* cypher_file(char* file_name, size_t* nb_blocks, public_key key);

/*
* La fonction de chiffrement d'un fichier fait appel aux 
* deux fonctions suivantes :
*/

/*
* Lecture et copie du fichier file_name à l'adresse retournée par la fonction
* la taille du fichier est stockée dans nb_bytes
*/
uint8_t*  file_to_bytes(char* file_name, size_t* nb_bytes);

/*
* Construction des blocs de mots de code à chiffrer :
* en entrée, l'adresse bytes_seq et la taille nb_bytes
* en sortie, l'adresse retournée de la suite de blocs et leur nombre nb_blocks
*/
uint32_t* bytes_to_blocks(uint8_t* bytes_seq, size_t nb_bytes, size_t* nb_blocks);

/*
* Une fois chiffré le contenu du fichier clair, la fonction suivante recopie
* les nb_blocks blocs écrits à partir de l'adresse blocks_seq dans le fichier 
* file_name
*/
void blocks_to_file(char* file_name, uint32_t* blocks_seq, size_t nb_blocks);


/*
*void bytes_to_file(char* file_name, uint8_t* bytes_seq, size_t nb_bytes);
*/

/*****************************
* Déchiffrement d'un fichier *
******************************/ 

/*
* Fonction de dechiffrement du fichier file_name au moyen de la clé key.
* La fonction renvoie l'adresse de la suite d'octets contenant le message
* déchiffré (de taille nb_bytes).
*/
uint8_t* decypher_file(char* file_name, RSA_key key, size_t* nb_bytes);

/*
* Fonction prenant la suite de mots (uin32_t) blocks_seq de longueur nb_blocks
* et retournant (l'adresse de) la suite d'octets correspondant.
* (fonction "réciproque" de bytes_to_blocks)
*/
uint8_t*  blocks_to_bytes(uint32_t* blocks_seq, size_t nb_blocks);




#endif /* RSA_h */

