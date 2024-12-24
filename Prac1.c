
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to validate string against the pattern a*bb
bool validateString(const char *str) {
    int i = 0;

    // Match zero or more 'a's
    while (str[i] == 'a') {
        i++;
    }

    // Check for "bb" at the end
    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return true;
    }

    return false;
}

int main() {
    char input[100];

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character, if present
    size_t len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Validate the input string
    if (validateString(input)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}
