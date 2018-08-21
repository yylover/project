package flog

type EmptyLogger struct {
}

func (el *EmptyLogger) Debug(format string, v ...interface{}) {}
func (el *EmptyLogger) Info(format string, v ...interface{})  {}
func (el *EmptyLogger) Warn(format string, v ...interface{})  {}
func (el *EmptyLogger) Error(format string, v ...interface{}) {}
func (el *EmptyLogger) Fatal(format string, v ...interface{}) {}
func (el *EmptyLogger) Close()                                {}

type StdLogger struct {
}

func (el *StdLogger) Debug(format string, v ...interface{}) {}
func (el *StdLogger) Info(format string, v ...interface{})  {}
func (el *StdLogger) Warn(format string, v ...interface{})  {}
func (el *StdLogger) Error(format string, v ...interface{}) {}
func (el *StdLogger) Fatal(format string, v ...interface{}) {}
func (el *StdLogger) Close()                                {}
