--TEST--
m009: Implementing SPL classes
--SKIPIF--
--INI--
extension=m009.so
--FILE--
<?php
foreach (new RangeIterator(0, 5) as $a) {
    var_dump($a);
}
?>
--EXPECT--
int(0)
int(1)
int(2)
int(3)
int(4)
