--TEST--
m007: extension-wide variables
--SKIPIF--
--INI--
extension=m007.so
--FILE--
<?php
for ($i = 0; $i < 10; ++$i) {
    var_dump(accumulate($i));
}
?>
--EXPECT--
int(0)
int(1)
int(3)
int(6)
int(10)
int(15)
int(21)
int(28)
int(36)
int(45)
