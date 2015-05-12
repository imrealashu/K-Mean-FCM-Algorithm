<?php

$date = date('Y-m-d H:i:s');
$timestamp = time();

if(!empty($_FILES['file'])){
	
	foreach($_FILES['file']['name'] as $key => $name){
		$file = $_FILES['file']['name'][$key];
		$extension = pathinfo($file, PATHINFO_EXTENSION);
		// $image_name = $timestamp.$count.'.'.$extension;
		$output = "";
		if($_FILES['file']['error'][$key] == 0 && move_uploaded_file($_FILES['file']['tmp_name'][$key],"images/".$file)){
			$new_file = substr($file,0,-4);
			exec('convert images/'.$file.' images/'.$new_file.'.jpg');
			$output .=$file.','.$new_file.'.jpg#';
		}
		echo $output;
	}
	if(!empty($_POST['ajax'])){
		die(json_encode($uploaded));
	}
}
?>