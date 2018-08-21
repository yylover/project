package antisnow

import "fmt"

const (
	DEFAULT_NUM = 2000
)

type TokenPool struct {
	pool chan struct{}
}

func NewTokenPool(num int) *TokenPool {

	tp := &TokenPool{
		pool: make(chan struct{}, num),
	}

	for i := 0; i < num; i++ {
		tp.pool <- struct{}{}
	}

	return tp
}

//获取资源
func (tp *TokenPool) Get() {
	<-tp.pool
}

//释放资源
func (tp *TokenPool) Put() {
	select {
	case tp.pool <- struct{}{}:
	default:
		fmt.Println("pool full")

	}
}
