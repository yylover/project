package main

import (
	"time"
    "antisnow"
)

//func threeSum(nums []int) [][]int {
//	var res [][]int
//	for i := 0; i < len(nums)-2; i++ {
//		for j := i + 1; i < len(nums)-1; j++ {
//			for k := j + 1; k < len(nums); k++ {
//				if nums[i]+nums[j]+nums[k] == 0 {
//					temp := []int{1, 2, 3}
//					res = append(res, temp)
//				}
//			}
//		}
//	}
//	return res
//}

func process(tp *antisnow.TokenPool) {
    for i := 0 ;i < 100; i++ {
        tp.Get()
        time.Sleep(time.Millisecond *10)
        tp.Put()
    }
}


func main() {
	//t1 := time.Now()
	//fmt.Printf("%v", t1.Add(time.Second*20).Sub(t1))

	tp := antisnow.NewTokenPool(10)


	for i := 0 ;i < 1000; i++ {
	    go process(tp)
    }

	time.Sleep(time.Second * 100)

}
