<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css">
<div class="row">
    <div class="col-sm-4">
        <section class="panel">
            <header class="panel-heading">
                Configuración de usuario
                <span class="tools pull-right">
                    <a href="javascript:;" class="fa fa-chevron-down"></a>
                    <a href="javascript:;" class="fa fa-cog"></a>
                    <a href="javascript:;" class="fa fa-times"></a>
                </span>
            </header>
            <div class="panel-body">
                <?php if(isset($_POST['change_user'])){
                    $name       = mysqli_real_escape_string($link,$_POST['name']);
                    $username   = mysqli_real_escape_string($link,$_POST['username']);
                    $password   = mysqli_real_escape_string($link,md5($_POST['password']));
                    $change_user = mysqli_query($link,"UPDATE user SET name_user='$name', username='$username',  password='$password' WHERE id_user='1'") or die(mysqli_error());
                    if($change_user){
                        echo '<div class="alert alert-success" role="alert">
                        <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                         <strong>¡Todo correcto!</strong> Se han cambiado las credenciales de usuario con exito. </div>';
                    }
                }?>
                <?php
                    $user = mysqli_query($link,"SELECT * FROM user WHERE id_user='1'") or die(mysql_error());
                    $u = mysqli_fetch_assoc($user);
                ?>
                <form accept="" method="post">
                    <div class="form-group">
                      <label>Nombre :</label>
                      <input type="text" class="form-control" name="name" value="<?=$u['name_user'];?>">
                    </div>
                    <div class="form-group">
                      <label>Usuario :</label>
                      <input type="text" class="form-control" name="username" value="<?=$u['username'];?>">
                    </div>
                    <div class="form-group">
                      <label>Contraseña :</label>
                      <input type="password" class="form-control" name="password" value="<?=$u['password'];?>">
                    </div>
                    <button type="submit" class="btn btn-success" name="change_user">Guardar</button>
                </form>  
            </div>
        </section>
    </div>
</div>