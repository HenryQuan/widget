///
// widget.c
// Create stateful or stateless widgets for flutter
// 
// 21/09/2019
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int exists(char*);
char* getFileName(char*);
char* getClassName(char*);
int createStateful(char*, char*);
int createStateless(char*, char*);
void usage();
void fatal(char*);

int main(int argc, char* argv[])
{
    int returnValue = 0;

    if (argc < 3) {
        // No enough arguments
        usage();
        returnValue = 1;
    } else {
        char* option = argv[1];
        char* input = argv[2];

        char* filename = getFileName(input);
        char* classname = getClassName(input);
        // Make sure the first alphabet is in UPPER CASE
        classname[0] = toupper(classname[0]);
        
        if (strcmp(option, "-f") == 0) {
            returnValue = createStateful(filename, classname);
        } else if (strcmp(option, "-l") == 0) {
            returnValue = createStateless(filename, classname);
        } else {
            // Invalid option
            fatal("Invalid option!\n");
        }

        // Free up memory (other languages have gc...)
        free(filename);
        free(classname);
    }

    return returnValue;
}

// Check if file exists
int exists(char* filename) {
    if (access(filename, F_OK) != -1) {
        printf("%s exists\nNothing was created\n", filename);
        return 1;
    } else {
        return 0;
    }
}

// Append .dart to input if necessary
char* getFileName(char* input) {
    char* name = malloc(sizeof(char) * (strlen(input) + 5));
    if (name == NULL) fatal("Out of memory");

    strcpy(name, input);
    strcat(name, ".dart");

    return name;
}

// Usually the input is like `HelloWorld` but it is also possible to have `./Henry/HelloWorld` and we need to get `HelloWorld only`
char* getClassName(char* input) {
    int length = strlen(input);
    int start = -1;
    for (int i = length; i > 0; i--) {
        // Starting from the last index
        char curr = input[i - 1];
        if (curr == '/' || curr == '\\') {
            // It should start from the next character because now it is '/' or '\'
            start = i + 1;
            break;
        }
    }

    if (start == -1) {
        // This name is valid (so no '/' or '\')
        return input;
    } else {
        char* name = malloc(sizeof(char) * (length - start + 1));
        if (name == NULL) fatal("Out of memory"); 

        // Copy it into name
        int i = 0;
        for (int j = start; j <= length; j++, i++) {
            name[i] = input[j - 1];
        }

        // Add null
        name[i] = '\0';
        return name;
    }
}

// Create a stateful widget
int createStateful(char* filename, char* input) {
    printf("Creating stateful widget\n");
    if (!exists(filename)) {
        FILE *widget;
        widget = fopen(filename, "w");
        fprintf(widget, "import 'package:flutter/material.dart';\n\n");
        fprintf(widget, "/// %s class\n", input);
        fprintf(widget, "class %s extends StatefulWidget {\n", input);
        fprintf(widget, "  %s({Key key}) : super(key: key);\n\n", input);
        fprintf(widget, "  @override\n");
        fprintf(widget, "  _%sState createState() => _%sState();\n}\n\n\n", input, input);
        fprintf(widget, "class _%sState extends State<%s> {\n", input, input);
        fprintf(widget, "  @override\n");
        fprintf(widget, "  Widget build(BuildContext context) {\n");
        fprintf(widget, "    return Scaffold(\n");
        fprintf(widget, "      appBar: AppBar(\n");
        fprintf(widget, "        title: Text('%s')\n", input);
        fprintf(widget, "      ),\n");
        fprintf(widget, "      body: Container(),\n");
        fprintf(widget, "    );\n");
        fprintf(widget, "  }\n");
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
        fprintf(widget, "class %s extends StatelessWidget {\n", input);
        fprintf(widget, "  %s({Key key}) : super(key: key);\n\n", input);
        fprintf(widget, "  @override\n");
        fprintf(widget, "  Widget build(BuildContext context) {\n");
        fprintf(widget, "    return Scaffold(\n");
        fprintf(widget, "      appBar: AppBar(\n");
        fprintf(widget, "        title: Text('%s')\n", input);
        fprintf(widget, "      ),\n");
        fprintf(widget, "      body: Container(),\n");
        fprintf(widget, "    );\n");
        fprintf(widget, "  }\n");
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

// Fatal error
void fatal(char* msg) {
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}
