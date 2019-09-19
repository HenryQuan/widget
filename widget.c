#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int exists(char*);
char* getClassName(char*);
int createStateful(char*, char*);
int createStateless(char*, char*);
void usage();

int main(int argc, char* argv[])
{
    if (argc < 3) {
        // No enough arguments
        usage();
        return 1;
    } else {
        char* option = argv[1];
        char* input = argv[2];
        // Input + .dart
        char* filename = malloc(sizeof(char) * (strlen(input) + 5));
        strcpy(filename, input);
        strcat(filename, ".dart");
        
        if (strcmp(option, "-f") == 0) {
            return createStateful(filename, input);
        } else if (strcmp(option, "-l") == 0) {
            return createStateless(filename, input);
        } else {
            // Invalid option
            printf("Invalid option!\n");
            return 1;
        }
    }
}

// Check if file exists
int exists(char* filename) {
    if (access(filename, F_OK) != -1) {
        printf("%s exists\nNothing was created", filename);
        return 1;
    } else {
        return 0;
    }
}

// Usually the input is like `HelloWorld` but it is also possible to have `./Henry/HelloWorld` and we need to get `HelloWorld only`
char* getClassName(char* input) {
    return NULL;
}

// Create a stateful widget
int createStateful(char* filename, char* input) {
    printf("Creating stateful widget\n");
    if (!exists(filename)) {
        FILE *widget;
        widget = fopen(filename, "w");
        fprintf(widget, "import 'package:flutter/material.dart';\n\n");
        fprintf(widget, "/// %s class\n", input);
        fprintf(widget, "class %s extends StatefulWidget {\n\n", input);
        fprintf(widget, "   %s({Key key}) : super(key: key);\n\n", input);
        fprintf(widget, "   @override\n");
        fprintf(widget, "   _%sState createState() => _%sState();\n\n}\n\n\n", input, input);
        fprintf(widget, "class _%sState extends State<%s> {\n\n", input, input);
        fprintf(widget, "   @override\n");
        fprintf(widget, "   Widget build(BuildContext context) {\n");
        fprintf(widget, "       return Container();\n");
        fprintf(widget, "   }\n\n");
        fprintf(widget, "}\n");
        fclose(widget);
        printf("Success\n");
        return 0;
    }

    return 1;
}

// Create a stateless widget
int createStateless(char* filename, char* input) {
    printf("Creating stateless widget\n");
    if (!exists(filename)) {
        FILE *widget;
        widget = fopen(filename, "w");
        fprintf(widget, "import 'package:flutter/material.dart';\n\n");
        fprintf(widget, "/// %s class\n", input);
        fprintf(widget, "class %s extends StatelessWidget {\n\n", input);
        fprintf(widget, "   %s({Key key}) : super(key: key);\n\n", input);
        fprintf(widget, "   @override\n");
        fprintf(widget, "   Widget build(BuildContext context) {\n");
        fprintf(widget, "       return Container();\n");
        fprintf(widget, "   }\n\n");
        fprintf(widget, "}\n");
        fclose(widget);
        printf("Success\n");
        return 0;
    }

    return 1;
}

// Print how to use this program
void usage() {
    printf("usage: widget [option] [name]\n-f\tcreate a stateful widget\n-l\tcreate a stateless widget (it is 'L' not '1')\nname\tanything but DO NOT include .dart\n\nhttps://github.com/HenryQuan/widget\n");
}
