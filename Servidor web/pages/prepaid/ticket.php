<!DOCTYPE html>
<html lang="en">
  <head>

  </head>

<body>

<div class="row">
	<div class="col-sm-10">
		<section class="panel">
			<header class="panel-heading" align="center">
				<span class="tools pull-right">
					<a href="javascript:;" class="fa fa-chevron-down"></a>
					<a href="javascript:;" class="fa fa-cog"></a>
					<a href="javascript:;" class="fa fa-times"></a>
				</span><div align="center"><h4><strong>Selecciona el tiempo y presiona Generar Ticket para que el usuario pueda navegar.</strong></h4></div>
			</header>
			<div class="panel-body">
				<div class="adv-table">
				</div>
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
									<tr class="alt" align="center"><td><input  type="image" src="backend/images/ticket.png" alt="Submit Form"/></td></tr>
							</table>
						</form>			
					</div>
									

				</div>
            </div>
        </section>
    </div>
</div>

</body>

<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.3.1/jquery.min.js'></script>
<script type='text/javascript' src='js/logging.js'></script>
</html>