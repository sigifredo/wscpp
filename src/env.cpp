

// std
#include <cstdio>

int main (int argc, char **argv, char **env)
{
    std::printf("Content-type: text/plain\r\n\r\n");

    char ** it = env;
    for (it = env; *it != 0; it++)
    {
        std::printf("%s\n", *it);
    }

    return 0;
}
