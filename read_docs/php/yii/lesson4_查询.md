

### 数据库查询器
建立在数据库Database access object(DAO)之上，相比较原生，具有可读性强，安全性高等特点。
```
$rows = (new \yii\db\Query())
    ->select(['id', 'email'])
    ->from('user')
    ->where(['last_name' => 'Smith'])
    ->limit(10)
    ->all();

    //select
    $query->select(['id', 'email']);
    $query->select('id, email');  #[]与字符串写法相同，但是如果中间用来函数，就必须用数组写法
    $query->select(["CONCAT(first_name, ' ', last_name) AS full_name", 'email']);
    $query->select(['user.id AS user_id', 'email']); #AS
    $query->select(['user_id' => 'user.id', 'email']);#使用数组指定别名
    $query->select('*'); #查询所有字段

    //from 指定表名
    $query->from('user');
    $query->from(['public.user u', 'public.post p']);
    $query->from(['u' => 'public.user', 'p' => 'public.post']); #键名指定别名
    //查询子查询
    $subQuery = (new Query())->select('id')->from('user')->where('status=1');
    $query->from(['u' => $subQuery]);

    //where条件,三种方式:,哈希格式:,
    //1. 字符串'status=1',但是千万不能直接嵌入变量，会造成SQL注入攻击
    $query->where('status=:status', [':status' => $status]);
    $query->where('YEAR(somedate) = 2015');
    //2. 哈希格式 ['status' => 1, 'type' => 2]
    $query->where([
        'status' => 10,
        'type' => null,
        'id' => [4, 8, 15],
    ]);
    //3. 操作符格式 ['like', 'name', 'test'] 允许指定任意格式的
    //and or between not between, in, not in, like, or like, not like, or not like,
    //exists, not exists, >, <=
    //附加条件 andWhere orWhere
    //过滤条件，将忽略空值filterWhere andFilterCompare

    //distinct orderBy addOrderBy groupBy addGroupBy having limit offset join|innerJoin
    //leftJoin|rightJoin union
    $query->select('user_id')->distinct();#distinct 去掉重复行
    $query->select('user_id')->addSelect('name');
    $query->orderBy([
        'id' => SORT_ASC,
        'name' => SORT_DESC,
    ]);
    $query->groupBy(['id', 'status']);
    $query->having(['status' => 1]);
    $query->limit(10)->offset(20);
    $query->join('LEFT JOIN', 'post', 'post.user_id = user.id');
    $query1->union($query2);

    //查询方法
    //all() one() column() scalar() exists() count() createCommand() 查看sql语句


    //索引查询结果
    $query = (new \yii\db\Query())
        ->from('user')
        ->indexBy(function ($row) {
            return $row['id'] . $row['username'];
        })->all();

    //批量处理,batch each 返回实现了Iterator接口的BatchQueryResult对象
    $query = (new \yii\db\Query())
        ->from('user')
        ->indexBy('username');

    foreach ($query->batch() as $users) {
        // $users 的 “username” 字段将会成为索引
    }

    foreach ($query->each() as $username => $user) {
    }
```

### ActiveRecord
1. 构建查询find findBySql 返回yii\db\ActiveQuery 实例，
```
$customers = Customer::find()
    ->where(['status' => Customer::STATUS_ACTIVE])
    ->orderBy('id')
    ->all();

$count = Customer::find()
    ->where(['status' => Customer::STATUS_ACTIVE])
    ->count();
```
2. 批量获取数据

3. 关联查询
```
yii\db\ActiveRecord::hasMany() 和 yii\db\ActiveRecord::hasOne()
public function getOrders()
{
    // 客户和订单通过 Order.customer_id -> id 关联建立一对多关系
    return $this->hasMany(Order::className(), ['customer_id' => 'id']);
}
# 如果是多对多的关系，中间有一个关系表连接起来
public function getItems()
{
    return $this->hasMany(Item::className(), ['id' => 'item_id'])
        ->viaTable('order_item', ['order_id' => 'id']);
}
```

4. 延迟加载和即时加载
with

5. 定义逆关系
