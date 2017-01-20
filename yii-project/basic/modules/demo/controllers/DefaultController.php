<?php

namespace app\modules\demo\controllers;

use yii\web\Controller;
use yii\filters\VerbFilter;
use yii;

/**
 * Default controller for the `demo` module
 */
class DefaultController extends Controller
{

    // public function behaviors()
    // {
    //     return [
    //         'verbs' => [
    //             'class' => VerbFilter::className(),
    //             'actions' => [
    //                 'test'  => ['post'],
    //                 'view'   => ['get'],
    //                 'create' => ['get', 'post'],
    //                 'update' => ['get', 'put', 'post'],
    //                 'delete' => ['post', 'delete'],
    //             ],
    //         ],
    //     ];
    // }
    /**
     * Renders the index view for the module
     * @return string
     */
    public function actionIndex()
    {
        return $this->render('index');
    }

    public function actionRequestTest()
    {
        //GET
        $request = Yii::$app->request;
        $get     = $request->get();
        $rule    = $request->get("rule", null);
        $server  = $request->get("server", null);

        //POST
        $post    = $request->post();
        $rule    = $request->post("rule", null);
        $server  = $request->post("server", null);

        //返回所有参数
        $params = $request->bodyParams;
        $rule   = $request->getBodyParam("rule", null);

        #当前请求的方法 string
        $method = Yii::$app->request->method;
        echo $request->isAjax;
        echo $request->isGet;
        echo $request->isPost;
        echo $request->isPut;

        #请求urls
        #http://example.com/admin/index.php/product?id=100
        echo $request->url;  #/admin/index.php/product?id=100
        echo $request->absoluteUrl; #http://example.com/admin/index.php/product?id=100
        echo $request->hostInfo;   #http://example.com/
        echo $request->pathInfo;   #/product
        echo $request->queryString;#id=100
        echo $request->baseUrl;    #/admin
        echo $request->scriptUrl;  #/admin/index.php
        echo $request->serverName; #example.com
        echo $request->serverPort; # 80

        #http headers
        $headers = Yii::$app->request->headers;
    }

    public function actionResponseTest()
    {
        #普通状态码
        Yii::$app->response->statusCode = 200;

        #其他状态码通过跑出异常
        //throw new \yii\web\NotFoundHttpException; #404
        // yii\web\BadRequestHttpException: status code 400.
        // yii\web\ConflictHttpException: status code 409.
        // yii\web\ForbiddenHttpException: status code 403.
        // yii\web\GoneHttpException: status code 410.
        // yii\web\MethodNotAllowedHttpException: status code 405.
        // yii\web\NotAcceptableHttpException: status code 406.
        // yii\web\NotFoundHttpException: status code 404.
        // yii\web\ServerErrorHttpException: status code 500.
        // yii\web\TooManyRequestsHttpException: status code 429.
        // yii\web\UnauthorizedHttpException: status code 401.
        // yii\web\UnsupportedMediaTypeHttpException: status code 415.

        #创建 http Exception
        #throw new \yii\web\HttpException(402);

        #http 头部大小写敏感
        $headers = Yii::$app->response->headers;
        // 增加一个 Pragma 头，已存在的Pragma 头不会被覆盖。
        $headers->add('Pragma', 'no-cache');
        // 设置一个Pragma 头. 任何已存在的Pragma 头都会被丢弃
        $headers->set('Pragma', 'no-cache');
        // 删除Pragma 头并返回删除的Pragma 头的值到数组
        $values = $headers->remove('Pragma');


        #响应主体
        $response = Yii::$app->response;
        $response->format = \yii\web\Response::FORMAT_JSON;
        $response->data = ['message' => 'hello world'];

        #浏览器跳转
        #\Yii::$app->response->redirect('http://example.com/new', 301)->send();

        #文件发送
        # return \Yii::$app->response->sendFile('path/to/file.txt');

        #
    }

    public function actionSessionCookie()
    {
        $session = Yii::$app->session;

        // 检查session是否开启
        echo $session->isActive ?  "session is alive" : "session is not alive";
        // 开启session, session is alive
        $session->open();
        // 关闭session, session is not alive
        $session->close();
        // 销毁session中所有已注册的数据
        $session->destroy();

        #session 操作
        $session->set("key", 3);  #set
        $session->get("key"); # get
        $session->remove("key"); # remove
        $session->has("key");  #boolean

        #sessin值为数组时，单独修改一个无效
        #// 如下代码不会生效
        #$session['captcha']['number'] = 5;
        #$session['captcha']['lifetime'] = 3600;
        $session['captcha'] = new \ArrayObject;
        $session['captcha']['number'] = 5;
        $session['captcha']['lifetime'] = 3600;
        #带前缀的键存储
        $session['captcha.number'] = 5;
        $session['captcha.lifetime'] = 3600;

        var_dump($session["captcha.number"]);

        $session = Yii::$app->session;

        // 设置一个名为"postDeleted" flash 信息
        $session->setFlash('postDeleted', 'You have successfully deleted your post.');
        // 请求 #2
        // 显示名为"postDeleted" flash 信息
        echo $session->getFlash('postDeleted');
        // 请求 #3
        // $result 为 false，因为flash信息已被自动删除
        $result = $session->hasFlash('postDeleted');


        ## cookie
        ## 读取cookie
        $cookies = Yii::$app->request->cookies;
        $language = $cookies->getValue('language', 'en');
        echo $language;

        ## 设置cookie
        $cookies = Yii::$app->response->cookies;
        $cookies->add(new \yii\web\Cookie([
            'name' => 'name',
            'value' => 'yang',
        ]));
    }


    public function actionErrorhandle()
    {
        try {
            10/0;
        } catch (\ErrorException $e) {
            var_dump($e->getMessage());
            Yii::warning("Division by zero.");
        }
    }

    public function actionLog()
    {
        // Yii::trace('start calculating average revenue', __METHOD__);
        Yii::error('start calculating average revenue', "test");
    }

}
