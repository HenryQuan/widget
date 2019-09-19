#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int exists(char*);
int createStateful(char*);
int createStateless(char*);
void usage();

int main(int argc, char* argv[])
{
    if (argc < 3) {
        // No enough arguments
        usage();
        return 1;
    } else {
        FILE *widget;

        char* option = argv[1];
        char* input = argv[2];
        // Input + .dart
        char* filename = malloc(sizeof(char) * (strlen(input) + 5));
        strcpy(filename, input);
        strcat(filename, ".dart");
        
        if (strcmp(option, "-f") == 0) {
            printf("Creating stateful widget\n");
            if (!exists(filename)) {
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
            }
        } else if (strcmp(option, "-l") == 0) {
            printf("Creating stateless widget\n");
            if (!exists(filename)) {
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
            }
        } else {
            // Invalid option
            printf("Invalid option!\n");
            return 1;
        }
    }

    return 0;
}

// Check if file exists
int exists(char* filename) {
    if (access(filename, F_OK) != -1) {
        printf("%s exists", filename);
        return 1;
    } else {
        return 0;
    }
}

// Create a stateful widget
int createStateful(char* name) {
    return 0;
}

// Create a stateless widget
int createStateless(char* name) {
    return 0;
}

// Print how to use this program
void usage() {
    printf("usage: widget [option] [name]\n-f\tcreate a stateful widget\n-l\tcreate a stateless widget (it is 'L' not '1')\nname\tanything but DO NOT include .dart\n\nhttps://github.com/HenryQuan/widget\n");
}
