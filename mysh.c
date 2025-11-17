#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_LEN 1024

int main(int argc, char *argv[])
{
    FILE *input = stdin;
    int interactive_mode = 0;

    // Handle command line arguments
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [script_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
        interactive_mode = 0; // File input is never interactive
    }
    else
    {
        // Check if stdin is connected to a terminal
        interactive_mode = isatty(STDIN_FILENO);
    }

    // Print welcome message in interactive mode
    if (interactive_mode)
    {
        printf("Welcome to my shell!\n");
    }

    // Main shell loop
    char command[MAX_CMD_LEN];
    while (1)
    {
        // Print prompt in interactive mode
        if (interactive_mode)
        {
            printf("mysh> ");
            fflush(stdout);
        }

        // Read command using read() as required
        char *result = fgets(command, sizeof(command), input);
        if (!result)
        {
            // EOF reached
            break;
        }

        // Remove trailing newline
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
        {
            command[len - 1] = '\0';
        }

        // Skip empty commands
        if (strlen(command) == 0)
        {
            continue;
        }

        // TODO: Parse and execute command
        printf("You entered: %s\n", command);

        // Check for exit command
        if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }

    // Print goodbye message in interactive mode
    if (interactive_mode)
    {
        printf("mysh: exiting\n");
    }

    // Close file if we opened one
    if (input != stdin)
    {
        fclose(input);
    }

    return EXIT_SUCCESS;
}
