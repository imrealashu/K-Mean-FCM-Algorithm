<?php
$mode = $_POST['data'];

if($mode = 'fcm'){
$data1 = $_POST['data1'];
$data2 = $_POST['data2'];

exec('gcc fuzzy.c -lm');
$a = exec('./a.out '.$data1.' '.$data2);
exec('convert seg0.pgm seg0.jpg');
exec('convert seg1.pgm seg1.jpg');
exec('convert seg2.pgm seg2.jpg');
exec('convert seg3.pgm seg3.jpg');
echo $a;	
}

// if($mode = 'kmean'){
// 	$data1 = $_POST['data1'];
// 	$data2 = $_POST['data2'];

// 	exec('gcc -o b kmean.c');
// 	$b = exec('./b '.$data1.' '.$data2);
// 	exec('convert seg0.pgm 1.jpg');
// 	exec('convert seg1.pgm 2.jpg');
// 	exec('convert seg2.pgm 3.jpg');
// 	exec('convert seg3.pgm 4.jpg');
// 	echo $b;
// }
?>