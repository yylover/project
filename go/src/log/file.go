package log

import (
	"bytes"
	"os"
	"sync"
	"time"
)

const (
	ChanSize   = 100
	BufferSize = 1024 * 1024
)

type FileLog struct {
	logPath   string
	prefix    string
	logLevel  LOGLEVEL
	logName   string
	logNum    int
	logSize   int
	shiftType SHIFT_TYPE

	file        *os.File
	writeBuffer *bytes.Buffer
	writeChan   chan string
	quitChan    chan bool
	wg          sync.WaitGroup
	fileMutext  *sync.Mutex
}

func NewFileLog(logpath string, logPrefix string, logname string, logLevel LOGLEVEL, logNum int, logSize int, shifttype SHIFT_TYPE) *FileLog {

	buffer := bytes.NewBuffer(nil)
	buffer.Grow(BufferSize)

	log := &FileLog{
		logPath:   logpath,
		logName:   logname,
		prefix:    logPrefix,
		logLevel:  logLevel,
		logNum:    logNum,
		logSize:   logSize,
		shiftType: shifttype,

		writeBuffer: buffer,
		writeChan:   make(chan string, ChanSize),
		quitChan:    make(chan bool),
		fileMutext:  new(sync.Mutex),
	}

	return log
}

func (this *FileLog) Close() {

}

func (this *FileLog) RawLog() {

}

func (this *FileLog) logprint(level LOGLEVEL, format string, v ...interface{}) {
	content := this.formatContent(level)
	this.writeChan <- content
}

func (this *FileLog) formatContent(level LOGLEVEL) string {
	return ""
}

func (this *FileLog) shiftFileBySize(fileName string) error {
	return nil
}

func (this *FileLog) shiftFileByTime(fileName string) error {
	return nil
}

func (this *FileLog) rotateDeleteLogs() error {
	return nil
}

func (this *FileLog) shiftTime() *time.Timer {
	return time.NewTimer(time.Second * 10)
}

func (this *FileLog) getFileName() string {
	return ""
}

func (this *FileLog) asyncFlush() {

}

//将缓冲区的文件内容输出到文件
func (this *FileLog) Flush() {

}

//判断文件路径是否合法
func checkFilePath(logPath string) {

}
