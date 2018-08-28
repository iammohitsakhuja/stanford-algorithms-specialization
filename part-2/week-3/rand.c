#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s num mod\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int num = atoi(argv[1]);
    int mod = atoi(argv[2]);

    for (int i = 0; i < num; i++)
        printf("%i\n", rand() % mod);

    return 0;
}
