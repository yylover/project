<?php
namespace app\modules\demo\tests;

use PHPUnit\Framework\TestCase;
use app\modules\demo\tests\CsvFileIterator;

require "CsvFileIterator.php";

/**
 * 基本单元测试：
 * 断言函数，依赖，
 * $this->assertEquals('value', 'response-value');
 * $this->assertEmpty();
 */
class StackTest extends TestCase
{
    /**
     * 1. 断言测试
     * $this->assertEquals('value', 'response-value');
     */
    public function testPushandPop()
    {
        $arr = [];
        $this->assertEquals(0, count($arr));

        array_push($arr, "foo");
        $this->assertEquals('foo', $arr[count($arr) - 1]);
        $this->assertEquals(1, count($arr));

        $this->assertEquals('foo', array_pop($arr));
        $this->assertEquals(0, count($arr));
    }

    /**
     * 2. 依赖测试
     */
    public function testOneEmpty()
    {
        $stack = [];
        $this->assertEmpty($stack);

        return $stack;
    }

    /**
     * 测试array push
     * @param array $stack
     * @depends testOneEmpty
     */
    public function testTwoPush($stack)
    {
        array_push($stack, "foo");
        $this->assertEquals('foo', $stack[count($stack) - 1]);
        $this->assertEquals(1, count($stack));
        return $stack;
    }

    /**
     * 测试arrayPop
     * @param array $stack
     * @depends testTwoPush
     */
    public function testThreePop($stack)
    {
        $this->assertEquals('foo', array_pop($stack));
        $this->assertEmpty($stack);
    }

    /**
     * 3. 多重依赖测试
     * 参数不用明确声明，采用func_get_args获取参数
     */
    public function testProducerFirst()
    {
        $this->assertTrue(true);
        return "first";
    }

    public function testProducerSecond()
    {
        $this->assertTrue(true);
        return "second";
    }

    /**
    * @depends testProducerFirst
    * @depends testProducerSecond
     */
    public function testComsumer()
    {
        $this->assertEquals(["first", 'second'], func_get_args());
    }

    /**
     * 4. 数据提供器测试
     * @return array
     */
    public function addprovider()
    {
        return [
            [0, 0, 0],
            [0, 1, 1],
            [1, 0, 1],
            [1, 1, 2]
        ];
    }

    //命名数据集的数据供给器,这样输出信息更加详细
    public function addproviderDetail()
    {
        return [
            'Zero and zero' => [0, 0, 0],
            'Zero and one' => [0, 1, 1],
            'one and zero' => [1, 0, 1],
            'one and zero' => [1, 1, 2]
        ];
    }

    /**
     * 4. 数据提供器测试
     * @dataProvider addproviderDetail
     */
    public function testAdd($a, $b, $expected)
    {
        $this->assertEquals($a + $b, $expected);
    }

    //迭代器
    public function addProviderFromIterator()
    {
        return new CsvFileIterator("./data_interator.csv");
    }

    /**
     * 5. 数据提供器测试-- Interator对象
     * @dataProvider addProviderFromIterator
     */
    public function testAddCsv($a, $b, $expected)
    {
        $this->assertEquals($expected, $a + $b);
    }


    public function provider()
    {
        return [['provider1'], ['provider2']];
    }

    /**
     * 5. 数据提供器测试-- 同时使用dataProvider和depends
     * @depends testProducerFirst
     * @depends testProducerSecond
     * @dataProvider provider
     */
    public function testConsumer()
    {
        $this->assertEquals(['provider1', 'first', 'second'], func_get_args());
    }
}
