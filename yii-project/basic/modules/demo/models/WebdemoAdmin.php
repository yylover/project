<?php

namespace app\modules\demo\models;

use Yii;

/**
 * This is the model class for table "webdemo_admin".
 *
 * @property integer $admin_id
 * @property string $admin_name
 * @property string $admin_password
 */
class WebdemoAdmin extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'webdemo_admin';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['admin_name', 'admin_password'], 'required'],
            [['admin_name', 'admin_password'], 'string', 'max' => 32],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'admin_id' => 'Admin ID',
            'admin_name' => 'Admin Name',
            'admin_password' => 'Admin Password',
        ];
    }
}
