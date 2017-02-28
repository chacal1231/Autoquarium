		<?php 
		if (isSet($_POST['tiempo'])){
			$tiempo=$_POST['tiempo'];
			$tiempo+=1;
			$tiempo-=1;
		}else
			$tiempo=15;
		
		if ( empty ($_POST['tiempo']) or empty ($_POST['perfil']) or empty ($_POST['vel']) ){
			header('Location: ?page=prepaid/error');
		}
		else{


		
		$segundos=$tiempo*60;
		$dias=$tiempo/1440;
		$date = date("d/m/Y");
		$vel=$_POST['vel'];
		
		//Precios dispositivos asociados 1 hora celular
		$chora2d=700;
		$chora3d=1100;
		$chora4d=1500;
		
		//Precios dispositivos asociados 1 Dia celular
		$cdia2d=2000;
		$cdia3d=3500;
		$cdia4d=5000;
		
		//Precios dispositivos asociados 1 Semana celular
		$csem2d=7000;
		$csem3d=11000;
		$csem4d=15000;
		
		//Precios dispositivos asociados 15 Dias celular
		$cqdias2d=10000;
		$cqdias3d=20000;
		$cqdias4d=30000;
		
		//Precios dispositivos asociados 1 Mes celular
		$cmes2d=25000;
		$cmes3d=38000;
		$cmes4d=50000;
		
		//Precios dispositivos asociados 1 Hora computador
		$horaco2d=1000;
		$horaco3d=1500;
		$horaco4d=2000;
		
		//Precios dispositivos asociados 1 Dia computador
		$undia2dc=3000;
		$undia3dc=5000;
		$undia4dc=7000;
		
		//Precios dispositivos asociados 1 Semana computador
		$unasem2dc=10000;
		$unasem3dc=15000;
		$unasem4dc=20000;
		
		//Precios dispositivos asociados 15 Dias computador
		$qdias2dc=20000;
		$qdias3dc=30000;
		$qdias4dc=40000;
		
		//Precios dispositivos asociados 1 Mes computador
		$mes2dc=30000;
		$mes3dc=50000;
		$mes4dc=70000;
		
		//Cantidad de celulares
		$celular="Celular";
		
		//Cantidad de computadores
		$compu="Computador";
		
		
		//Precios normales celular-tiempo
		if ($dias==(1/24)){
			$precio=1500;
			$dias2="1 Hora";
		}	else if($dias==1){
			$precio=5000;
			$dias2="1 dia";
		}else if($dias==7){
			$precio=15000;
			$dias2="7 dias";
		}else if($dias==15){
			$precio=30000;
			$dias2="15 dias";
		}else if($dias==30){
			$precio=50000;
			$dias2="30 dias";
		}
		
		//Precios normales computador-tiempo
		if ($dias==(1/24) and $vel=="256k/1024k"){
			$precio=2000;
			$dias2="1 Hora";
		}	else if($dias==1 and $vel=="256k/1024k"){
			$precio=7000;
			$dias2="1 dia";
		}else if($dias==7 and $vel=="256k/1024k"){
			$precio=20000;
			$dias2="7 dias";
		}else if($dias==15 and $vel=="256k/1024k"){
			$precio=40000;
			$dias2="15 dias";
		}else if($dias==30 and $vel=="256k/1024k"){
			$precio=70000;
			$dias2="30 dias";
		}
		
		
		
		function randomcrap(){
		$caracteres = "abcdefghijklmnopqrstuvwxyz"; //posibles caracteres a usar
		$numerodeletras=5; //numero de letras para generar el texto
		$cadena = ""; //variable para almacenar la cadena generada
		for($i=0;$i<$numerodeletras;$i++){
			$cadena .= substr($caracteres,rand(0,strlen($caracteres)),1); /*Extraemos 1 caracter de los caracteres 
			entre el rango 0 a Numero de letras que tiene la cadena */
		}
		return $cadena;
		}	
			
		$usuario=randomcrap();
		$password=randomcrap();
		$profile=$_POST['perfil'];
		
		//Perfil 200k/768k - Celulares
		// un dispositivo
		if ($vel=="200k/768k" and $profile==PAGO){
			$profile2=Celular1;
			$dis=1;
			$equipo=$celular;
			$precio=$precio;
		}

		// dos dispositivos
			else if ($vel=="200k/768k" and $profile==PAGO2){
			$profile2=Celular2;
			$dis=2;
			$equipo=$celular;
		
			if($dias==(1/24)){
				$precio=$precio+$chora2d;
			}
			if($dias==1){
				$precio=$precio+$cdia2d;
			}
			if($dias==7){
				$precio=$precio+$csem2d;
			}
			if($dias==15){
				$precio=$precio+$cqdias2d;
			}
			if($dias==30){
				$precio=$precio+$cmes2d;
			}
		}
		
		// tres dispositivos
			else if ($vel=="200k/768k" and $profile==PAGO3){
			$profile2=Celular3;
			$dis=3;
			$equipo=$celular;
		
			if($dias==(1/24)){
				$precio=$precio+$chora3d;
			}
			if($dias==1){
				$precio=$precio+$cdia3d;
			}
			if($dias==7){
				$precio=$precio+$csem3d;
			}
			if($dias==15){
				$precio=$precio+$cqdias3d;
			}
			if($dias==30){
				$precio=$precio+$cmes3d;
			}
		}
		
		// cuatro dispositivos
			else if ($vel=="200k/768k" and $profile==PAGO4){
			$profile2=Celular4;
			$dis=4;
			$equipo=$celular;
		
			if($dias==(1/24)){
				$precio=$precio+$chora4d;
			}
			if($dias==1){
				$precio=$precio+$cdia4d;
			}
			if($dias==7){
				$precio=$precio+$csem4d;
			}
			if($dias==15){
				$precio=$precio+$cqdias4d;
			}
			if($dias==30){
				$precio=$precio+$cmes4d;
			}
		}
			
		//Perfil 256k/1024k - Celulares
		// un dispositivo
		if ($vel=="256k/1024k" and $profile==PAGO){
			$profile2=Computador1;
			$dis=1;
			$equipo=$compu;
			$precio=$precio;
			}

		// dos dispositivos
			else if ($vel=="256k/1024k" and $profile==PAGO2){
			$profile2=Computador2;
			$dis=2;
			$equipo=$compu;
		
			if($dias==(1/24)){
				$precio=$precio+$horaco2d;
			}
			if($dias==1){
				$precio=$precio+$undia2dc;
			}
			if($dias==7){
				$precio=$precio+$unasem2dc;
			}
			if($dias==15){
				$precio=$precio+$qdias2dc;
			}
			if($dias==30){
				$precio=$precio+$mes2dc;
			}
		}
		
		// tres dispositivos
			else if ($vel=="256k/1024k" and $profile==PAGO3){
			$profile2=Computador3;
			$dis=3;
			$equipo=$compu;
		
			if($dias==(1/24)){
				$precio=$precio+$horaco3d;
			}
			if($dias==1){
				$precio=$precio+$undia3dc;
			}
			if($dias==7){
				$precio=$precio+$unasem3dc;
			}
			if($dias==15){
				$precio=$precio+$qdias3dc;
			}
			if($dias==30){
				$precio=$precio+$mes3dc;
			}
		}
		
		// cuatro dispositivos
			else if ($vel=="256k/1024k" and $profile==PAGO4){
			$profile2=Computador4;
			$dis=4;
			$equipo=$compu;
		
			if($dias==(1/24)){
				$precio=$precio+$horaco4d;
			}
			if($dias==1){
				$precio=$precio+$undia4dc;
			}
			if($dias==7){
				$precio=$precio+$unasem4dc;
			}
			if($dias==15){
				$precio=$precio+$qdias4dc;
			}
			if($dias==30){
				$precio=$precio+$mes4dc;
			}
		}		

		
		
		$QUEUES = $API->comm("/ip/hotspot/user/add", array(
                "name"        => $usuario,
                "limit-uptime"      => $segundos,
                "profile"   => $profile2,
                "password"      => $password,
                ));

		
		$file = fopen("pages/prepaid/registro.txt", "a");
		fwrite($file, "Se creó el usuario '$usuario' con la contraseña '$password' el día $date tiempo de navegación $dias2 con $dis dispositivos asociados a la cuenta, tipo de equipo $equipo por el valor de $precio" . PHP_EOL);
		fwrite($file, "" . PHP_EOL);
		fclose($file);
		
		$date2 = date("Y-m-d");
		mysqli_query($link,"INSERT INTO usuarios(usuario,clave,tiempo,precio,equipos,fecha,tipo) VALUES ('$usuario','$password','$dias2','$precio','$dis','$date2','$equipo')");
		$my_error = mysqli_error($link);
		
		?>
<div class="row">
	<div class="col-sm-5">
		<section class="panel">
			<header class="panel-heading">
				<span class="tools pull-right">
					<a href="javascript:;" class="fa fa-chevron-down"></a>
					<a href="javascript:;" class="fa fa-cog"></a>
					<a href="javascript:;" class="fa fa-times"></a>
				</span>
				<h4><strong> ¡Se ha generado un nuevo ticket!</h4></strong>				
			</header>
			<table id="customers" class="display table table-bordered table-striped">
			<tr><td>Nombre de Usuario</td><td><strong><?php echo $usuario;?></strong></td></tr>
			<tr class="alt"><td>Clave de usuario</td><td><strong><?php echo $password;?></strong></td></tr>
			<tr><td>Tiempo de navegacion</td><td><?php echo $dias2;?></td></tr>
			<tr class="alt"><td>Cantidad dispositivos en el usuario</td><td><?php echo $dis. " Dispositivos";?></td></tr>
			<tr><td>Tipo de equipo</td><td><?php echo $equipo ?></td></tr>
			<tr class="alt"><td>Precio</td><td><?php echo $precio. " Pesos";?></td></tr>
			</table>
		</section>
	</div>
			<!-- Inicio tabla seleccion de tiempo -->		
	<div class="col-sm-7">
		<section class="panel">
			<header class="panel-heading">
				<span class="tools pull-right">
					<a href="javascript:;" class="fa fa-chevron-down"></a>
					<a href="javascript:;" class="fa fa-cog"></a>
					<a href="javascript:;" class="fa fa-times"></a>
				</span>
					<div align="center"><h4><strong>Selecciona el tiempo y presiona Generar Ticket para que el usuario pueda navegar.</strong></h4></div>
			</header>
			<div class="panel-body">
				<div class="adv-table">
					<div id="container" class="container">
						<FORM action="?page=prepaid/tickets" method="post">
							<table id="customers" class="display table table-bordered table-striped">
							<tr>
								<td width="auto"><strong>Tiempo :</strong></td>
								<td width="auto"><strong><input type="radio" name="tiempo" value="60"/> 1 Hora</strong></td>
								<td width="auto"><strong><input type="radio" name="tiempo" value="1440"/> 1 Dia</strong></td>
								<td width="auto"><strong><input type="radio" name="tiempo" value="10080"/> 1 Semana</strong></td>
								<td width="auto"><strong><input type="radio" name="tiempo" value="21600"/> 15 Dias</strong></td>
								<td width="auto"><strong><input type="radio" name="tiempo" value="43200"/> 1 Mes</strong></td>
							</tr>
							</table>
							<table id="customers" class="display table table-bordered table-striped">
								<tr class="alt">
									<td>Numero de Dispositivos: 
										<select name="perfil">
										<option value="" selected="selected">Seleccione</option>
										<option value="PAGO">1 Dispositivo</option>
										<option value="PAGO2">2 Dispositivos</option>
										<option value="PAGO3">3 Dispositivos</option>
										<option value="PAGO4">4 Dispositivos</option>
									</td>
									<td>Tipo de equipo: 
									<select name="vel">
										<!-- <option value="75k/256k">75k/256k</option>
										<option value="100k/512k">100k/512k</option> -->
										<option value="" selected="selected">Seleccione</option>
										<option value="200k/768k">Celular</option>
										<option value="256k/1024k">Computador</option>
									</td>
								</tr>
							</table>
							<table id="customers" align="center">
									<tr class="alt"><td><input  type="image" src="backend/images/button.png" alt="Submit Form"/></td></tr>
							</table>
						</form>			
					</div>
				</div>
			</div>
		</section>
	</div>
</div>
<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.3.1/jquery.min.js'></script>
<script type='text/javascript' src='js/logging.js'></script>
		<?php }?>