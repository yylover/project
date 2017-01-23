<?php

namespace app\modules\tools\controllers;

use yii\web\Controller;
use app\modules\tools\logic\Beanstalk;

/**
 * Default controller for the `tools` module
 */
class DefaultController extends Controller
{
    /**
     * Renders the index view for the module
     * @return string
     */
    public function actionIndex()
    {
        return $this->render('index');
    }

    public function actionTest()
    {
        $beanstalk = new Beanstalk;
        // $beanstalk->reserveJobs();
        $beanstalk->putJobs();
    }
}
