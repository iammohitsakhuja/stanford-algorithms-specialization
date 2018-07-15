#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s num\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int num = atoi(argv[1]);

    for (int i = 0; i < num; i++)
        printf("%i\n", rand() % 10000);

    return 0;
}