
int max(int n1, int n2, int n3) {
    int max = n1;
    if (n2 > max) {
        max = n2;
    }

    if (n3 > max) {
        max = n3;
    }

    return max;
}

/*
-fPIC是编译选项，PIC是 Position Independent Code 的缩写，表示要生成位置无关的代码，
-shared是链接选项，告诉gcc生成动态库而不是可执行文件。


*/
