


/**
 * i : 不要超了
 * j : 
 */



int area(int *height, int index1, int index2) {
    int h = height[index1] < height[index2] ? height[index1] : height[index2];
    int sum = 0;
    for (size_t i = index1+1; i < index2; i++) {
        sum += h-height[i];
    }
    return sum;
}


int trap(int* height, int heightSize) {
    if (heightSize < 2) {
        return 0;
    }

    int sum = 0;
    int x, y = 0;
    int maxIndex,maxValue; //中间变量，记录最高的
    for (int i =0; i< heightSize -1; ) {
        printf("%d ", i);
        //找到最高的左值
        x = 0;
        y = 0;
        while (height[i] >= x) {
            x = height[i];
            if (i+1 == heightSize -1) {
                return sum;
            }
            i++;
        }
        i--;

        //找到右值，右值大于等于x；如果不存在找到最长的。
        int j = i+1;
        maxValue = 0;
        maxIndex = 0;
        while (j < heightSize) {
            if (height[j] > maxValue) {
                maxValue = height[j];
                maxIndex = j;
            }

            if (height[j] >= x) {
                break;
            }
            j++;
        }

        //没有找到
        if (maxValue == 0) {
            i++;
            continue;
        }
        printf(" %d %d\n", i, maxIndex);
        //计算面积
        sum += area(height, i, maxIndex);
        i = maxIndex; //重要，不要超过，应该从maxIndex开始下一次循环。

    }
    return sum;
}
