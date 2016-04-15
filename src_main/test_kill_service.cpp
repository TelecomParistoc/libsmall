#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    setuid(0);
    printf("%d\n",system("ps -Al | grep loop"));
    return 0;
}
