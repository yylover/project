package flog

type LOGLEVEL int
type SHIFT_TYPE int

const (
	LOGSHIFT_TYPE_SIZE SHIFT_TYPE = iota
	LOGSHIFT_TYPE_DAY
	LOGSHIFT_TYPE_HOUR
	LOGSHIFT_TYPE_MINUTE

	LOGLEVEL_DEBUG LOGLEVEL = iota
	LOGLEVEL_INFO
	LOGLEVEL_WARN
	LOGLEVEL_ERROR
	LOGLEVEL_FATAL
)

type Logger interface {
	Debug(format string, v ...interface{})
	Info(format string, v ...interface{})
	Warn(format string, v ...interface{})
	Error(format string, v ...interface{})
	Fatal(format string, v ...interface{})
	Close()
}
