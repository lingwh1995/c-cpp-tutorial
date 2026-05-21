#include <stdbool.h>
#include <stdio.h>

int main()
{
    bool is_valid = true;
    bool is_error = false;

    if (is_valid)
    {
        printf("Valid!\n");
    }

    if (!is_error)
    {
        printf("Error!\n");
    }
    return 0;
}
