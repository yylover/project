<?php

namespace app\modules\demo\controllers;

use yii\web\Controller;
use yii\filters\VerbFilter;
use yii;
use app\modules\demo\models\Foo;

/**
 * Default controller for the `demo` module
 */
class KeyconceptController extends Controller
{

    public function actionEvents()
    {
        $foo = new Foo;
        $foo->on(Foo::EVENT_HELLO, [$foo, "helloHandle"]);
        $this->trigger(Foo::EVENT_HELLO);
    }
}
