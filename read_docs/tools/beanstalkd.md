


#


   put            reserve               delete
  -----> [READY] ---------> [RESERVED] --------> *poof*


put with delay               release with delay
 ----------------> [DELAYED] <------------.
                       |                   |
                       | (time passes)     |
                       |                   |
  put                  v     reserve       |       delete
 -----------------> [READY] ---------> [RESERVED] --------> *poof*
                      ^  ^                |  |
                      |   \  release      |  |
                      |    `-------------'   |
                      |                      |
                      | kick                 |
                      |                      |
                      |       bury           |
                   [BURIED] <---------------'
                      |
                      |  delete
                       `--------> *poof*

注：如果consumer仅仅reserve一个job,处理完没有delete,那么任务仍然回到ready状态。

### 命令

#### put
put <pri> <delay> <ttr> <bytes>\r\n
<data>\r\n
--- pri (0~ 2^32), 0优先级最大，默认1024
--- delay 等待的秒数，首先进入delayed状态
--- ttr 运行时间，从reserve开始计时，如果client在此时间没有delete,release,bury操作，将自动release
--- bytes: job body大小
--- data : job body

#### use
use <tube>\r\n
--- tube 最大200字节

#### reserve
reserve\r\n
reserve-with-timeout <seconds>\r\n

#### delete 删除
delete <id>\r\n

#### release
release <id> <pri> <delay>\r\n

#### bury 休眠队列
bury <id> <pri>\r\n

#### touch 表明正在处理任务，请求更多时间
touch <id>\r\n

#### watch 添加tube进观察队列
watch <tube>\r\n

#### ignore 从观察队列中删除tube
ignore <tube>\r\n

#### kick
kick count\r\n #注意：仅对当前tube有效

#### stats-job
stats-job <id> #查看某个job的状态。
stats-tube <tube>\r\n
stats\r\n #系统的统计信息
list-tubes\r\n #查看所有的tube
list-tube-used\r\n #查看正在使用的tube
