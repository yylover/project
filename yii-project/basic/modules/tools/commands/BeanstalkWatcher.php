<?php

namespace app\modules\tools\commands;

use Pheanstalk\Pheanstalk;

class BeanstalkWatcher
{
    const TIMEOUNT_RESERVE = 10;

    private $host;
    private $port;
    private $callback;
    private $tubes;

    public function __construct($host, $port, $tubes, $callback)
    {
        $this->host = $host;
        $this->port = $port;
        $this->tubes = $tubes;
        $this->callback = $callback;
    }

    public function loop()
    {
        $pheanstalk = new Pheanstalk($this->host, $this->port);
        foreach ($this->tubes as $key => $value) {
            $pheanstalk->watch($value);
        }
        $pheanstalk->ignore("default");

        $count = 0;
        while (true) {
            if (!$pheanstalk->getConnection()->isServiceListening()) {
                var_dump("connection corrupt");
                break;
            }

            $job = $pheanstalk->reserve(BeanstalkWatcher::TIMEOUNT_RESERVE);
            if ($job) {
                $encoding = mb_detect_encoding($job->getData(), 'UTF-8', true);
                if ($encoding !== "UTF-8" && $encoding !== 'ASCII') {
                    $pheanstalk->delete($job);
                    continue;
                }

                $data = json_decode($job->getData(), true);
                if ($data === null) {
                    $pheanstalk->delete($job);
                    \Yii::info("data is not json");
                    continue;
                }

                if (call_user_func($this->callback, $data)) {
                    $pheanstalk->delete($job);
                }
            }
        }
    }
}
