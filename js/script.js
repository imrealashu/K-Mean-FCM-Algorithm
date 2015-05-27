jQuery(function(){
	$('#fcm').click(function(){
		$.post('images/generate.php',{data:'fcm',data1:$('#img1').attr('data'),data2:$('#img2').attr('data')},function(data){
			var accuracy = data.split("#");
			$('#target_image2').html('<img src="images/seg0.jpg?x" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg1.jpg?y" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg2.jpg?z" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg3.jpg?w" class="img-thumbnail"/>');
			$('#target_image2').append('<p>Background Accuracy: '+accuracy[4]+'%</p>');
			$('#target_image2').append('<p>White Matter Accuracy: '+accuracy[1]+'%</p>');
			$('#target_image2').append('<p>CSF Accuracy: '+accuracy[2]+'%</p>');
			$('#target_image2').append('<p>Grey Matter Accuracy: '+accuracy[3]+'%</p>');
			$('#target_image2').append('<p>Overall Accuracy: '+accuracy[0]+'%</p>');
		});
	});
	$('#kmean').click(function(){
		$.post('images/process.php',{data:'kmean',data1:$('#img1').attr('data'),data2:$('#img2').attr('data')},function(data){
			var accuracy = data.split("#");
			$('#target_image2').html('<img src="images/seg0.jpg?aa" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg1.jpg?bb" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg2.jpg?cc" class="img-thumbnail"/>');
			$('#target_image2').append('<img src="images/seg3.jpg?dd" class="img-thumbnail"/>');
			$('#target_image2').append('<p>Background Accuracy: '+accuracy[4]+'%</p>');
			$('#target_image2').append('<p>Grey Matter Accuracy: '+accuracy[3]+'%</p>');
			$('#target_image2').append('<p>CSF Accuracy: '+accuracy[2]+'%</p>');
			$('#target_image2').append('<p>White Matter Accuracy: '+accuracy[1]+'%</p>');
			$('#target_image2').append('<p>Overall Accuracy: '+accuracy[0]+'%</p>');
		});
	});
});
function start(filenames){

	var name_array = filenames.split("#");
	//console.log(filenames);
	var first_img = name_array[0].split(',');
	var second_img = name_array[1].split(',');

	var $data = '<img id="img1" data="'+second_img[0]+'" src="images/'+second_img[1]+'"class="img-thumbnail"/><br/>';
	$data += '<img id="img2" data="'+first_img[0]+'" src="images/'+first_img[1]+'" class="img-thumbnail"/>';
	
	$("#target_image").html($data);
}