package main

import (
	//"time"
    //"antisnow"
	"flog"
	"time"
	"sync"
	"signal"
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

//func process(tp *antisnow.TokenPool) {
//    for i := 0 ;i < 100; i++ {
//        tp.Get()
//        time.Sleep(time.Millisecond *10)
//        tp.Put()
//    }
//}
//
//func token_pool() {
//	tp := antisnow.NewTokenPool(10)
//	for i := 0 ;i < 1000; i++ {
//	   go process(tp)
//	}
//}

func writeFile(logger *flog.Log, index int) {

	i := 0
	for {
		time.Sleep(time.Millisecond * 40)
		logger.Info("hello this is ", index)
		i++
		if i >= 2000 {
			return
		}
	}
}


func main() {
	//t1 := time.Now()
	//fmt.Printf("%v", t1.Add(time.Second*20).Sub(t1))

	signal.NewSignalCatcher()

	logger := flog.NewLogger("./logs/", "", "test", flog.LOGLEVEL_INFO, 10, 0, flog.LOGSHIFT_TYPE_MINUTE)
	wg := sync.WaitGroup{}
	for i:=0; i< 50; i++ {
		wg.Add(1)
		go writeFile(logger, i)
	}

	wg.Wait()
	logger.Close()
	time.Sleep(time.Second * 2)

}
