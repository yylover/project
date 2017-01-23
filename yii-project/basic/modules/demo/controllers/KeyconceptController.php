<?php

namespace app\modules\demo\controllers;

use yii;
use yii\web\Controller;
use yii\filters\VerbFilter;
use app\modules\demo\models\Foo;
use app\modules\demo\logic\DbCommandQueryLogic;
use app\modules\demo\logic\DbQueryBuilderLogic;
use app\modules\demo\models\WebdemoAdmin;

/**
 * Default controller for the `demo` module
 */
class KeyconceptController extends Controller
{

    public function actionEvents()
    {
        $foo = new Foo;
        $foo->on(Foo::EVENT_HELLO, [$foo, "helloHandle"]);
        $foo->trigger(Foo::EVENT_HELLO);
    }

    public function actionTest()
    {
        // (new WebdemoAdminLogic)->test();
        // (new WebdemoAdminLogic)->dbQuery();
        (new DbCommandQueryLogic)->bindParams();
        // $logic = new WebdemoAdminLogic;
        // $one = WebdemoAdmin::findOne(1);
        // var_dump($one->attributes());
    }

    public function actionQueryBuilder()
    {
        $logic = new DbQueryBuilderLogic;
    }
}
