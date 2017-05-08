<?php
//Configuración servidor Mysql
$host = "localhost"; 
$user = "root";
$pass = "2*b**:E82JZ=93L|c0Tw"; 
$database ="auto";
$link=mysqli_connect($host,$user,$pass,$database);
while(1){
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
 socket_bind($sock,"0.0.0.0","7778");
 socket_listen($sock, 5);
 $socket=socket_accept($sock);
 while(1){ 
 $mensaje = socket_read($socket,2048,PHP_NORMAL_READ);
 if ($mensaje==''){
	 socket_close($socket);
	 socket_close($sock);
	 break;
 }else{
	echo $mensaje;
	if(strpos($mensaje,"timeS")!==false){
		$x=date(s);
		$s="Time now is=$x\r\n";
		socket_write($socket, $s, strlen($s));
	}else if(strpos($mensaje,"Comida=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$ToDb=str_replace("Comida=","",$mensaje);
		mysqli_query($link,"INSERT INTO comida(C,fecha) VALUES('$ToDb','$fecha')");
	}
	else if(strpos($mensaje,"pH=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$toDb=str_replace("pH=","",$mensaje);
		mysqli_query($link,"INSERT INTO ph(P,fecha) VALUES('$toDb','$fecha')");
	}
	else if(strpos($mensaje,"Temp=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$ToDb=str_replace("Temp=","",$mensaje);
		mysqli_query($link,"INSERT INTO temp(T,fecha) VALUES('$ToDb','$fecha')");
	}
	else if(strpos($mensaje,"Filtro=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$ToDb=str_replace("Filtro=","",$mensaje);
		mysqli_query($link,"INSERT INTO filtro(F,fecha) VALUES('$ToDb','$fecha')");
	}
	else if(strpos($mensaje,"Imagen=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$ToDb=str_replace("Imagen=","",$mensaje);
		mysqli_query($link,"INSERT INTO imagen(I,fecha) VALUES('$ToDb','$fecha')");
	}
	else if(strpos($mensaje,"Potencia=")!==false){
		$fecha = date ('Y-m-d H:i:s');
		$ToDb=str_replace("Potencia=","",$mensaje);
		mysqli_query($link,"INSERT INTO potencia(P,fecha) VALUES('$ToDb','$fecha')");
	}
	else if(strpos($mensaje,"TakeI=")!==false){
	}
	else if(strpos($mensaje,"TakeFil=")!==false){
	}
	else if(strpos($mensaje,"TakeAlim=")!==false){
	}
	if($Command=="1"){
		$s="Comando 1\r\n";
		socket_write($socket, $s, strlen($s));
	}
	else if($Command=="2"){
		$s="Comando 2\r\n";
		socket_write($socket, $s, strlen($s));
	}
	else if($Command=="3"){
		$s="Comando 3\r\n";
		socket_write($socket, $s, strlen($s));		
	}else if(strpos($mensaje,"Check")!==false){
		$s="Live\r\n";
		socket_write($socket, $s, strlen($s));
	}
 }
}
}
?>