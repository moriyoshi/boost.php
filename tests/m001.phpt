--TEST--
m001: extension loading
--SKIPIF--
--INI--
extension=m001.so
--FILE--
<?php
var_dump(extension_loaded('m001'));
?>
--EXPECT--
bool(true)
