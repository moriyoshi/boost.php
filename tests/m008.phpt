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
    var_dump($test2 == $test2->self());
    var_dump($test2->self()->self()->accumulate(10-$i));
    echo "--\n";
}
?>
--EXPECT--
1
bool(true)
int(12)
--
2
bool(true)
int(21)
--
4
bool(true)
int(29)
--
7
bool(true)
int(36)
--
11
bool(true)
int(42)
--
16
bool(true)
int(47)
--
22
bool(true)
int(51)
--
29
bool(true)
int(54)
--
37
bool(true)
int(56)
--
46
bool(true)
int(57)
--
