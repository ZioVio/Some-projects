#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <getopt.h> 
#include <ctype.h>
#include <stdbool.h>


typedef struct _args
{
    char *inputFileName;
    char *n;
    char *outFileName;
} Args; 

bool str_is_num(const char * src) {
    while(*src != '\0') {
        if (!isdigit(*src)) 
            return false;
        src++;
    }
    return true;
}

string * createOuputStringFromFile(char *inputFileName);

Args parseArgs(int argc, char **argv)
{
    int opt;
    Args args = {NULL, NULL, NULL};
    while ((opt = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            args.n = optarg;
            if (!str_is_num(optarg))
            {
                printf("Oprion \"n\" needs an number value\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'o':
            args.outFileName = optarg;
            break;
        case ':':
            printf("option needs a value\n");
            break;
        case '?':
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (optind + 1 == argc)
        args.inputFileName = argv[optind];
    return args;
}
int main(int argc, char *argv[]) {
    Args comLine = parseArgs(argc, argv);
    if (comLine.inputFileName != NULL)
        printf("Input file: %s\n", comLine.inputFileName);
    if (comLine.outFileName == NULL)
        printf("Output file: %s\n", comLine.outFileName);


    if (comLine.n != NULL)
        printf("N argument: %s\n", comLine.n);

    if (comLine.inputFileName == NULL) {
        printf("Missing input file name\n");
        exit(1);
    }


    FILE *fout;
    if (comLine.outFileName != NULL)
    {
        if ((fout = freopen(comLine.outFileName, "w+", stdout)) == NULL)
        {
            printf("Cannot open file %s\n", comLine.outFileName);
            exit(EXIT_FAILURE);
        }
    } else {
        //console print
    }

    string * result_string = createOuputStringFromFile(comLine.inputFileName);
    String_println(result_string);

    return 0;
}


string * createOuputStringFromFile(char *inputFileName) {
    FILE *fp;
    string * string = String_alloc("");
    if ((fp = fopen(inputFileName, "r+")) == NULL)
    {
        fprintf(stderr, "Cannot open file %s\n", inputFileName);
        return string;
    }
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch)) {
            continue;
        }
        char buf[2];
        buf[0] = ch; buf[1] = '\0';
        String_append(string, buf); 
    }
    fclose(fp);
    return string;
}