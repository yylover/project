<?php

namespace app\modules\demo\models;

use yii\base\Model;

class ContactForm extends Model
{
    #定义属性
    public $name;
    public $email;
    public $subject;
    public $body;

    #属性标签
    public function attributeLabels()
    {
        return [
            'name' => 'Your name',
            'email' => 'Your email address',
            'subject' => 'Subject',
            'body' => 'Content',
        ];
    }

    #场景
    const SCENARIO_LOGIN = 'login';
    const SCENARIO_REGISTER = 'register';
    public function scenarios()
    {
        $scenarios = parent::scenarios();
        $scenarios[self::SCENARIO_LOGIN] = ['username', 'password'];
        $scenarios[self::SCENARIO_REGISTER] = ['username', 'email', 'password'];
        return $scenarios;
    }

    #验证规则
    public function rules()
    {
        return [
            // name, email, subject 和 body 属性必须有值
            [['name', 'email', 'subject', 'body'], 'required'],
            #使用场景
            [['username', 'password'], 'required', 'on' => 'login'],

            // email 属性必须是一个有效的电子邮箱地址
            ['email', 'email'],
        ];
    }
}
