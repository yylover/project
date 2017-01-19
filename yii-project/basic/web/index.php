<?php

// comment out the following two lines when deployed to production
// 全局变量
defined('YII_DEBUG') or define('YII_DEBUG', true);
defined('YII_ENV') or define('YII_ENV', 'dev');

require(__DIR__ . '/../vendor/autoload.php');#composer 自动加载器
require(__DIR__ . '/../vendor/yiisoft/yii2/Yii.php'); #yii 类库文件

$config = require(__DIR__ . '/../config/web.php'); #全局配置

(new yii\web\Application($config))->run();# 运行应用实例
