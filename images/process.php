<?php
$data1 = $_POST['data1'];
$data2 = $_POST['data2'];
exec('gcc -o a kmeans.c');
$b = exec('./a '.$data1.' '.$data2);
// exec('convert segmented.pgm segmented.jpg');
	exec('convert seg0.pgm seg0.jpg');
	exec('convert seg1.pgm seg1.jpg');
	exec('convert seg2.pgm seg2.jpg');
	exec('convert seg3.pgm seg3.jpg');
	echo $b;
	
?>