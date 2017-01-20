
## 入口脚本
1. web 入口脚本:
Web 应用的入口脚本必须放在终端用户能够访问的目录下， 通常命名为 index.php

2. 控制台应用的入口脚本一般在应用根目录下命名为 yii（后缀为.php）,需要添加可执行权限

入口脚本的主要工作:
    1. 定义全局变量
    2. 注册Composer自动加载器
    3. 包含Yii类库文件
    4. 创建应用实例并配置
    5. 运行应用实例

3. 定义常量
    yii 支持三个常量

    YII_DEBUG:是否调试模式
    YII_ENV:标识运行环境，默认'prod'
    YII_ENABLE_ERROR_HANDLER: 是否启用错误处理，默认为true

## 应用主体

1. 应用主题全局唯一，并且在入口脚本创建。\Yii::$app在全局访问。
2.


## 应用组件

1. 应用主体是服务定位器,它部署一组提供各种不同功能的应用组件来处理请求。
2. 每个应用组件都有一个独一无二的 ID 用来区分其他应用组件
\Yii::$app->componentID
3. 第一次使用以上表达式时候会创建应用组件实例， 后续再访问会返回此实例。
```
[
    'components' => [
        // 使用类名注册 "cache" 组件
        'cache' => 'yii\caching\ApcCache',

        // 使用配置数组注册 "db" 组件
        'db' => [
            'class' => 'yii\db\Connection',
            'dsn' => 'mysql:host=localhost;dbname=demo',
            'username' => 'root',
            'password' => '',
        ],

        // 使用函数注册"search" 组件
        'search' => function () {
            return new app\components\SolrService;
        },
    ],
]
```
4. 核心应用组件

## 控制器Controller

1. 路由：ModuleID/ControllerID/ActionID
2.

## model
### 1. 属性
1. 模型通过 属性 来代表业务数据，每个属性像是模型的公有可访问属性。 yii\base\Model::attributes()
指定模型拥有的属性。
2. 属性可以通过ArrayAccess ArrayIterator方式访问。
```
model = new \app\models\ContactForm;

// 像访问数组单元项一样访问属性
$model['name'] = 'example';
echo $model['name'];

// 迭代器遍历模型
foreach ($model as $name => $value) {
    echo "$name: $value\n";
}
```
3. 定义
```
#方式1：直接定义:
public $name;

#方式2，通过attributes()来定义属性，然后重写_get _set魔术方法。
```
4. 属性标签
```
public function attributeLabels()
{
    return [
        'name' => 'Your name',
        'email' => 'Your email address',
        'subject' => 'Subject',
        'body' => 'Content',
    ];
}
public function attributeLabels()
{
    return [
        'name' => \Yii::t('app', 'Your name'),
        'email' => \Yii::t('app', 'Your email address'),
        'subject' => \Yii::t('app', 'Subject'),
        'body' => \Yii::t('app', 'Content'),
    ];
}
```
5. 场景
```
// 场景作为属性来设置
$model = new User;
$model->scenario = 'login';

// 场景通过构造初始化配置来设置
$model = new User(['scenario' => 'login']);
```
6. 验证规则

7. 块赋值
```
$model = new \app\models\ContactForm;
$model->attributes = \Yii::$app->request->post('ContactForm');

```

8. 安全属性：不需要验证
```
public function scenarios()
{
    return [
        'login' => ['username', 'password'],
        'register' => ['username', 'email', 'password'],
    ];
}
#或者
public function rules()
{
    return [
        [['title', 'description'], 'safe'],
    ];
}

```

9. 非安全属性
```
public function scenarios()
{
    return [
        'login' => ['username', 'password', '!secret'],
    ];
}
public function rules()
{
    return [
        [['username', 'password', '!secret'], 'required', 'on' => 'login']
    ];
}
#两种方式都可以，这种情形下，必须通过明确赋值才可以，块赋值不能赋值。
#$model->secret = $secret;
```

10. 数据导出:
```
$post = \app\models\Post::findOne(100);
$array = $post->attributes;

#方式2
yii\base\Model::toArray() 方法
```
11. 字段
fields() 来增加、删除、重命名和重定义字段，

```
$array = $model->toArray([], ['prettyName', 'fullAddress']);
public function fields()
{
    return [
        // 字段名和属性名相同
        'id',
        // 字段名为 "email"，对应属性名为 "email_address"
        'email' => 'email_address',
        // 字段名为 "name", 值通过PHP代码返回
        'name' => function () {
            return $this->first_name . ' ' . $this->last_name;
        },
    ];
}
```

### 视图
??

### 模块


### 过滤器
过滤器是动作之前或之前要执行的对象。

核心过滤器

### widget
小部件是在 视图 中使用的可重用单元， 使用面向对象方式创建复杂和可配置用户界面单元。
??
###
