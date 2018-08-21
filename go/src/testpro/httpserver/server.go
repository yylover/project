package main

import (
	//"fmt"
	//"html"
	//"html/template"
	"net/http"
	_ "net/http/pprof"
)

type Page struct {
	Scheme string
	Domain string
	Body   string
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	//p := &Page{
	//	Scheme: "http",
	//	Domain: "meican.loc",
	//	Body:   "快乐大本营新一期嘉宾预告:刘宪华演技\"浮夸\"，向往的生活MC齐聚!",
	//}
	//fmt.Println(html.EscapeString(p.Body))
	//t, _ := template.ParseFiles("index.html")
	//t.Execute(w, p)

	w.Write([]byte("hello"))
}

func main() {

	http.HandleFunc("/index", indexHandler)
	http.ListenAndServe(":8089", nil)
}
