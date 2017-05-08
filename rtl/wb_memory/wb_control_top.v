//---------------------------------------------------------------------------
//
// Wishbone BasicIO
//
// Register Description:
//
//    0x00 init
//    0X04 done
//    0x08 start_add
//    0x0C data
//    0x10 rw
//
//---------------------------------------------------------------------------

module wb_control_top (
   input              clk,
   input              rst,
   // Wishbone interface
   input              wb_stb_i,
   input              wb_cyc_i,
   output             wb_ack_o,
   input              wb_we_i,
   input       [31:0] wb_adr_i,
   input        [3:0] wb_sel_i,
   input       [31:0] wb_dat_i,
   output reg  [31:0] wb_dat_o,
   // Control_top Outputs & Inputs
   output signal, //signal to leds
   output done  //Finish flag
   
  );

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
reg  ack;

reg init;
reg [5:0] start_add;
reg [23:0] data;
reg rw;
wire [5:0] w_AD;  //wire addres between modules
wire [23:0] w_data;//Exchange data between modules

ram_using_file ram0 (.clk(clk), .addr_out(w_AD), .rw(rw), .addr_in(start_add), .data_in(data), .data_out(w_data)); //Ram memory
control_led C1 (.clk(clk), .rst(rst), .init(init), .done(done), .data(w_data),.out(signal), .address(w_AD));

//control_top lights0(.clk(clk) , .signal(signal), .done(done), .init(init), .rst(rst), .start_add(start_add), .data(data), .rw(rw));



assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;


  always @(posedge clk)
  begin
    if (rst) begin
      ack      <= 0;
      init      <= 0;
      end else begin

      // Handle WISHBONE access
      ack    <= 0;

     if (wb_rd & ~ack) begin           // read cycle
       ack <= 1;
       case (wb_adr_i[5:0])
       'h04: wb_dat_o <= {31'h0, done};
        default: begin
				 wb_dat_o <= 0;
			  end	
       endcase
       
     end else if (wb_wr & ~ack ) begin // write cycle
       ack <= 1;
       case (wb_adr_i[5:0])
       'h00: init <= wb_dat_i[0];
	  'h08: start_add <= wb_dat_i[5:0];
       'h0C: data <= wb_dat_i[23:0];
       'h10: rw <= wb_dat_i[0];
        default: begin
				 wb_dat_o <= 0;
			  end
       endcase
     end
    end
  end

endmodule
