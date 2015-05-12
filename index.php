<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
	<style type="text/css">
	body *{
		border-radius: 0px !important;
	}
	</style>

	<script type="text/javascript" src="js/upload.js"></script>
	<script type="text/javascript" src="js/jquery-1.11.2.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<script type="text/javascript" src="js/script.js"></script>
	<title></title>
</head>
<body>
	<div class="container">
		<div class="row">
			<h2 class="text-center">SEGMENTATION OF MEDICAL IMAGES USING CLUSTERING ALGORITHMS</h2>
			<div class="col-md-12">
				<hr>
					<form class="form-inline" action="" method="POST" enctype="mulitpart/form-data">
						<input type="file" id="file" class="form-control" name="file[]" multiple="multiple"/>
						<input type="submit" id="submit" class="btn btn-success" value="Upload"/>
						<button type="button" id="kmean" class="btn btn-danger">Run K-Means</button>
						<button type="button" id="fcm" class="btn btn-danger">Run Fuzzy c-Means</button>
						<button type="button" class="btn btn-primary pull-right">About</button>
					</form>
			</div>
		</div>
		<div class="row">
			<div class="col-md-12">
				<div>
					<div id="target_image" class="col-md-3 text-center"></div>
					<div id="target_image2" class="col-md-9">
					</div>
				</div>
			</div>
		</div>
	</div>
</body>
</html>