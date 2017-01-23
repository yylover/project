<?php
namespace app\modules\demo\logic;

use yii;
use app\modules\demo\models\WebdemoAdmin;

/**
 *
 */
class DbCommandQueryLogic
{

    public function __construct()
    {
        # code...
    }

    public function test()
    {
        $one = WebdemoAdmin::findOne(1);
        var_dump($one->attributes());
    }

    /**
     * 数据库查询
     * @return [type] [description]
     */
    public function dbQuery()
    {
        //queryAll
        $all = Yii::$app->db->createCommand("select * from webdemo_admin")->queryAll();
        var_dump($all);

        //queryOne
        $user = Yii::$app->db->createCommand('SELECT * FROM webdemo_admin WHERE admin_id=1')
           ->queryOne();
        var_dump($user);

        //queryColumn
        $titles = Yii::$app->db->createCommand('SELECT admin_name FROM webdemo_admin')
            ->queryColumn();
        var_dump($titles);

        //queryScalar
        $count = Yii::$app->db->createCommand('SELECT COUNT(*) FROM webdemo_admin')
             ->queryScalar();
        var_dump($count);
    }

    /**
     * 参数绑定
     * bindValue
     * bindValues
     * bindParam
     * @return [type] [description]
     */
    public function bindParams()
    {
        //bindValue
        $user = Yii::$app->db
            ->createCommand('SELECT * FROM webdemo_admin WHERE admin_id=:id and admin_name=:admin_name')
            ->bindValue(":id", 1)
            ->bindValue("admin_name", 'user')
            ->queryOne();
        var_dump($user);

        //bindValues
        $values = [':id' => 1, 'admin_name' => 'user'];
        $user = Yii::$app->db
            ->createCommand('SELECT * FROM webdemo_admin WHERE admin_id=:id and admin_name=:admin_name')
            ->bindValues($values)
            ->queryOne();
        var_dump($user);

        //createCommand values
        $values = [':id' => 1, 'admin_name' => 'user'];
        $user = Yii::$app->db
            ->createCommand('SELECT * FROM webdemo_admin WHERE admin_id=:id and admin_name=:admin_name', $values)
            ->queryOne();
        var_dump($user);

        //复用commands
        $command = Yii::$app->db
            ->createCommand('SELECT * FROM webdemo_admin WHERE admin_id=:id');
        $user1 = $command->bindValue(":id", 1)->queryOne();
        $user2 = $command->bindValue(":id", 2)->queryOne();
        print_r($user1);
        print_r($user2);

        //update return 修改的行数
        Yii::$app->db->createCommand("UPDATE webdemo_admin SET admin_name='want' WHERE admin_id=2")->execute();

        //使用insert update delete 方法
        $res = Yii::$app->db->createCommand()
            ->insert("webdemo_admin", ['admin_name' => "zhao", "admin_password" => '65432'])
            ->execute();

        //update(talbe, values, condition)
        $res = Yii::$app->db->createCommand()
            ->update("webdemo_admin", ["admin_password" => '654321'], ["admin_name" => "zhao"])
            ->execute();
        var_dump($res);

        //delete
        $res = Yii::$app->db->createCommand()
            ->delete("webdemo_admin", ["admin_id" => 3])
            ->execute();

        //批量插入batchInsert
        Yii::$app->db->createCommand()->batchInsert('webdemo_admin', ['admin_name', 'admin_password'], [
            ['Tom', 30],
            ['Jane', 20],
            ['Linda', 25],
        ])->execute();

        //事务操作
        Yii::$app->db->transaction(function ($db) {
            $db->createCommand($sql1)->execute();
            $db->createCommand($sql2)->execute();
        });

        $db = Yii::$app->db;
        $transaction = $db->beginTransaction();
        try {
            $db->createCommand($sql1)->execute();
            $db->createCommand($sql2)->execute();

            $transaction->commit();
        } catch (\Exception $e) {
            $transaction->rollBack();

            throw $e;
        }
    }
}
