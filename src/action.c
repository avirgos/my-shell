#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/action.h"

struct {
    const char *name;
    action action;
} actions[] = {
    { .name = "exit", .action = do_exit },
    { .name = "cd", .action = do_cd },
    { .name = "pwd", .action = do_pwd },
    { .name = "?", .action = do_help },
    { .name = "help", .action = do_help },
    { .name = "!", .action = do_system },
    { .name = "rem", .action = do_reminder },
    { .name = NULL, .action = do_execute },
};

action get_action(char *name) {
    int i = 0;

    while (actions[i].name != NULL && strcmp(actions[i].name, name) != 0) {
        ++i;
    }
    
    return actions[i].action;
}

void do_action(char *name, struct shell *this, const struct string_vector *args) {
    action action = get_action(name);
    action(this, args);
}

void do_exit(struct shell *this, const struct string_vector *args) {
    this->running = 0;
    
    (void)args;
}

void do_cd(struct shell *this, const struct string_vector *args) {
    char *path;

    if (string_vector_size(args) == 1) {
        path = getenv("HOME");
    } else {
        path = string_vector_get(args, 1);
    }

    chdir(path);

    (void)this;
}

void do_pwd() {
    char *cwd = malloc(STRING_SIZE * sizeof(char));
    getcwd(cwd, STRING_SIZE);

    printf("%s\n", cwd);

    free(cwd);
}

void do_help() {
    write(STDIN_FILENO, "\tmy-shell\n\n", 12);
    write(STDIN_FILENO, "- exit\n", 8);
    write(STDIN_FILENO, "- cd <dir> : change directory\n", 31);
    write(STDIN_FILENO, "- pwd : print current/working directory\n", 41);
    write(STDIN_FILENO, "- ! : execute a subshell\n", 26);
    write(STDIN_FILENO, "- ! <command> : execute a command from a subshell\n", 51);
    write(STDIN_FILENO, "- rem <time_seconds> <message> : print a reminder message\n", 59);
}

void do_system(struct shell *this, const struct string_vector *args) {
    char *shell = getenv("SHELL");
    
    if (string_vector_size(args) == 1) {
        if (shell == NULL) {
            write(STDIN_FILENO, "Environment variable SHELL is not defined.\n", 44);
        } else {
            write(STDIN_FILENO, "Subshell executed. (type exit to come back)\n", 45);      
            system(shell);
        }
    // ! <command>
    } else {
        char *subshell_command = malloc(STRING_SIZE * sizeof(char));
        str_join_array(subshell_command, args, 1, string_vector_size(args), " ");
        char *subshell_command_without_first_space = subshell_command + 1;

        // ! clear
        if(strcmp(subshell_command_without_first_space, "clear") == 0) {
            this->line_number = 0;
        }

        system(subshell_command_without_first_space);

        free(subshell_command);
    }
}

void do_reminder(struct shell *this, const struct string_vector *args) {
    if (string_vector_size(args) > 2) {
        pid_t p = fork();

        if (p == 0) {
            int time_seconds = strtol(string_vector_get(args, 1), NULL, 10);
            sleep(time_seconds);

            char *message = malloc(STRING_SIZE * sizeof(char));
            str_join_array(message, args, 2, string_vector_size(args), " ");
            char *message_without_first_space = message + 1;

            write(STDIN_FILENO, "\n[] Reminder : ", 16);
            write(STDIN_FILENO, message_without_first_space, strlen(message_without_first_space));
            write(STDIN_FILENO, " ", 2);

            free(message);
            
            exit(EXIT_SUCCESS);
        }
    } else {
        write(STDIN_FILENO, "- rem <time_seconds> <message> : print a reminder message\n", 59);
    }

    (void)this;
}

void do_execute() {
    write(STDIN_FILENO, "Unknown command.\n", 18);    
}