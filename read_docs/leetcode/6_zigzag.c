


/**
 * 
 * 主要点: 分配空间列数的计数
 * 2. 在初始化数组的时候，j已经越过边界，所以要减两次才可以
 * @param  s       [description]
 * @param  numRows [description]
 * @return         [description]
 */
char* convert(char* s, int numRows) {
    if (s == NULL || strlen(s) == 0) {
        return "";
    }

    int strLen = strlen(s);
    int modColumn = 0;
    if ((strLen%(2*numRows-1)) < numRows) {
        modColumn = 1;
    } else {
        modColumn = (strLen%(2*numRows-1)) - (numRows-1) ;
    }
    int columns = (strLen/(2*numRows-1)) * numRows + modColumn;

    char *t = malloc(numRows * columns *sizeof(char));
    memset(t, 0, numRows * columns * sizeof(char));

    int i = 0, j = 0, k = 0;
    while (k < strLen) {
        for (j = 0; j < numRows && k < strLen; j++) {
            *(t + j*columns+i) = s[k++];
        }
        j--;
        j--;
        i++;
        for (; j > 0 && k < strLen; j--) {
            *(t + j*columns+i) = s[k++];
            i++;
        }
    }

    // for (j = 0; j < numRows; j++) {
    //     for (i = 0; i < columns; i++) {
    //         if (*(t + j*columns+i) != 0) {
    //             printf("%c", *(t + j*columns+i));
    //         } else {
    //             printf("%d", 0);
    //         }
    //     }
    //     printf("\n");
    // }

    char *res = malloc(sizeof(char) * strLen + 1);
    memset(res, 0, sizeof(char) *strLen + 1);
    k = 0;
    for (j = 0; j < numRows; j++) {
        for (i = 0; i < columns; i++) {
            if (*(t + j*columns+i)!= 0) {
                res[k++]  = *(t + j*columns+i);
            }
        }
    }

    return res;

}
