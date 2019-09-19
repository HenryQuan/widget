#include <stdio.h>
#include <string.h>

void usage();

int main(int argc, char* argv[])
{
    if (argc < 3) {
        // No enough arguments
        usage();
        return 1;
    } else {
        char* option = argv[1];
        if (strcmp(option, "-f") == 0) {
            printf("Creating stateful widget...\n");
        } else if (strcmp(option, "-l") == 0) {
            printf("Creating stateless widget...\n");
        } else {
            // Invalid option
            printf("Invalid option!\n");
            return 1;
        }
    }

    return 0;
}

// Print how to use this program
void usage() {
    printf("usage: widget [option] [name]\n-f\tcreate a stateful widget\n-l    create a stateless widget (it is 'L' not '1')\n\nhttps://github.com/HenryQuan/widget\n");
}
