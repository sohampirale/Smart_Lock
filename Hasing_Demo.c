// // Password Hashing using PBKDF2 and SHA-256 algorithm
//    Program to see the acutal hased passwrod

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void hash_password(const char *password, const char *salt, unsigned char *outputBuffer){
    int iterations = 1000;
    int outputLength = 20;

    PKCS5_PBKDF2_HMAC(password, strlen(password), (unsigned char *)salt, strlen(salt), iterations, EVP_sha256(), outputLength, outputBuffer);
}

int main(){
    char password[15];
    printf("Enter your Password : ");
    fgets(password,15,stdin);
    char salt[] = "random_salt";

    unsigned char hash[20];
    hash_password(password, salt, hash);

    printf("\n\nHash : ");

    for (int i = 0; i < 20; i++){
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}



