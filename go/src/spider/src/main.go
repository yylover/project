package main

import (
    "github.com/gocolly/colly"
    "util"
    "fmt"
    "log"
)

func main() {
    coll := colly.NewCollector(
        colly.UserAgent(util.RandomString()),
        colly.AllowedDomains("bj.lianjia.com"),
        //colly.AllowURLRevisit(),
    )
    coll.OnRequest(func(r *colly.Request) {
        fmt.Println("Visiting", r.URL)
    })

    coll.OnScraped(func(r *colly.Response) {
        fmt.Println("Finished", r.Request.URL)
    })
    coll.OnError(func(_ *colly.Response, err error) {
        log.Println("Something went wrong:", err)
    })

    coll.OnResponse(func(r *colly.Response) {
        fmt.Println("Visited", r.Request.URL)
    })

    coll.OnHTML("a[href]", func(e *colly.HTMLElement) {
        //fmt.Println("onHtml:", e.Attr("href"), string(e.Response.Body))
        fmt.Println("onHtml:", e.Attr("href"))
        e.Request.Visit(e.Attr("href"))
        c.Visit(e.Request.AbsoluteURL(e.Attr("href")))

    })

    coll.OnHTML("tr td:nth-of-type(1)", func(e *colly.HTMLElement) {
        fmt.Println("First column of a table row:", e.Text)
    })

    coll.OnXML("//h1", func(e *colly.XMLElement) {
        fmt.Println(e.Text)
    })

    coll.Request("GET", "https://bj.lianjia.com/ershoufang/", nil, nil, nil)
}
