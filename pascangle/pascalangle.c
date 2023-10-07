#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // On Windows
#else
    system("clear"); // On Unix-like systems, including macOS
#endif
}
/*
For each number in pascals triangle, it can be calculated using the nCr formula
*/
uint64_t choose(int n, int r)
{
    if (n < r || n < 0 || r < 0)
    {
        return 0; // Return 0 for invalid inputs
    }

    uint64_t result = 1;

    for (int i = 0; i < r; i++)
    {
        result *= (uint64_t)(n - i);
        result /= (uint64_t)(i + 1);
    }

    return result;
}

// Prints the triangle
void printTriangle(int n)
{

    clearScreen();
    printf("press arrow up to increase the height of the triangle and then down to decrease the height\nq to exit\n");
    printf("height: %d\n", n);
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            // Print leading spaces to center-align the numbers
            for (int k = 1; k <= n; k++)
            {
                printf(" ");
            }

            printf(" 1");

            // Move to the next line to start the next row
            printf("\n");
        }
        // Print leading spaces to center-align the numbers
        for (int k = 1; k <= n - i; k++)
        {
            printf(" ");
        }

        // Loop to print the numbers on the current row
        for (int j = 0; j <= 2 * i - 1; j++)
        {
            choose(i, j) == 0 ? printf(" ") : printf(" %llu", choose(i, j));
        }

        // Move to the next line to start the next row
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
    int n = 0;
    int ch;
    printf("\npress arrow up to increase the height of the triangle and then down to decrease the height\nq to exit\n");
    printf("height: %d\n", n);
    while (1)
    {
        ch = getchar(); // Read a character

        if (ch == 'q')
        {
            printf("You pressed 'q'. Quitting...\n");
            break; // Exit the loop if 'q' is pressed
        }
        else if (ch == 27)
        {
            // Check if it's an escape sequence (likely an arrow key)
            ch = getchar(); // Read the next character
            if (ch == '[')
            {
                if (ch == '[')
                {
                    // Read the final character to determine the specific arrow key
                    ch = getchar();
                    if (ch == 'A')
                    {
                        n += 1;
                        printTriangle(n);
                    }
                    else if (ch == 'B')
                    {
                        n -= 1;
                        if (n < 0)
                        {
                            n = 0;
                        }
                        printTriangle(n);
                    }
                }
            }
        }
    }
    return 0;
}
