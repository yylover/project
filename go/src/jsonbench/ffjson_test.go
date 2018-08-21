package jsonbench

import (
	"encoding/json"
	"github.com/json-iterator/go"
	"github.com/pquerna/ffjson/ffjson"
	//"github.com/mailru/easyjson"
	"testing"
)



func Benchmark_Original(b *testing.B) {

	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		//t := News{}
		//datamap := map[string]interface{}{}
		data, _ := json.Marshal(datamap)
		json.Unmarshal(data, datamap)
	}
}

func Benchmark_ffjson(b *testing.B) {
	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		//t := News{}
		//datamap := map[string]interface{}{}
		data, _ := ffjson.Marshal(datamap)
		ffjson.Unmarshal(data, datamap)
	}
}

func Benchmark_djson(b *testing.B) {
	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		//t := News{}
		//datamap := map[string]interface{}{}
		var djson = jsoniter.ConfigCompatibleWithStandardLibrary
		data, _ := djson.Marshal(datamap)
		djson.Unmarshal(data, datamap)
	}
}

func Benchmark_OriginjsonInterface(b *testing.B) {
	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}

	var djson = jsoniter.ConfigCompatibleWithStandardLibrary
	data, _ := djson.Marshal(datamap)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		t := map[string]interface{}{}
		json.Unmarshal(data, t)
	}
}

func Benchmark_ffjsonInterface(b *testing.B) {
	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}

	var djson = jsoniter.ConfigCompatibleWithStandardLibrary
	data, _ := djson.Marshal(datamap)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		t := map[string]interface{}{}
		ffjson.Unmarshal(data, t)
	}
}

func Benchmark_djsonInterface(b *testing.B) {
	datamap := &News{
		Id:          "2324",
		Title:       "werwrw",
		Articletype: "swerw",
		Src:         "setwtew",
		ShortUrl:    "wrwer",
		BigImg:      "werwr",
		Flag:        "werwr",
		Cid:         "werwr",
		Vid:         "werwr",
		Duration:    "werwr",
		Reason:      "werwr",
		ReasonFlag:  "werwr",
	}

	var djson = jsoniter.ConfigCompatibleWithStandardLibrary
	data, _ := djson.Marshal(datamap)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		t := map[string]interface{}{}
		djson.Unmarshal(data, t)
	}
}

