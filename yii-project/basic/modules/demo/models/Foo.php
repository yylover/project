<?php

namespace app\modules\demo\models;

use yii\base\Model;

class Foo extends Model
{
    const EVENT_HELLO = "event_hello";

    public function helloHandle($event)
    {
        echo "Hello event";
    }

    ##属性
    ##getter setter方法
    private $label;

    public function getLabel()
    {
        return $this->label;
    }

    public function setLabel($label)
    {
        $this->label = trim($label);
    }
}
