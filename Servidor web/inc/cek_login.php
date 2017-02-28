<?php
	@session_start();
	if(@$_SESSION['admin']){
		header("Location: admin/index.php");
	}
?>