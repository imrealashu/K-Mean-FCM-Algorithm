var handleUpload = function(event){
	event.preventDefault();
	event.stopPropagation();
	
	var fileInput = document.getElementById('file');
	
	var data = new FormData();
	
	data.append('ajax',true);
	
	for(var i = 0; i< fileInput.files.length; ++i){
		data.append('file[]',fileInput.files[i]);
	}
	if(fileInput.files.length <2){
		console.log('Please enter two files');
		exit();
	}
	var request = new XMLHttpRequest();
	
	request.upload.addEventListener('progress',function(event){
		if(event.lengthComputable){
			var percent = event.loaded / event.total;
			//var progress = document.getElementById('upload_progress');
			
			// while(progress.hasChildNodes()){
			// 	progress.removeChild(progress.firstChild);
			// }
			//var progressValue = progress.appendChild(document.createTextNode(Math.round(percent * 100) + ' %'));
			//console.log(Math.round(percent * 100));
			//document.getElementById('progress-bar').style.width = Math.round(percent * 100)+"%";
			//document.getElementById('progress-bar').innerHTML =  Math.round(percent * 100)+"%";
			console.log(Math.round(percent * 100)+"%")
		}
	});
	
	request.upload.addEventListener('load',function(event){
		//document.getElementById('upload_progress').style.display = 'none';
	});
	
	request.upload.addEventListener('error',function(event){
		alert('upload not completed');
	});
	
	request.addEventListener('readystatechange',function(event){
		if(this.readyState == 4){
			if(this.status == 200){
				start(this.response);
			}else{
				console.log(this.status);
			}
		}
	});
	
	request.open('POST','upload.php');
	request.setRequestHeader('Cache-Control','no-cache');
	request.send(data);
}
window.addEventListener('load',function(event){
	var submit = document.getElementById('submit');
	submit.addEventListener('click',handleUpload);
});