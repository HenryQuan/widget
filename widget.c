#include <stdio.h>

void usage();

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        // No enough arguments
        usage();
        return 1;
    } else {
        
    }

    return 0;
}

// Print how to use this program
void usage() {
    printf("usage: widget [option] [name]\n-f\tcreate a stateful widget\n-l    create a stateless widget (it is 'L' not '1')\n\nhttps://github.com/HenryQuan/widget\n");
}
