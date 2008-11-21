--TEST--
m004: reading an array
--SKIPIF--
--INI--
extension=m004.so
--FILE--
<?php
$arr = array(1, 2, 3);
for ($i = 0; $i < count($arr); $i++) {
    var_dump(array_func($arr, $i));
}
?>
--EXPECT--
string(37) "The content of array element #0 is 1."
string(37) "The content of array element #1 is 2."
string(37) "The content of array element #2 is 3."
