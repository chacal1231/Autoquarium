
                <!-- page end-->
                </section>
            </section>
            <!--main content end-->
        <!--right sidebar start-->
        <div class="right-sidebar">
            <div class="search-row">
                <input type="text" placeholder="Search" class="form-control">
            </div>
            <div class="right-stat-bar">
                <ul class="right-side-accordion">
                    <li class="widget-collapsible">
                        <a href="#" class="head widget-head red-bg active clearfix">
                            <span class="pull-left">work progress (5)</span>
                            <span class="pull-right widget-collapse"><i class="ico-minus"></i></span>
                        </a>
                        <ul class="widget-container">
                            <li>
                                <div class="prog-row side-mini-stat clearfix">
                                    <div class="side-graph-info">
                                        <h4>Target sell</h4>
                                        <p>
                                            25%, Deadline 12 june 13
                                        </p>
                                    </div>
                                    <div class="side-mini-graph">
                                        <div class="target-sell">
                                        </div>
                                    </div>
                                </div>
                                <div class="prog-row side-mini-stat">

                                </div>
                                <div class="prog-row side-mini-stat">
                                    
                                </div>
                                <div class="prog-row side-mini-stat">
                                    
                                </div>
                                <div class="prog-row side-mini-stat">

                                </div>
                            </li>
                        </ul>
                    </li>
                </ul>
            </div>
        </div>
        <!--right sidebar end-->
    </section>

<!-- Placed js at the end of the document so the pages load faster -->

<!--Core js-->
<script src="backend/panel/js/jquery.js"></script>
<script src="backend/panel/bs3/js/bootstrap.min.js"></script>
<script class="include" type="text/javascript" src="backend/panel/js/jquery.dcjqaccordion.2.7.js"></script>
<script src="backend/panel/js/jquery.scrollTo.min.js"></script>
<script src="backend/panel/js/jQuery-slimScroll-1.3.0/jquery.slimscroll.js"></script>
<script src="backend/panel/js/jquery.nicescroll.js"></script>

<!--Easy Pie Chart-->
<script src="backend/panel/js/easypiechart/jquery.easypiechart.js"></script>
<!--Sparkline Chart-->
<script src="backend/panel/js/sparkline/jquery.sparkline.js"></script>
<!--jQuery Flot Chart-->
<script src="backend/panel/js/flot-chart/jquery.flot.js"></script>
<script src="backend/panel/js/flot-chart/jquery.flot.tooltip.min.js"></script>
<script src="backend/panel/js/flot-chart/jquery.flot.resize.js"></script>
<script src="backend/panel/js/flot-chart/jquery.flot.pie.resize.js"></script>

<!--dynamic table-->
<script type="text/javascript" language="javascript" src="backend/panel/js/advanced-datatable/js/jquery.dataTables.js"></script>
<script type="text/javascript" src="backend/panel/js/data-tables/DT_bootstrap.js"></script>
<!--common script init for all pages-->

<!--dynamic table initialization -->
<script src="backend/panel/js/dynamic_table_init.js"></script>

<script src="backend/plugin/fp/bootstrap-fileupload.js"></script>

<!--Fusion Charts-->
<script type="text/javascript" src="http://static.fusioncharts.com/code/latest/fusioncharts.js"></script>

<script type="text/javascript">         
    $(document).on('click', '#modal-form-submit', function (e) {
        $('#modal-form').submit();
    });
</script>

<!--datatimepipicker initialization -->
<script src="backend/js/bootstrap-datepicker.js"></script>
<script src="backend/js/bootstrap-timepicker.min.js"></script>
<script type="text/javascript">
    //Initialise datepicker
    $('#datepicker, #datepicker2').datepicker();
    // initialise on document ready
    jQuery(document).ready(function ($) {
        'use strict';

        // CENTERED MODALS
        // phase one - store every dialog's height
        $('.modal').each(function () {
            var t = $(this),
                d = t.find('.modal-dialog'),
                fadeClass = (t.is('.fade') ? 'fade' : '');
            // render dialog
            t.removeClass('fade')
                .addClass('invisible')
                .css('display', 'block');
            // read and store dialog height
            d.data('height', d.height());
            // hide dialog again
            t.css('display', '')
                .removeClass('invisible')
                .addClass(fadeClass);
        });
        // phase two - set margin-top on every dialog show
        $('.modal').on('show.bs.modal', function () {
            var t = $(this),
                d = t.find('.modal-dialog'),
                dh = d.data('height'),
                w = $(window).width(),
                h = $(window).height();
            // if it is desktop & dialog is lower than viewport
            // (set your own values)
            if (w > 380 && (dh + 60) < h) {
                d.css('margin-top', Math.round(0.96 * (h - dh) / 2));
            } else {
                d.css('margin-top', '');
            }
        });

    });
</script>

<!--common script init for all pages-->
<script src="backend/panel/js/scripts.js"></script>

<!--ckeditor-->
<script type="text/javascript" src="backend/plugin/ckeditor/ckeditor.js"></script>
<script type="text/javascript">
   var ckeditor = CKEDITOR.replace('ckeditor',{
        height:'300px',
        filebrowserBrowseUrl : 'backend/plugin/media/browse.php?type=files',
        filebrowserImageBrowseUrl : 'backend/plugin/media/browse.php?type=images',
        filebrowserFlashBrowseUrl : 'backend/plugin/media/browse.php?type=flash',
        filebrowserUploadUrl : 'backend/panel/plugin/upload.php?type=files',
        filebrowserImageUploadUrl : 'backend/plugin/media/upload.php?type=images',
        filebrowserFlashUploadUrl : 'backend/plugin/media/upload.php?type=flash'     
    });
    CKEDITOR.disableAutoInline = true;
    CKEDITOR.inline('editable');        
</script>


</body>
</html>
