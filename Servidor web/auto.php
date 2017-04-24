<?php
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
 socket_bind($sock,"0.0.0.0","8000");
 socket_listen($sock, 5);
 $socket=socket_accept($sock);
 while(1){
 $mensaje = socket_read($socket,4,PHP_NORMAL_READ);
 if ($mensaje==''){
	 socket_close($socket);
	 socket_close($sock);
	 break;
 }else{
	echo $mensaje;
	if($mensaje=="1111"){
		$x=date(H);
		$s="Time now is=$x\r\n";
		socket_write($socket, $s, strlen($s));
	}
 }
}
?>