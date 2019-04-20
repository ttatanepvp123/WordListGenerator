#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("Usage : %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        char buffer[255] = {};
        int wordsNumber = 0;
        char **words = NULL;
        FILE *input = NULL;
        FILE *output = NULL;

        if (!strcmp(argv[1], "-")){
            input = fopen("/dev/stdin", "r");
        } else {
            input = fopen(argv[1], "r");
        }
        
        if (input == NULL){
            perror("[ ERROR ] ");
            exit(EXIT_FAILURE);
        }

        while (1){
            memset(buffer, '\0', 255);
            fgets(buffer, 255, input);
            buffer[strlen(buffer)-1] = '\0';
            if(!strlen(buffer)){
                break;
            } else if (!wordsNumber){
                wordsNumber++;
                words = malloc(sizeof(char *));
                assert(words != NULL);
                words[wordsNumber-1] = malloc(strlen(buffer));
                strcpy(words[wordsNumber-1], buffer);
            } else {
                wordsNumber++;
                words = realloc(words,sizeof(char *)*wordsNumber);
                assert(words != NULL);
                words[wordsNumber-1] = malloc(strlen(buffer));
                strcpy(words[wordsNumber-1], buffer);
            }
        }

        fclose(input);

        output = fopen(argv[2], "w");

        if (output == NULL){
            perror("[ ERROR ] ");
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < wordsNumber; i++){
            printf("%ld\r", i * 100 / wordsNumber);
            for (size_t j = 0; j < wordsNumber; j++){
                memset(buffer, '\0', 255);
                sprintf(buffer,"%s%s", words[i], words[j]);
                fprintf(output, "%s\n", buffer);
            }
        }
        fclose(output);
    }
    return 0;
}
