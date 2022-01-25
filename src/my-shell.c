#include "../include/shell.h"

int main(void) {
    int return_value = 0;

    struct shell shell;
    shell_init(&shell);
    shell_run(&shell);
    shell_destroy(&shell);

    return return_value;
}