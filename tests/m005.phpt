--TEST--
m005: array manipulations
--SKIPIF--
--INI--
extension=m005.so
--FILE--
<?php
array_iter(array(1, 2, 3, "A" => "4", 5));
var_dump(array_explode(':', array(1, 2, 3, "A" => "4", 5)));
?>
--EXPECT--
0
1
2
A
3
1
2
3
4
5
string(9) "1:2:3:4:5"
