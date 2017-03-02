<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css">
<?php
$result=mysqli_query($link,"SELECT * FROM teta ORDER BY fecha DESC");
$row=mysqli_fetch_array($result);

$result2=mysqli_query($link,"SELECT * FROM fi ORDER BY fecha DESC");
$row2=mysqli_fetch_array($result2);
?>

<h1>Panel solar</h1>
<div class="table-responsive">
                                <table  class="display table table-bordered table-striped" id="dynamic-table">
                                    <thead>
                                        <tr>
                                            <th>Ángulo tetha (θ)</th>
                                            <th>Fecha</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <?php foreach( $result as $row => $field ) : ?> <!-- Mulai loop -->
                                        <tr class="text-besar">
                                            <td><?php echo "$field[teta]  (° Grados)";?></td>
                                            <td><?php echo $field['fecha']; ?></td>                                               
                                        </tr>
                                        <?php endforeach; ?> <!-- Selesai loop -->                                  
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </section>
                </div>
            </div>

<div class="table-responsive">
                                <table  class="display table table-bordered table-striped" id="dynamic-table">
                                    <thead>
                                        <tr>
                                            <th>Ángulo Fhi (φ)</th>
                                            <th>Fecha</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <?php foreach( $result2 as $row2 => $field ) : ?> <!-- Mulai loop -->
                                        <tr class="text-besar">
                                            <td><?php echo "$field[fi]  (° Grados)";?></td>
                                            <td><?php echo $field['fecha']; ?></td>                                               
                                        </tr>
                                        <?php endforeach; ?> <!-- Selesai loop -->                                  
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </section>
                </div>
            </div>