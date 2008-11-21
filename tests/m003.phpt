--TEST--
m003: string manipulations
--SKIPIF--
--INI--
extension=m003.so
--FILE--
<?php
var_dump(concat_and_uppercase("abc", "def"). "...");
?>
--EXPECT--
string(9) "ABCDEF..."
