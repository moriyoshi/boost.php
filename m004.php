<?php
$arr = array(1, 2, 3);
for ($i = 0; $i < count($arr); $i++) {
    var_dump(array_func($arr, $i));
}
?>
