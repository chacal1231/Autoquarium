<?php
$query=mysqli_query($link,"SELECT * FROM usuarios");
$row=mysqli_fetch_array($query);
?>

<?php
$result = mysqli_query($link,"SELECT * FROM usuarios");
$row = mysqli_fetch_array($result)
?>

<?php
$result2 = mysqli_query($link,"SELECT nombre FROM planes ORDER BY id asc");
$row2 = mysqli_fetch_array($result2)
?>
                
            <div class="row">
                <div class="col-sm-12">
                    <section class="panel">
                        <header class="panel-heading">
                            Registro de usuarios
                            <span class="tools pull-right">
                                <a href="javascript:;" class="fa fa-chevron-down"></a>
                                <a href="javascript:;" class="fa fa-cog"></a>
                                <a href="javascript:;" class="fa fa-times"></a>
                            </span>
                        </header>
                        <div class="panel-body"> 
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
                                        </tr>
                                        <?php endforeach; ?> <!-- Selesai loop -->                                  
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </section>
                </div>
            </div>
   
   
  



            <!-- Modal -->
           
            <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
            <div class="modal-dialog" role="document">
                    <div class="modal-content">
                        <div class="modal-header">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                            <h4 class="modal-title" id="myModalLabel">Nuevo cliente</h4>
                            </div>
                        <div class="modal-body">
                        <form id="modal-form" action="" method="post">
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Nombre:</label>
                                <input type="text" class="form-control" name="name">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Cedula/NIT:</label>
                                <input type="text" class="form-control" name="cedula">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Telefono:</label>
                                <input type="text" class="form-control" name="telefono">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Correo electronico:</label>
                                <input type="text" class="form-control" name="correo">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Dirección de residencia:</label>
                                <input type="text" class="form-control" name="direccion">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Tipo de usuario:</label>
                                <select id="tipo_u" name="tipo_u" class="form-control">
                                <option value="Residencial">Residencial</option>
                                <option value="Comercial">Comercial</option>
                                </select>
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Plan:</label>
                                <div class="form-group">
                                <select id="plan" name="plan" class="form-control">
                                <?php
                                
                                    do 
                                    {
                                        ?>
                                        <option value="<?php echo $row2['nombre']?>">
                                        <?php echo $row2['nombre']; ?>
                                        </option>
                                        <?php

                                    }while ($row2 = $result2->fetch_assoc())   ?>   
                                
                                </select>
                            </div>
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Ip:</label>
                                <input type="text" class="form-control" name="target" placeholder="0.0.0.0/32">
                            </div>
                            <div class="form-group">
                                <label for="recipient-name" class="control-label">Fecha de instalación:</label>
                                <input type="text" class="form-control" id="datepicker"  data-date-format="yyyy-mm-dd" readonly="readonly" name="fecha_i">
                            </div>    
                                <div class="form-group">
                                <label for="recipient-name" class="control-label">Fecha de corte:</label>
                                <input type="text" class="form-control" id="datepicker2"  data-date-format="yyyy-mm-dd" readonly="readonly" name="fecha_c">
                                 </div>
                                <div class="text-right">
                                <button type="button" class="btn btn-default" data-dismiss="modal">Cerrar</button>
                                <button type="submit" class="btn btn-primary" name="simpan" value="Sign up">Agregar cliente</button>
                            </div>
                        </form>
                    </div>
                </div>
            </div> 

            </head>
</html>