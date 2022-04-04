#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>

#define STRING_SIZE 1024

// colors
#define CYN "\x1B[36m"
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"

struct shell {
    int running;
    int line_number;
    size_t buffer_size;
    char *buffer;
};

/**
 * @brief Initialize the shell.
 * 
 * @param s shell to initialize
 */
void shell_init(struct shell *s);

/**
 * @brief Run the shell.
 * 
 * @param s shell to run
 */
void shell_run(struct shell *s);

/**
 * @brief Destroy the shell.
 * 
 * @param s shell to destroy
 */
void shell_destroy(struct shell *s);

/**
 * @brief Read a line of the shell.
 * 
 * @param s shell for which the line is read
 */
void shell_read_line(struct shell *s);

/**
 * @brief Display the shell prompt.
 * 
 * @param s shell for which the prompt is displayed
 */
void shell_prompt(struct shell *s);

/**
 * @brief Interpret and execute a line of the shell.
 * 
 * @param s shell for which the line is interpreted and executed
 */
void shell_execute_line(struct shell *s);
#endif