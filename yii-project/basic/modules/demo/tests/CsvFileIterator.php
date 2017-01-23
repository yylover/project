<?php

namespace app\modules\demo\tests;

class CsvFileIterator implements \Iterator
{
    protected $file;
    protected $key = 0;
    protected $current;

    public function __construct($file)
    {
        $this->file = fopen($file, "r");
    }

    public function __destruct()
    {
        fclose($this->file);
    }

    public function rewind()
    {
        rewind($this->file);
        $this->current = fgetcsv($this->file);
        $this->key = 0;
    }

    public function valid()
    {
        return !feof($this->file);
    }

    public function key()
    {
        return $this-> key;
    }

    public function current()
    {
        return $this->current;
    }

    public function next()
    {
        return $this->current = fgetcsv($this->file);
        $this->key ++;
    }

    public function testThrowException()
    {
        throw new \InvalidArgumentException("Error Processing Request", 1);
    }
}
