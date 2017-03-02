<style type="text/css">
A:link {
	text-decoration:none;color:#FFFFFF;
}
</style> 


<div class="row">
	<div class="col-sm-10">
		<section class="panel">
			<header class="panel-heading" align="center">
				<div align="center"><h4><strong>Recuerde seleccionar el rango de fechas en las cuales desea saber las ventas realizadas..</strong></h4></div>
			</header>
			<div class="panel-body">
				<div class="adv-table">
					<table class="display table table-bordered table-striped" id="dynamic-table">
						<tr>
							<td>
								<?php
								$buscar=$_POST['datepicker'];
								$buscar1=$_POST['datepicker1'];						 
								$result = mysqli_query($link,"SELECT * FROM usuarios WHERE fecha >='$buscar' and fecha <= '$buscar1'");
								while($row=mysqli_fetch_assoc($result))
								{
								$total=$total+$row['precio'];
								}
								echo "<h2><div align=center> Las ventas realizadas de $busca2 desde el dia <b>$buscar</b> hasta el dia <b>$buscar1</b> es de  <b><font color=#FE642E>$ $total</font></b> pesos.</div></h2>";
								?>
							</td>
						</tr>
					</table>
						<div align="center">
							<button type="button" class="btn btn-primary"><a href="javascript:history.back()">Volver atras</a></button>
						</div>
				</div>
            </div>
        </section>
    </div>
</div>