<?php

namespace app\modules\control\controllers;

use yii\web\Controller;

/**
 * Default controller for the `control` module
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
        echo "Default Controller";
    }
}
