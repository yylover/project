<?php
namespace app\modules\demo\tests;

use PHPUnit\Framework\TestCase;
use app\modules\demo\tests\CsvFileIterator;

require "CsvFileIterator.php";
/**
 * $this->assertEquals('value', 'response-value');
 * $this->assertEmpty();
 */
class ExceptionTest extends TestCase
{
    // public function testException()
    // {
    //     $this->expectException(InvalidArgumentException::class);
    // }

    /**
     * @expectedException InvalidArgumentException
     */
    public function testExpectExcepiton()
    {
        $model = new CsvFileIterator("data_interator.csv");
        $model->testThrowException();
    }

    /**
    * @expectedException PHPUnit_Framework_Error
    */
    public function testFailingInclude()
    {
        include 'not_existing_file.php';
    }

    public function testFileWriting()
    {
        $writer = new FileWriter;
        $this->assertFalse(@$writer->write('/is-not-writeable/file', 'stuff'));
    }

    public function testExpectFooActualFoo()
    {
        $this->expectOutputString('foo');
        print 'foo';
    }
}

class FileWriter
{
    public function write($file, $content)
    {
        $file = fopen($file, 'w');
        if ($file == false) {
            return false;
        }
    }
}
