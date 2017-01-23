<?php
namespace app\modules\tools\logic;

use Pheanstalk\Pheanstalk;

class Beanstalk
{
    private $pheanstalk;
    public function __construct()
    {
        $this->pheanstalk = new Pheanstalk('127.0.0.1');
    }

    public function putJobs()
    {
        if ($this->pheanstalk->getConnection()->isServiceListening()) {
            $this->pheanstalk
              ->useTube('testtube')
              ->put(json_encode(["data" => "hello this is payload"]));
        } else {
            echo "connection 断开了";
        }
    }

    public function reserveJobs()
    {
        if ($this->pheanstalk->getConnection()->isServiceListening()) {
            $job = $this->pheanstalk
              ->watch('testtube')
              ->ignore('default')
              ->reserve();
            sleep(20);
            echo $job->getData();
        } else {
            echo "connection 断开";
        }
    }
}
