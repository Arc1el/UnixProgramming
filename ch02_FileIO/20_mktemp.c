#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TMPLT_SIZE 32

int main(void)
{
        char *fname;
        char fntmp[BUFSIZ];
        char template[32];

        fname = tmpnam(NULL);
        printf("1. TMP File Name(tmpnam) : %s\n", fname);

        tmpnam(fntmp);
        printf("2. TMP File Name(tmpnam) : %s\n", fntmp);

        fname=tempnam("/tmp","unix2");
        printf("3. TMP File Name(tempnam) : %s\n", fname);

        strncpy(template, "/tmp/unix2XXXXXX", TMPLT_SIZE);
        fname=mktemp(template);
        printf("4. TMP File Name(mktemp) : :%s\n", fname);

        return 0;
}
