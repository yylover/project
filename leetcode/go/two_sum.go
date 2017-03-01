package main

import (
	"fmt"
)

func twoSum(nums []int, target int) []int {

	var a[]int = make([]int , 2)

	for i:= 0; i < len(nums)-1; i++ {
		for j := i+1; j < len(nums); j++ {
			if (nums[i] + nums[j] == target) {
				a[0] = i
				a[1] = j
			}
		}


	}

	return a
}


func main() {
	a := []int {2, 7, 11, 15}
	b := twoSum(a, 9)
    fmt.Printf("sdfdsf%v", b);
}
