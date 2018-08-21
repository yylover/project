package main

import (
	"fmt"
	"encoding/json"
	"os"
	"runtime/pprof"
)

func main() {

	f, err := os.Create("cpu.prof")
	if err != nil {
		return
	}
	defer f.Close()
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()

	fmt.Println("")
	for i := 0 ;i < 10000;i ++ {
		json.Marshal(map[string]interface{}{
			"quick" : "yang",
			"name" : "sex",
		})
	}


}
