#ifndef ACTION_H
#define ACTION_H
#include "shell.h"
#include "string-vector.h"

#define STRING_SIZE 1024

typedef void (*action) (
    struct shell *,
    const struct string_vector *
);

/**
 * @brief Get the action.
 * 
 * @param name the name of the action
 * @return action a action
 */
action get_action(char *name);

/**
 * @brief Do the action gave.
 * 
 * @param name the name of the action
 * @param this the shell
 * @param args the command read by the shell
 */
void do_action(char *name, struct shell *this, const struct string_vector *args);

/**
 * @brief Exit the shell.
 * 
 * @param this the shell
 * @param args the command read by the shell
 */
void do_exit(struct shell *this, const struct string_vector *args);

/**
 * @brief Change directory.
 * 
 * @param this the shell
 * @param args the command read by the shell
 */
void do_cd(struct shell *this, const struct string_vector *args);

/**
 * @brief Print working directory.
 */
void do_pwd();

/**
 * @brief Print help.
 */
void do_help();

/**
 * @brief Execute a subshell or a subshell command.
 * 
 * @param this the shell
 * @param args the command read by the shell
 */
void do_system(struct shell *this, const struct string_vector *args);

/**
 * @brief Print a reminder message within a specified time (in seconds). 
 * 
 * @param this the shell
 * @param args the command read by the shell
 */
void do_reminder(struct shell *this, const struct string_vector *args);

/**
 * @brief Show the use of an unknown command.
 */
void do_execute();
#endif