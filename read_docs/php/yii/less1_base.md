### 安装yii

验证安装:
php yii serve
php yii serve --port=9999

#### 配置web服务器

1. 将basic/web设置为根目录，防止终端用户访问应用代码和敏感数据文件。

2. Apache配置

3. nginx 配置
    ？

####

1. Yii 使用 action 前缀区分普通方法和操作。 action 前缀后面的名称被映射为操作的 ID。操作 ID create-comment 相当于方法名 actionCreateComment

2. 操作和视图的对应

say 视图应该存为 views/site/say.php 文件。当一个操作中调用了 yii\web\Controller::render() 方法时， 它将会按 views/控制器 ID/视图名.php 路径加载 PHP 文件。

3. 基本模型类 \yii\base\Model
    * yii\base\Model 被用于普通模型类的父类并与数据表无关。yii\db\ActiveRecord 通常是普通模型类的父类但与数据表有关联（译注：yii\db\ActiveRecord 类其实也是继承自 yii\base\Model，增加了数据库处理）。
    * Yii::$app 代表应用实例， 它是一个全局可访问的单例。同时它也是一个服务定位器， 能提供 request，response，db 等等特定功能的组件。 在上面的代码里就是使用 request 组件
    *
