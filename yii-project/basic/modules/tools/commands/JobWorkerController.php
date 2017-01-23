<?php
namespace app\modules\tools\commands;

use Pheanstalk\Pheanstalk;
use yii\console\Controller;

class JobWorkerController extends Controller
{

    public function actionIndex()
    {
        $callback = function ($msg) {
            var_dump($msg);
            return true;
        };

        try {
            (new BeanstalkWatcher("127.0.0.1", "11300", ['testtube'], $callback))->loop();
        } catch (\Exception $e) {
            var_dump($e->getMessage());
        }
    }
}
