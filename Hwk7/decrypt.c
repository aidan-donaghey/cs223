#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "dict.h"


//Below is variables that I am taking from encrypt so that the hashing works the same 
#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

#define PASSWORD_DELIMITER (':')

#define GETLINE_INITIAL_SIZE (16)
#define GETARRAY_INITIAL_SIZE (32)
#define GETLINE_MULTIPLIER (2)


typedef struct ArrayofStrings
{
    char** lines;
    size_t nlines;
} arrayofStrings;

////////////////////////////////////
///////////////////////////////////
//INSTRUCTIONS TO HASH THE FUNCTION
//FIRST HASH THE SALT 
//THEN HASH THE PASSWORD USING THE SALT HASH AS THE HASH
//RUN precomputeSaltHash
//
////////////////////////////////////
///////////////////////////////////



//This updates a the hash adding in the string 
//The string is the password 
//The orginal hash is the hash of the salt
static void FNV1a(uint64_t *hash, const char *s)
{
    while(*s) {
        *hash ^= *s++;
        *hash *= FNV_PRIME_64;
    }
}

// This creates the hash that is passed into the fuction above
//It is based off of the salt. 
static uint64_t
precomputeSaltHash(const char *salt)
{
    uint64_t hash = FNV_OFFSET_BASIS_64;

    FNV1a(&hash, salt);

    return hash;
}

//This is the fuction that rehashes the orginal Hash and the string together
static uint64_t
passwordHash(uint64_t saltHash, const char *password)
{
    FNV1a(&saltHash, password);

    return saltHash;
}

// fetch characters from stdin to first newline or EOL
// returns malloc'd buffer that should be freed by caller
// if EOL is first character, returns 0
static char * getLine(void)
{
    int c;
    // invariant:
    // size > top
    // size = size of buffer
    size_t size = GETLINE_INITIAL_SIZE;
    size_t top = 0;
    char *buffer = calloc(size, sizeof(char));

    assert(buffer);

    for(;;) {
        switch((c = getchar())) {

            case EOF:
                if(top == 0) {
                    // got nothing
                    free(buffer);
                    return 0;
                }
                // else fall through

            case '\n':
                buffer[top] = '\0';
                return buffer;

            default:
                buffer[top++] = c;
                if(top >= size) {
                    size *= GETLINE_MULTIPLIER;
                    buffer = realloc(buffer, size * sizeof(char));

                    assert(buffer);
                }
        }
    }
}
//This checks if file exists and returns it if it does.
FILE* getPasswordFile(char *filename){
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp){
        // while ( (ch = fgetc(fp)) != EOF )
        //    {
        //         printf("%c",ch);
        //    }
        return fp;
    }
    else{
        printf("Failed to open the file\n");
        return NULL;
    }

}



//This encrpyted a single password
uint64_t encryptPassword(uint64_t saltHash, char *password){
    int64_t hash = passwordHash(saltHash, password);
    return hash;
}

//This is gonna be a function that adds all of the passwords and the 
//the hashed passwords to the hash table.
//Rename this function
Dict getAllLines(FILE *fp,uint64_t saltHash){
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    Dict dictionary = DictCreate();
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0){
        line_count++;
        //This line checks if it is a blank line.
        if(line_buf[0]=='\n'){
            break;
        }
        //printf("%s",line_buf);
        //At this point line_buf is the current password in the list
        //We want to save a variable that is the hashed version of it
        //And add it as the Key and the actual password as the value


        //This line removes the new line char that was messing with the data
        line_buf[line_size-1] ='\0'; 
        char* password = line_buf;
        int64_t encryptedpassword = encryptPassword(saltHash,password);
        //printf("%" PRIx64 ":%s\n", encryptedpassword,password);
        char encrypted[64];
        //Before inserting it must be of the type char*
        sprintf(encrypted, "%"  PRIx64 , encryptedpassword);
        DictInsert(dictionary, encrypted, password);
        //


        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    free(line_buf);
    line_buf = NULL;
    return dictionary;
}






//This is a modified Main file from the encrypt file
int
main(int argc, char **argv)
{
    FILE *fp;
    char *filename;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s salt {Password.dict File} <encrypted.pass \n", argv[0]);
        return 1;
    }
    filename = argv[2];
    fp = getPasswordFile(filename);

    uint64_t saltHash = precomputeSaltHash(argv[1]);
    Dict dictionary = getAllLines(fp,saltHash);
    
    //printf("%s",DictSearch(dictionary, "ba29395850adc9a4"));
    //This is altered code from the encrypt file
    int c;
    while((c = getchar()) != EOF) {
        // copy to stdout
        //This is copying the parts before the delimiter
        putchar(c);

        if(c == PASSWORD_DELIMITER) {
            // process password which is now encryted
            char *password = getLine();
            assert(password);
            //TODO
            if(DictSearch(dictionary,password) == NULL){
                printf("%s\n",password);
            }
            else{
                printf("%s\n",DictSearch(dictionary,password));
            }
            free(password);
        } 
    }
    //free(password);
    fclose(fp);
    return 0;
}


