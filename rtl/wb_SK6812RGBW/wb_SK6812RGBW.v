//---------------------------------------------------------------------------
//
// Wishbone SK6812RGBW
//
// Register Description:
//
//    0x0000 SK6812RGBW_n_bits : Numero de bits que se van a escribir con led_control n_leds=n_bits/32
//    0x0004 SK6812RGBW_data_led : registro de 32 bits que corresponde a los colores GRB_W; green, red, blue, white  
//    0x0008 SK6812RGBW_source : 0 data_led, 1 memoria ram
//    0x000C SK6812RGBW_busy : 1 SK6812RGBW busy
//    0x1xxx SK6812RGBW_ram : direcciones de memoria ram
//
//---------------------------------------------------------------------------

module wb_SK6812RGBW #(
    parameter ram_width = 35,
    parameter ram_addwidth = 6
) (
   input              clk,
   input              reset,
   // Wishbone interface
   input              wb_stb_i,
   input              wb_cyc_i,
   output             wb_ack_o,
   input              wb_we_i,
   input       [31:0] wb_adr_i,
   input        [3:0] wb_sel_i,
   input       [31:0] wb_dat_i,
   output reg  [31:0] wb_dat_o,
   // SK6812RGBW Output
   output led_control
);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

reg [10:0] n_bits;
reg [31:0] data_led;
wire [31:0] rd;
reg source;
wire busy;
wire we_sk  = wb_wr & (wb_adr_i[15:0]==16'h0004);
wire we_ram = wb_wr & (wb_adr_i[12]==1'b1);

SK6812RGBW #(
    .ram_width(ram_width),
    .ram_addwidth(ram_addwidth)
) SK6812RGBW (
.clk(clk),
.reset(reset),
.we(we_sk),
.we_ram(we_ram),
.add(wb_adr_i[ram_addwidth-1:0]),
.data_led(data_led),
.data_ram(wb_dat_i),
.n_bits(n_bits),
.source(source),
.busy(busy),
.rd(rd),
.led_control(led_control));

  always @(posedge clk)
  begin
    if (reset) begin
      ack         <= 0;
      n_bits      <= 0;
      data_led    <= 0;
      source      <= 0;
    end else begin

      // Handle WISHBONE access
      ack    <= 0;

     if (wb_rd & ~ack) begin           // read cycle
       ack <= 1;
       case (wb_adr_i[15:0])
       'h000C:  wb_dat_o           <= {31'h0,busy};
       default: wb_dat_o           <= rd;
       endcase
     end else if (wb_wr & ~ack ) begin // write cycle
       ack <= 1;
       case (wb_adr_i[15:0])
       'h0000: n_bits[10:0]     <= wb_dat_i[10:0];
       'h0004: data_led[31:0]   <= wb_dat_i[31:0];
       'h0008: source           <= wb_dat_i[0];
       endcase
     end
    end
  end

endmodule
