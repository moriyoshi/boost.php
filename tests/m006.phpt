--TEST--
m006: extension using php's native functions
--SKIPIF--
--INI--
extension=m006.so
--FILE--
<?php
var_dump(my_file_get_contents(__FILE__));
?>
--EXPECT--
string(51) "<?php
var_dump(my_file_get_contents(__FILE__));
?>
"
