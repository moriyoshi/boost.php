<?php
$test1 = new test();
$test2 = new test();
for ($i = 0; $i < 10; ++$i) {
    $test1->accumulate($i);
    test::foo($test1);
    var_dump($test2->accumulate(10-$i));
    echo "--\n";
}
?>
