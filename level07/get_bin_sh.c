#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "/bin/sh";
    char *p = (char *) 0xbffff000;

    while (memcmp(++p, s, sizeof s));

    printf("%s\n", p);
    printf("%p\n", p);
}
