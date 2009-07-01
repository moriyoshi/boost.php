--TEST--
m008: C++/PHP classes
--SKIPIF--
--INI--
extension=m008.so
--FILE--
<?php
$test1 = test::create(1);
$test2 = new test(2);
for ($i = 0; $i < 10; ++$i) {
    $test1->accumulate($i);
    test::foo($test1);
    var_dump($test2->accumulate(10-$i));
    echo "--\n";
}
?>
--EXPECT--
1
int(12)
--
2
int(21)
--
4
int(29)
--
7
int(36)
--
11
int(42)
--
16
int(47)
--
22
int(51)
--
29
int(54)
--
37
int(56)
--
46
int(57)
--
