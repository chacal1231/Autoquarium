<?php
$query=mysqli_query($link,"SELECT * FROM usuarios");
$row=mysqli_fetch_array($query);
?>

<div class="row">
	<div class="col-sm-12">
		<section class="panel">
			<header class="panel-heading">
				Area de clientes
				<span class="tools pull-right">
					<a href="javascript:;" class="fa fa-chevron-down"></a>
					<a href="javascript:;" class="fa fa-cog"></a>
					<a href="javascript:;" class="fa fa-times"></a>
				</span>
			</header>
			<div class="panel-body"> 
				<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#myModal">
					Añadir un nuevo cliente 
				</button>
				<button type="button" class="btn btn-info" data-toggle="modal" data-target="#myModal2">
					Exportar clientes
				</button>
				<hr/>
				<div class="adv-table">
					<table  class="display table table-bordered table-striped" id="dynamic-table">
						<thead>
							<tr>
								<th>Usuario</th>
								<th>Clave</th>
								<th>Plan</th>
								<th>Precio</th>
								<th>N. Equipos</th>
								<th>Fecha Ingreso</th>
								<th>Tipo</th>
								<th>Acción</th>
								<th><i class="fa fa-trash-o"></i></th>
								<th><i class="fa fa-pencil"></i></th>
							</tr>
						</thead>
						<tbody>
							<?php foreach( $query as $row => $field ) : ?> <!-- Mulai loop -->
							<tr class="text-besar">
								<td><?php echo $field['usuario']; ?></td>
								<td><?php echo $field['clave']; ?></td>
								<td><?php echo $field['tiempo']; ?></td>
								<td><?php echo $field['precio']; ?></td>
								<td><?php echo $field['equipos']; ?></td>
								<td><?php echo $field['fecha']; ?></td>
								<td><?php echo $field['tipo']; ?></td>
								<td><?php echo $field['accion']; ?>
									<td><?php if($field['estado'] == 'off'){ ?>
									<a href="?page=reac_cli&ip=<?php echo $field['ip']; ?>&id=<?php echo $field['id'];?>" title="Reactivar">
									<span class="label label-success">Reactivar</span></a>

									<?php } else { ?>
									
									<a href="?page=sus_cli&ip=<?php echo $field['ip'];?>&id=<?php echo $field['id'];?>" title="Suspender">
									<span class="label label-danger">Suspender</span></a>

									<?php } ?></td>
									 <td>  
										<a href="?page=eli_cli&id=<?php echo $field['id']; ?>&ipp=<?php echo $field['ip']; ?>" title="Eliminar" onClick="return confirm('Desea eliminar al cliente ?...')">
										<button class="btn btn-danger btn-xs"><i class="fa fa-trash-o"></i></button>
										</a>
										</td>
									   
										<td><a href="?page=modi_cli&id=<?php echo $field['id']; ?>" title="Modificar">
										<button class="btn btn-success btn-xs"><i class="fa fa-pencil"></i></button></td>
								</td>
									
							</tr>
							<?php endforeach; ?> <!-- Selesai loop -->                                  
						</tbody>
					</table>
				</div>
			</div>
		</section>
	</div>
</div>