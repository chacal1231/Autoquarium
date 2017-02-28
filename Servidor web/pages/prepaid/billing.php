<html xmlns="http://www.w3.org/1999/xhtml" lang="es" xml:lang="es">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="author" content="">
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<meta name="title" content="Demo de jQuery Data Picker" />
	<meta name="description" content="Demo de jQuery Data Picker" />
	<meta name="keywords" content="Demo, calendario, Data Picker" />
	<meta name="author" content="Emenia" />
	<link rel="stylesheet" type="text/css" href="css/jquery-ui-1.7.2.custom.css" />
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js"></script>
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js"></script>
	
 	<script type="text/javascript">
	jQuery(function($){
	$.datepicker.regional['es'] = {
		closeText: 'Cerrar',
		prevText: '&#x3c;Ant',
		nextText: 'Sig&#x3e;',
		currentText: 'Hoy',
		monthNames: ['Enero','Febrero','Marzo','Abril','Mayo','Junio',
		'Julio','Agosto','Septiembre','Octubre','Noviembre','Diciembre'],
		monthNamesShort: ['Ene','Feb','Mar','Abr','May','Jun',
		'Jul','Ago','Sep','Oct','Nov','Dic'],
		dayNames: ['Domingo','Lunes','Martes','Mi&eacute;rcoles','Jueves','Viernes','S&aacute;bado'],
		dayNamesShort: ['Dom','Lun','Mar','Mi&eacute;','Juv','Vie','S&aacute;b'],
		dayNamesMin: ['Do','Lu','Ma','Mi','Ju','Vi','S&aacute;'],
		weekHeader: 'Sm',
		dateFormat: 'yy-mm-dd',
		firstDay: 1,
		isRTL: false,
		showMonthAfterYear: false,
		yearSuffix: ''};
	$.datepicker.setDefaults($.datepicker.regional['es']);
});    
$(document).ready(function() {
           $("#datepicker").datepicker();
        });
        $(document).ready(function() {
           $("#datepicker2").datepicker();
        });
    </script>
</head>
<body>
<div class="row">
	<div class="col-sm-12">
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
					
					
					<div class="col-sm-12">
						<table class="display table table-bordered table-striped">
							<tr>
								
									<td>
									<div class="col-lg-6">
										<strong>Fecha de busqueda inicio:</strong>&#160;</strong>
									</div>
										<form method="post" action="?page=prepaid/billings">
										<div class="col-lg-3">
											<input type="text" name="datepicker" id="datepicker" readonly="readonly" data-date-format="dd-mm-yyyy" size="12" />
										</div>
										
									</td>
									
								
								
								
								
							
								<div class="col-sm-0">
									<td><strong>Fecha de busqueda fin:</strong>&#160;</strong>
										<form method="post" action="?page=prepaid/billings">
										<input type="text" name="datepicker1" id="datepicker2" readonly="readonly" data-date-format="dd-mm-yyyy" size="12" />
									</td> 
								</div>
							</tr>
						</table>
					</div>
						
						
						
						
						
						<table id="customers" align="center">
								<tr align="center"><td><input  type="image" src="backend/images/send.png" alt="Submit Form"/></td></tr>
						</table>
					</div>
				</div>
			
        </section>   
    </div>
</div>
</body>
</html>