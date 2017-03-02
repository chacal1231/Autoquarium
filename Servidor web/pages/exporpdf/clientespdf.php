<?php
ob_end_clean();
require('../../backend/fpdf/fpdf.php');
require('../../inc/conexion.php');

$pdf = new FPDF('L','mm', 'A4');
$pdf->AddPage();
$pdf->SetFont('Arial', '', 12);
$pdf->Image('../../backend/images/logo.gif',15,15,70,20);
$pdf->Cell(120, 10, '', 0);
$pdf->SetFont('Arial', 'B', 11);
$pdf->Cell(70, 10, 'Grupo SITEL S.A.S', 0);
$pdf->Cell(45, 8, '', 0);
$pdf->SetFont('Arial', '', 9);
$pdf->Cell(50, 10, 'Fecha: '.date('d-m-Y').'', 0);
$pdf->Ln(7);
$pdf->Cell(125, 8, '', 0);
$pdf->Cell(30, 8, 'Nit: 900 706 948-2', 0);
$pdf->Ln(15);
$pdf->SetFont('Arial', 'B', 11);
$pdf->Cell(105, 8, '', 0);
$pdf->Cell(100, 8, 'Clientes Fijos - Grupo SITEL S.A.S', 0);
$pdf->Ln(23);
$pdf->SetFont('Arial', 'B', 8);
$pdf->Cell(8, 8, 'No.', 0);
$pdf->Cell(45, 8, 'Nombre', 0);
$pdf->Cell(25, 8, 'IP', 0);
$pdf->Cell(20, 8, 'Plan', 0);
$pdf->Cell(20, 8, 'Telefono', 0);
$pdf->Cell(50, 8, 'Correo', 0);
$pdf->Cell(20, 8, 'Cedula', 0);
$pdf->Cell(25, 8, 'F. Instalacion', 0);
$pdf->Cell(25, 8, 'F. corte', 0);
$pdf->Cell(25, 8, 'Usuario', 0);
$pdf->Ln(8);
$pdf->SetFont('Arial', '', 8);
//CONSULTA
$clientes = mysql_query("SELECT * FROM clientes");
$item = 0;
$totaluni = 0;
$totaldis = 0;
while($clientes2 = mysql_fetch_array($clientes)){
	$item = $item+1;
	$pdf->Cell(8, 8, $item, 0);
	$pdf->Cell(45, 8,$clientes2['nombre'], 0);
	$pdf->Cell(25, 8, $clientes2['ip'], 0);
	$pdf->Cell(20, 8, $clientes2['plan'], 0);
	$pdf->Cell(20, 8, $clientes2['telefono'], 0);
	$pdf->Cell(50, 8, $clientes2['correo'], 0);
	$pdf->Cell(20, 8, $clientes2['cedula'], 0);
	$pdf->Cell(25, 8, $clientes2['fecha_i'], 0);
	$pdf->Cell(25, 8, $clientes2['fecha_c'], 0);
	$pdf->Cell(25, 8, $clientes2['usuario'], 0);
	$pdf->Ln(8);
}
$pdf->SetFont('Arial', 'B', 8);
$pdf->Output();
?>