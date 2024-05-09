#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define OPTIONS_COUNT 5

char *options[] = {
    "Option 1",
    "Option 2",
    "Option 3",
    "Option 4",
    "Option 5"
};

int currentOption = 0;

void enableRawMode() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

void disableRawMode() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

int main() {
    enableRawMode();

    while (1)
    {
        printf("\033[2J\033[H"); // Clear the screen
        for (int i = 0; i < OPTIONS_COUNT; i++)
        {
            if (i == currentOption)
             {
                printf("\033[1;32m > (%d) %s\n", i + 1, options[i]);
                printf("\033[0m");
            }
            else
                printf(" (%d) %s\n", i + 1, options[i]);
        }

        char c = getchar();
        if (c == 'q')
            break;

        if (c == '\033') { // Handle arrow key input
            getchar(); // Skip the '['
            switch (getchar())
            {
                case 'A': // Up arrow
                    currentOption = (currentOption - 1 + OPTIONS_COUNT) % OPTIONS_COUNT;
                    break;
                case 'B': // Down arrow
                    currentOption = (currentOption + 1) % OPTIONS_COUNT;
                    break;
                case 'C': // Right arrow
                    break;
                case 'D': // Left arrow
                    break;
            }
        } else if (c == '\n') { // Enter key
            printf("Selected option: %s\n", options[currentOption]);
            // Perform the desired action for the selected option
            break;
        }
    }

    disableRawMode();
    return 0;
}
