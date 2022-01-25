#include <string.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/string-vector.h"
#include "../include/string-utils.h"
#include "../include/action.h"

void shell_init(struct shell *s) {
    s->running = 1;
    s->line_number = 0;
    s->buffer_size = 256;
    s->buffer = malloc(s->buffer_size * sizeof(char));
}

void shell_run(struct shell *s) {
    while(s->running == 1) {
        shell_read_line(s);
        shell_execute_line(s);
    }
}

void shell_destroy(struct shell *s) {
    free(s->buffer);
    s->buffer = NULL;
}

void shell_read_line(struct shell *s) {
    shell_prompt(s);
    
    ssize_t size_read_line = read(STDIN_FILENO, s->buffer, s->buffer_size);
    s->buffer[size_read_line] = '\0';

    ++s->line_number; 
}

void shell_prompt(struct shell *s) {
    char *cwd = malloc(STRING_SIZE * sizeof(char));
    getcwd(cwd, STRING_SIZE);

    char *user = getenv("USER");

    char *home = getenv("HOME");

    char *line_number_str = malloc(STRING_SIZE * sizeof(char));
    sprintf(line_number_str,  "%d", s->line_number);

    if (strstr(cwd, home) != NULL) {
        // home replaced by ~
        char *cwd_replace = strreplace(cwd, home, "~");

        write(STDOUT_FILENO, line_number_str, strlen(line_number_str));
        write(STDOUT_FILENO, "|", 1);
        write(STDOUT_FILENO, CYN, strlen(CYN));
        write(STDOUT_FILENO, user, strlen(user));
        write(STDOUT_FILENO, RESET, strlen(RESET));
        write(STDOUT_FILENO, ":", 1);
        write(STDOUT_FILENO, GRN, strlen(GRN));
        write(STDOUT_FILENO, cwd_replace, strlen(cwd_replace));
        write(STDOUT_FILENO, RESET, strlen(RESET));
        write(STDOUT_FILENO, " $ ", 3);

        free(cwd_replace);
    } else {
        write(STDOUT_FILENO, line_number_str, strlen(line_number_str));
        write(STDOUT_FILENO, "|", 1);
        write(STDOUT_FILENO, CYN, strlen(CYN));
        write(STDOUT_FILENO, user, strlen(user));
        write(STDOUT_FILENO, RESET, strlen(RESET));
        write(STDOUT_FILENO, ":", 1);
        write(STDOUT_FILENO, GRN, strlen(GRN));
        write(STDOUT_FILENO, cwd, strlen(cwd));
        write(STDOUT_FILENO, RESET, strlen(RESET));
        write(STDOUT_FILENO, " $ ", 3);
    }

    free(line_number_str);
    free(cwd);
}

void shell_execute_line(struct shell *s) {
    struct string_vector tokens = split_line(s->buffer);
    size_t tokens_number = string_vector_size(&tokens);

    if (tokens_number == 0) {
        string_vector_free(&tokens);
        return;
    } else {
        char *first_token = string_vector_get(&tokens, 0);

        do_action(first_token, s, &tokens);
    }

    string_vector_free(&tokens);
}