<?php
namespace app\modules\demo\logic;

use yii;
use app\modules\demo\models\WebdemoAdmin;

/**
 * ActiveRecord 提供提供了一个面向对象的接口， 用以访问数据库中的数据。一个 AR 类关联一张数据表， 每个 AR 对象对应表中的一行。需要extends ActiveRecord
 */
class ActiveRecordQueryLogic
{

    /**
     * @return string 返回该AR类关联的数据表名
     */
    public static function tableName()
    {
        return 'customer';
    }

    /**
     * 如果用了不止一个数据库，需要覆盖getDb方法。
     * @return [type] [description]
     */
    public static function getDb()
    {
        return \Yii::$app->db2;  // 使用名为 "db2" 的应用组件
    }

    /**
     * 用户设置Model的默认值
     * @return [type] [description]
     */
    public function loadDefaultValues()
    {
    }

    /**
     * 关联查询
     * @return [type] [description]
     */
    public function getOrders()
    {
        // 客户和订单通过 Order.customer_id -> id 关联建立一对多关系
        return $this->hasMany(Order::className(), ['customer_id' => 'id']);

        //逆关系
        return $this->hasMany(Order::className(), ['customer_id' => 'id'])->inverseOf('customer');
    }

    /**
     * 关联查询加条件
     * @param  integer $threshold [description]
     * @return [type]             [description]
     */
    public function getBigOrders($threshold = 100)
    {
        return $this->hasMany(Order::className(), ['customer_id' => 'id'])
            ->where('subtotal > :threshold', [':threshold' => $threshold])
            ->orderBy('id');
    }


    /**
     * 数据库查询
     * @return [type] [description]
     */
    public function dbQuery()
    {
        //findOne findAll 返回一组AR实例
        $customer = Customer::findOne(1);
        $customers = Customer::findAll([1, 2, 3]);

        //数组形式获取数据asArray
        $customers = Customer::find()
            ->asArray()
            ->all();

        //批量获取数据
        // 一次提取 10 个客户信息
        foreach (Customer::find()->batch(10) as $customers) {
            // $customers 是 10 个或更少的客户对象的数组
        }
        // 一次提取 10 个客户并一个一个地遍历处理
        foreach (Customer::find()->each(10) as $customer) {
            // $customer 是一个 ”Customer“ 对象
        }
        // 贪婪加载模式的批处理查询
        foreach (Customer::find()->with('orders')->each() as $customer) {
        }

        //操作数据save update delete deleteAll() updateAll updateCounters
        // 插入新客户的记录
        $customer = new Customer();
        $customer->name = 'James';
        $customer->save();

        $customer = Customer::findOne($id);
        $customer->email = 'james@example.com';
        $customer->save();  // 等同于 $customer->update();

        $customer = Customer::findOne($id);
        $customer->delete();

        // 删除多个年龄大于20，性别为男（Male）的客户记录
        Customer::deleteAll('age > :age AND gender = :gender', [':age' => 20, ':gender' => 'M']);

        // 所有客户的age（年龄）字段加1：
        Customer::updateAllCounters(['age' => 1]);
    }

    public function lazyQuery()
    {
        //延迟加载的例子
        $customer = Customer::findOne(1);
        // SQL executed: SELECT * FROM order WHERE customer_id=1
        $orders = $customer->orders;
        // 没有 SQL 语句被执行
        $orders2 = $customer->orders;

        //即时加载
        $customers = Customer::find()->limit(100)
            ->with('orders')->all();

        //自定义
        $customers = Customer::find()->limit(100)->with([
            'orders' => function ($query) {
                $query->andWhere('subtotal>100');
            },
        ])->all();
    }
}
