
## 测试依赖
### 断言测试
```
$this->assertEquals('value', 'response-value');
$this->assertEmpty($arr); #null [] 都是true
```

### 依赖测试

1. 函数之间有依赖关系的，要进行依赖测试
@depends

2. 当某个测试所依赖的测试失败时，PHPUnit 会跳过这个测试。

3. 多重依赖测试
一个测试函数对多个函数的输入有依赖关系，使用多个@depends

## 数据提供器

1. 测试方法可以接受任何参数，@dataProvider标明使用哪个提供器。返回值要么是一个数组，每个元素也是数组。
要么是实现了Iterator接口的对象。
2. 带有大量的数据集测试时，可以指定键名。
3. 可以同时使用@depends @dataProvider来获取数据



## 异常测试

expectException()
expectExceptionCode()
expectExceptionMessage()
expectExceptionMessageRegExp()

@expectException
@expectExceptionCode
@expectExceptionMessage
@expectExceptionMessageRegExp


## php错误测试
1. PHPUnit 将测试在执行中触发的 PHP 错误、警告、通知都转换为异常。利用这些异常进行错误测试。
2. 利用@抑制错误提示，对返回值进行判断
$this->assertFalse(@$writer->write('/is-not-writeable/file', 'stuff'));

## 输出测试

expectOutputString();
void expectOutputRegex(string $regularExpression)
bool setOutputCallback(callable $callback)

## 基境
protected function setUp()
protected function tearDown()
public static function setUpBeforeClass()
public static function tearDownAfterClass()

##
