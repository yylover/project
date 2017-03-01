

// 最重要的是溢出判断，要在达到临界值前进行判断
int reverse(int x) {

    int isNegative = 0;
    if (x < 0) {
        isNegative = 1;
        x = -x;
    }

    int num = x;
    int res = 0;
    while (num > 0) {
        //溢出判断。
        if (res > (INT_MAX - num %10)/10) {
            return 0;
        }
        res = res * 10 + (num %10);
        num /= 10;
    }

    if (isNegative) {
        res = -res;
    }

    return res;
}
