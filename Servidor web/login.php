
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8">
		<link rel="icon" href="backend/images/icono.png" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta name="description" content="">
		<meta name="author" content="ThemeBucket">

		<title>UN ECO HOGAR</title>

		<!--Core CSS -->
		<link href="backend/panel/bs3/css/bootstrap.min.css" rel="stylesheet">
		<link href="backend/panel/css/bootstrap-reset.css" rel="stylesheet">
		<link href="backend/panel/font-awesome/css/font-awesome.min.css" rel="stylesheet" />

		<!-- Custom styles for this template -->
		<link href="backend/panel/css/style.css" rel="stylesheet">
		<link href="backend/panel/css/style-responsive.css" rel="stylesheet" />

		<!-- Just for debugging purposes. Don't actually copy this line! -->
		<!--[if lt IE 9]>
		<script src="js/ie8-responsive-file-warning.js"></script><![endif]-->

		<!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->
		<!--[if lt IE 9]>
		<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
		<script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
		<![endif]-->
	    <style type="text/css">
<!--
.Estilo3 {color: #996699}
-->
        </style>
<body class="login-body">
		<div class="container">
			<form class="form-signin" action="" method="post" enctype="multipart/form-data">
				<h2 class="form-signin-heading">Panel de acceso para Administrador</h2>
			  <div class="login-wrap">
					<div class="user-login-info">
                        
                        <?php
                        include 'inc/config.php';
                        if(isset($_POST['login'])){	
                            $username = mysqli_real_escape_string($link,$_POST['username']);
                            $password = mysqli_real_escape_string($link,md5($_POST['password']));
                            $perintah = mysqli_query($link,"SELECT * FROM user WHERE username = '$username' AND password = '$password'") or die(mysqli_error());
                            if (mysqli_num_rows($perintah) > 0) {
                                $row = mysqli_fetch_assoc($perintah);
                                session_start(); 
                                $_SESSION['admin'] = $username;
                                $_SESSION['name'] = $row['name_user'];
                                $_SESSION['id'] = $row['id_user'];
                                header("location: index.php");
                            }else{
                                echo "		
                                <div class='alert alert-danger fade in' role='alert'>
                                <button type='button' class='close' data-dismiss='alert'><span aria-hidden='true'>×</span><span class='sr-only'>Close</span></button>
                                <strong> Disculpa! </strong> Usuario / Contraseña incorrecta.
                                </div>
                                ";
                            }		
                        }
                        ?>
                        
					<input type="text" name="username" class="form-control" placeholder="Ingresa tu usuario" autofocus>
					<input type="password" name="password" class="form-control" placeholder="Contraseña">
					</div>
					<button class="btn btn-lg btn-login btn-block" name="login" type="submit">Entrar</button>
				<br>
			  </div>
			</form>
		</div>
		<!-- Placed js at the end of the document so the pages load faster -->
		<!--Core js-->
		<script src="backend/panel/js/jquery.js"></script>
		<script src="backend/panel/bs3/js/bootstrap.min.js"></script>
</body>
</html>
