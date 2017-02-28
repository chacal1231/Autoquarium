<script type="text/javascript" src="http://static.fusioncharts.com/code/latest/fusioncharts.js"></script>
<?php
class FusionCharts {
        
        private $constructorOptions = array();

        private $constructorTemplate = '
        <script type="text/javascript">
            FusionCharts.ready(function () {
                new FusionCharts(__constructorOptions__);
            });
        </script>';

        private $renderTemplate = '
        <script type="text/javascript">
            FusionCharts.ready(function () {
                FusionCharts("__chartId__").render();
            });
        </script>
        ';

        // constructor
        function __construct($type, $id, $width = 400, $height = 300, $renderAt, $dataFormat, $dataSource) {
            isset($type) ? $this->constructorOptions['type'] = $type : '';
            isset($id) ? $this->constructorOptions['id'] = $id : 'php-fc-'.time();
            isset($width) ? $this->constructorOptions['width'] = $width : '';
            isset($height) ? $this->constructorOptions['height'] = $height : '';
            isset($renderAt) ? $this->constructorOptions['renderAt'] = $renderAt : '';
            isset($dataFormat) ? $this->constructorOptions['dataFormat'] = $dataFormat : '';
            isset($dataSource) ? $this->constructorOptions['dataSource'] = $dataSource : '';

            $tempArray = array();
            foreach($this->constructorOptions as $key => $value) {
                if ($key === 'dataSource') {
                    $tempArray['dataSource'] = '__dataSource__';
                } else {
                    $tempArray[$key] = $value;
                }
            }
            
            $jsonEncodedOptions = json_encode($tempArray);
            
            if ($dataFormat === 'json') {
                $jsonEncodedOptions = preg_replace('/\"__dataSource__\"/', $this->constructorOptions['dataSource'], $jsonEncodedOptions);
            } elseif ($dataFormat === 'xml') { 
                $jsonEncodedOptions = preg_replace('/\"__dataSource__\"/', '\'__dataSource__\'', $jsonEncodedOptions);
                $jsonEncodedOptions = preg_replace('/__dataSource__/', $this->constructorOptions['dataSource'], $jsonEncodedOptions);
            } elseif ($dataFormat === 'xmlurl') {
                $jsonEncodedOptions = preg_replace('/__dataSource__/', $this->constructorOptions['dataSource'], $jsonEncodedOptions);
            } elseif ($dataFormat === 'jsonurl') {
                $jsonEncodedOptions = preg_replace('/__dataSource__/', $this->constructorOptions['dataSource'], $jsonEncodedOptions);
            }
            $newChartHTML = preg_replace('/__constructorOptions__/', $jsonEncodedOptions, $this->constructorTemplate);

            echo $newChartHTML;
        }

        // render the chart created
        // It prints a script and calls the FusionCharts javascript render method of created chart
        function render() {
           $renderHTML = preg_replace('/__chartId__/', $this->constructorOptions['id'], $this->renderTemplate);
           echo $renderHTML;
        }

    }
    //Temperatura máxima
    $queryTempMax=mysqli_query($link,"SELECT max(temp) FROM temp");
    $rowTemMax=mysqli_fetch_row($queryTempMax);
    $t_max=$rowTemMax['0'];

    //Temperatura mínima
    $queryTempMin=mysqli_query($link,"SELECT min(temp) FROM temp");
    $rowTemMin=mysqli_fetch_row($queryTempMin);
    $t_min=$rowTemMin['0'];

    //Humedad aún por definir
    $h_max=50;
    $h_min=10;

    //Panel solar
    $queryTetha=mysqli_query($link,"SELECT teta FROM teta ORDER by FECHA DESC");
    $rowTetha=mysqli_fetch_row($queryTetha);
    $t=$rowTetha['0'];

    //Panel solar
    $queryFi=mysqli_query($link,"SELECT fi FROM fi ORDER by FECHA DESC");
    $rowFi=mysqli_fetch_row($queryFi);
    $f=$rowFi['0'];


    //Etapa de crecimiento
    $queryEtapa=mysqli_query($link,"SELECT etapa from etapa_cre ORDER BY fecha DESC");
    $rowEtapa=mysqli_fetch_row($queryEtapa);
    $Etapa=$rowEtapa['0'];
?>

<div class="row">
    <div class="col-md-3">
        <div class="mini-stat clearfix">
            <font size="1"><b>Temperatura en el agua</b></font>
            <span class="mini-stat-icon green"><i class="fa fa-thermometer-half"></i></span>
            <div class="mini-stat-info">
               <button type="button" class="btn btn-danger btn-xs"><?=$t_max?> °C</button><font size="2"> Máxima</font><br>
                <button type="button" class="btn btn-info btn-xs"><?=$t_min?>°C</button><font size="2"> Mínima</font>
                </div>
        </div>
    </div>
    <div class="col-md-3">
        <div class="mini-stat clearfix">
            <font size="1"><b>Oxigeno en el agua</b></font>
            <span class="mini-stat-icon tar"><i class="fa fa-tint"></i></span>
            <div class="mini-stat-info">
                <button type="button" class="btn btn-info btn-xs"><?=$h_max?> %</button><font size="2"> Máxima</font><br>
                <button type="button" class="btn btn-danger btn-xs"><?=$h_min?> %</button><font size="2"> Mínima</font>
             
            </div>
        </div>
    </div>
    <div class="col-md-3">
        <div class="mini-stat clearfix">
            <font size="1"><b>Nivel de Co2</b></font> 
            <span class="mini-stat-icon pink"><i class="fa fa-soundcloud"></i></span>
            <div class="mini-stat-info">
            <button type="button" class="btn btn-info btn-xs"><?=$t?>%</button><font size="2"> Máxima</font><br>
                <button type="button" class="btn btn-danger btn-xs"><?=$f?>%</button><font size="2"> Mínima</font>  
            </div>
        </div>
    </div>
    <div class="col-md-3">
        <div class="mini-stat clearfix">
            <font size="1"><b>Calidad del ambiente</b></font>
            <span class="mini-stat-icon green"><i class="fa fa-heart"></i></span>
            <div class="mini-stat-info">
                <button type="button" class="btn btn-info btn-xs"><?=$Etapa?></button><font size="2">  Etapa</font>
                <br>
            </div>
        </div>
    </div>
</div>
 <div class="row">
    <div class="col-sm-6">
        <section class="panel">
            <header class="panel-heading">
               Temperatura en el agua
            </header>
            <div class="panel-body"> 
                <div class="table-responsive">
                    <table class="display table table-bordered table-striped">
                    <html>
   <head>
  </head>

   <body>
    <?php

        // Form the SQL query that returns the top 10 most populous countries
        $result_graph=mysqli_query($link,"SELECT DISTINCT fecha,MAX(temp) as down FROM temp GROUP BY fecha ORDER BY down DESC LIMIT 0,10");
        

        // If the query returns a valid response, prepare the JSON string
        if ($result_graph) {
            // The `$arrData` array holds the chart attributes and data
            $arrData = array(
                  "chart" => array(
                  "caption" => "Temperatura en el agua",
                  "renderAt" => 'chart-container',
                  "xAxisName"=> "Fecha",
                  "yAxisName"=> "Temperatura (En °C)",
                  "paletteColors" => "#c20014",
                  "bgColor" => "#ffffff",
                  "borderAlpha"=> "20",
                  "canvasBorderAlpha"=> "0",
                  "usePlotGradientColor"=> "0",
                  "plotBorderAlpha"=> "10",
                  "showXAxisLine"=> "1",
                  "xAxisLineColor" => "#999999",
                  "showValues" => "1",
                  "divlineColor" => "#999999",
                  "divLineIsDashed" => "1",
                  "showAlternateHGridColor" => "0",
                  "formatnumberscale" => "0",
                  "thousandSeparator" => ".",
                  "numberSuffix"=> " °C",
                  "rotateValues" => "1",
                  "placevaluesInside" => "0",

                )
            );

            $arrData["data"] = array();

            
    // Push the data into the array
            while($row_while = mysqli_fetch_array($result_graph)) {
            array_push($arrData["data"], array(
                "label" => $row_while["fecha"],
                "value" => $row_while["down"],
                )
            );
            }
            /*JSON Encode the data to retrieve the string containing the JSON representation of the data in the array. */

            $jsonEncodedData = json_encode($arrData);

    /*Create an object for the column chart using the FusionCharts PHP class constructor. Syntax for the constructor is ` FusionCharts("type of chart", "unique chart id", width of the chart, height of the chart, "div id to render the chart", "data format", "data source")`. Because we are using JSON data to render the chart, the data format will be `json`. The variable `$jsonEncodeData` holds all the JSON data for the chart, and will be passed as the value for the data source parameter of the constructor.*/

            $columnChart = new FusionCharts("line", "myFirstChart" , "100%", 300, "chart-1", "json", $jsonEncodedData);

            // Render the chart
            $columnChart->render();            
        }

    ?>

    <div id="chart-1"><!-- Fusion Charts will render here--></div>

   </body>

</html>
                    </table>
                </div>
            </div>
        </section>
    </div>

        <div class="col-sm-6">
        <section class="panel">
            <header class="panel-heading">
                Nivel de pH en el agua
            </header>
            <div class="panel-body"> 
                <div class="table-responsive">
                    <table class="display table table-bordered table-striped">
                    <?php
                    $result_graph_mes=mysqli_query($link,"SELECT DISTINCT fecha,MAX(etapa) as down FROM etapa_cre GROUP BY fecha ORDER BY down DESC LIMIT 0,5");

                    $arrData = array(
                    "chart" => array(
                    "paletteColors"=> "#0075c2",
                    "bgColor"=> "#ffffff",
                    "showBorder"=> "0",
                    "showCanvasBorder"=> "0",
                    "plotBorderAlpha"=> "10",
                    "usePlotGradientColor"=> "0",
                    "plotFillAlpha"=> "50",
                    "showXAxisLine"=> "1",
                    "axisLineAlpha"=> "25",
                    "divLineAlpha"=> "10",
                    "showValues"=> "1",
                    "showAlternateHGridColor"=> "0",
                    "captionFontSize"=> "14",
                    "subcaptionFontSize"=> "14",
                    "subcaptionFontBold"=> "0",
                    "toolTipColor"=>"#ffffff",
                    "toolTipBorderThickness"=> "0",
                    "toolTipBgColor"=> "#000000",
                    "toolTipBgAlpha"=> "80",
                    "toolTipBorderRadius"=> "2",
                    "toolTipPadding"=> "5",
                    "caption" => "Nivel de pH en el agua",
                    "yAxisName"=> "pH",
                    "xAxisName"=> "Fecha",
                    "bgColor" => "#ffffff",
                    "showlabels" => "1",
                    "showlegend" => "1",
                    "enablemultislicing" => "1",
                    "slicingdistance" => "15",
                    "showpercentvalues" => "1",
                    "showpercentintooltip" => "0",
                    "formatnumberscale" => "0",
         )
                );

        $arrData["data"] = array();

        while($row_while = mysqli_fetch_array($result_graph_mes)) {
            array_push($arrData["data"], array(
                "label" => $row_while["fecha"],
                "value" => $row_while["down"],
                )
            );
            }
             $jsonEncodedData2 = json_encode($arrData);
             $columnChart = new FusionCharts("area2d", "ex2", "100%", 300, "chart-2", "json", $jsonEncodedData2);
             $columnChart->render();

?>
                    <div id="chart-2"><!-- Fusion Charts will render here--></div>
                    </table>
                    </div>
                    </div>
                    </section>
                    </div>
                    </div>