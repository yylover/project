package flog

import (
	"bytes"
	"fmt"
	"os"
	"runtime"
	"strings"
	"sync"
	"time"
)

const (
	ChanSize   = 100
	BufferSize = 1024 * 1024
	FlushSize  = 1024 * 512
)

type FileLog struct {
	logPath   string
	prefix    string
	logLevel  LOGLEVEL
	logName   string
	logNum    int
	logSize   int
	shiftType SHIFT_TYPE

	file           *os.File
	writeBuffer    *bytes.Buffer
	writeChan      chan string
	quitChan       chan bool
	wg             sync.WaitGroup
	fileMutext     *sync.Mutex
	curLogFileName string
}

func NewFileLog(logpath string, logPrefix string, logname string, logLevel LOGLEVEL, logNum int, logSize int, shifttype SHIFT_TYPE) *FileLog {

	checkFilePath(logpath)
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

	go log.asyncFlush()
	go log.shiftFile()

	return log
}

func (this *FileLog) Close() {
	close(this.quitChan)
	this.wg.Wait()
}

func (this *FileLog) Logprint(level LOGLEVEL, format string, v ...interface{}) {
	content := this.formatContent(level, format, v...)
	this.writeChan <- content
}

func (this *FileLog) formatContent(level LOGLEVEL, format string, v ...interface{}) string {
	datestr := time.Now().Format("[2006-01-02] 15:04:05.99999")
	levelstr := ""
	switch this.logLevel {
	case LOGLEVEL_DEBUG:
		levelstr = "[DEBUG]"
	case LOGLEVEL_INFO:
		levelstr = "[INFO]"
	case LOGLEVEL_WARN:
		levelstr = "[WARN]"
	case LOGLEVEL_ERROR:
		levelstr = "[ERROR]"
	case LOGLEVEL_FATAL:
		levelstr = "[FATAL]"
	}

	ocontent := fmt.Sprintf(format, v...)

	_, fullFileName, line, _ := runtime.Caller(3)
	fullFileNameSp := strings.Split(fullFileName, "/")
	shortFileName := fullFileNameSp[len(fullFileNameSp)-1]
	fileInfo := fmt.Sprintf(" %s:%d", shortFileName, line)

	return fmt.Sprintf("%s %s %s %s %s", datestr, levelstr, this.prefix, ocontent, fileInfo)
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

func (this *FileLog) shiftFile() {
	defer this.wg.Done()
	if this.shiftType == LOGSHIFT_TYPE_SIZE {
		return
	}

	for {
		select {
		case <-this.quitChan:
			return
		case <-this.getNextTimer().C:
			//
			name := this.getLogfileName()
			if name != this.curLogFileName {
				if err := this.reopen(name); err != nil {
					fmt.Println("reopen failed :", name, err.Error())
					continue
				}
				this.curLogFileName = name
				continue
			}

			//get file name
			now := time.Now()
			newFileName := ""
			todeleteFileName := ""
			if this.shiftType == LOGSHIFT_TYPE_MINUTE {
				newFileName = now.Add(-1 * time.Minute).Format("20060102-1504")
				todeleteFileName = now.Add(-time.Duration(this.logNum) * time.Minute).Format("20060102-1504")
			} else if this.shiftType == LOGSHIFT_TYPE_HOUR {
				newFileName = now.Add(-1 * time.Hour).Format("20060102-15")
				todeleteFileName = now.Add(-time.Duration(this.logNum) * time.Hour).Format("20060102-15")
			} else if this.shiftType == LOGSHIFT_TYPE_DAY {
				newFileName = now.Add(-24 * time.Hour).Format("20060102")
				todeleteFileName = now.Add(-24 * time.Duration(this.logNum) * time.Hour).Format("20060102")
			}

			go os.Remove(name + "." + todeleteFileName)
			this.fileMutext.Lock()
			os.Rename(name, name+"."+newFileName)
			this.reopen(name)
			this.fileMutext.Unlock()
		}
	}
}

func (this *FileLog) reopen(filename string) error {
	if this.file != nil {
		this.file.Close()
	}

	var err error
	this.file, err = os.OpenFile(filename, os.O_CREATE|os.O_APPEND|os.O_WRONLY, os.ModePerm)
	return err
}

func (this *FileLog) getNextTimer() *time.Timer {
	if this.shiftType == LOGSHIFT_TYPE_HOUR {
		return time.NewTimer(time.Hour)
	} else if this.shiftType == LOGSHIFT_TYPE_DAY {
		return time.NewTimer(time.Hour * 24)
	} else {
		return time.NewTimer(time.Minute)
	}
}

//时间，缓冲区大小，条数
func (this *FileLog) asyncFlush() {
	defer this.wg.Done()

	tickerFlush := time.NewTicker(time.Second)
	for {
		select {
		case <-this.quitChan:
			this.Flush()
			//TODO
		case <-tickerFlush.C:
			this.Flush()
		case content, ok := <-this.writeChan:
			if ok {
				this.writeBuffer.WriteString(content + "\n")
				if this.writeBuffer.Len() > FlushSize {
					this.Flush()
				}
			}
		}
	}
}

//将缓冲区的文件内容输出到文件
func (this *FileLog) Flush() {

	if this.writeBuffer.Len() == 0 {
		return
	}

	//无论是否写成功都丢掉
	defer this.writeBuffer.Reset()

	file, err := this.getFileHandler()
	if err != nil || file == nil {
		return
	}

	//直接写byte ,少一步处理
	_, err = file.Write(this.writeBuffer.Bytes())
	if err != nil {
		fmt.Println("write err :", err.Error())
	}
	//this.file.WriteString(this.writeBuffer.String())
}

func (this *FileLog) getFileHandler() (*os.File, error) {

	logFileName := this.getLogfileName()
	if logFileName != this.curLogFileName {
		this.fileMutext.Lock()
		defer this.fileMutext.Unlock()
		err := this.reopen(logFileName)
		if err != nil {
			return nil, err
		}
		this.curLogFileName = logFileName
	}

	//判断是否需要换文件
	return this.file, nil
}

//判断文件路径是否合法
func checkFilePath(logPath string) {
	if err := os.MkdirAll(logPath, os.ModePerm); err != nil {
		fmt.Println("er:", err.Error())
	}
}

func (this *FileLog) getLogfileName() string {
	return fmt.Sprintf("%s%s.log", this.logPath, this.logName)
}
