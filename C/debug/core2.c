#include <stdio.h>
#include <unistd.h>

void core_test1() {
    int i = 0;
    scanf("%d", i);
    printf("%d\n", i);
}

void core_test2() {
    char *ptr = "myname is tenfyguo";
    *ptr = 0;
}

int main() {
    core_test1();
    core_test2();
}
