<?php

namespace app\modules\tools;

/**
 * tools module definition class
 */
class Tools extends \yii\base\Module
{
    /**
     * @inheritdoc
     */
    public $controllerNamespace = 'app\modules\tools\controllers';

    /**
     * @inheritdoc
     */
    public function init()
    {
        parent::init();

        // custom initialization code goes here
        if (\Yii::$app instanceof \yii\console\Application) {
            $this->controllerNamespace = 'app\modules\tools\commands';
        }
    }
}
