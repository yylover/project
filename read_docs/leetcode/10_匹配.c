

/**
 * 递归的思路
 * '.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
 */
/**
 * 字符串最后一个字符的判断可以使用*p == '\0' 或者 !*p
 */

bool IsCharacterEqual(char s, char p) {
    return s == p || (s != '\0' && p == '.');
}


//完全递归的方式实现。
bool isMatch(char* s, char* p) {
    if(s==NULL || p==NULL)return false;
    if(!*p) return !*s;
    if(*(p+1)=='*'){
        while(IsCharacterEqual(*s, *p)){
            if(isMatch(s,p+2))return true;
            s++;
        }
        return isMatch(s,p+2);
    }else if(IsCharacterEqual(*p, *s)){
        return isMatch(s+1,p+1);
    }
    return false;
}



//半循环的方式实现
bool isMatch(char *s, char *p) {
    if (s == NULL || p == NULL) {
        return false;
    }

    while (*p) {
        if (*(p+1) == '*') { //
            while(IsCharacterEqual(*s, *p)) {
                if (isMatch(s, p+2)) {
                    return true;
                }
                s++;
            }
            p = p+2;
        } else if (IsCharacterEqual(*s, *p)) {
            s++;
            p++;
        } else {
            return false;
        }
    }

    return !*s;
}


//完全递归的方式
bool isMatch(char *s, char *p) {
    if (s == NULL || p == NULL) {
        return false;
    }

    if (!*p) { //p 到末尾
        return !*s;
    }

    if (*(p + 1) == '*') {
        while (IsCharacterEqual(*s, *p)) {
            if (isMatch(s, p+2)) {
                return true;
            }
            s++;
        }
        return isMatch(s, p+2);
    } else if (IsCharacterEqual(*s, *p)) {
        return isMatch(s+1, p+1);
    }
    return false;
}
