int areaSize(int i, int j, int ai, int aj) {
    int height = ai < aj ? ai: aj;
    return height * (j-i);
}

//遍历 O(n^2) 复杂度
int maxArea(int* height, int heightSize) {
    if (heightSize < 2) {
        return 0;
    }

    int max = 0;
    for (int i = 0; i < heightSize-1; i++) {
        for (int j = i+1; j < heightSize;j++) {
            int temp = areaSize(i, j, height[i], height[j]);
            if (temp > max) {
                max = temp;
            }
        }
    }

    return max;
}



// 主要利用了性质，假设找到了两个点ai,aj,使得容量最大，那么，j右边的值都比j小，i左边的值都比i小。
// 
int maxArea(int* height, int heightSize) {
    if (heightSize < 2) {
        return 0;
    }

    int leftMax = 0, rightMax= 0;
    int max = 0;
    for (int i = 0; i < heightSize-1; i++) {
        rightMax=0;
        if (height[i] > leftMax) {
            leftMax = height[i];
        } else {
            continue;
        }
        for (int j = heightSize-1; j > i;j--) {
            if (height[j] >  rightMax) {
                rightMax = height[j];
            } else {
                continue;
            }

            int temp = areaSize(i, j, height[i], height[j]);
            if (temp > max) {
                max = temp;
            }
        }
    }

    return max;
}
