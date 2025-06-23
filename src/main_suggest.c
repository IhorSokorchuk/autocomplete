#include "ui.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <completion-command>\n", argv[0]);
        return 1;
    }
    interactive_loop(argv[1]);
    return 0;
}
