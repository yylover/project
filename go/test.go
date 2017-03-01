package main

func threeSum(nums []int) [][]int {
	var res [][]int
	for i := 0; i < len(nums)-2; i++ {
		for j := i + 1; i < len(nums)-1; j++ {
			for k := j + 1; k < len(nums); k++ {
				if nums[i]+nums[j]+nums[k] == 0 {
					temp := []int{1, 2, 3}
					res = append(res, temp)
				}
			}
		}
	}
	return res
}

func main() {

}
