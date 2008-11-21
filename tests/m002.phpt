--TEST--
m002: simple functions definition
--SKIPIF--
--INI--
extension=m002.so
--FILE--
<?php
for ($i = 0; $i < 10; ++$i) {
    var_dump(add($i, 2), sub($i, 2));
}
?>
--EXPECT--
int(2)
int(-2)
int(3)
int(-1)
int(4)
int(0)
int(5)
int(1)
int(6)
int(2)
int(7)
int(3)
int(8)
int(4)
int(9)
int(5)
int(10)
int(6)
int(11)
int(7)
