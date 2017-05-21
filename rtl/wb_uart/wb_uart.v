//---------------------------------------------------------------------------
// Wishbone UART 
//
// Register Description:
//
//    0x00 UCR      [ 0 | 0 | 0 | tx_busy | 0 | 0 | rx_error | rx_avail ]
//    0x04 DATA
//
//---------------------------------------------------------------------------

module wb_uart #(
	parameter          clk_freq = 100000000,
	parameter          baud     = 115200
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
	// Serial Wires
	input              uart_rxd,
	output             uart_txd
);

//---------------------------------------------------------------------------
// Actual UART engine
//---------------------------------------------------------------------------
wire [7:0] rx_data;
wire       rx_avail;
wire       rx_error;
reg        rx_ack;
reg [7:0] tx_data;
reg        tx_wr;
wire       tx_busy;

uart #(
	.freq_hz(   clk_freq ),
	.baud(      baud     )
) uart0 (
	.clk(       clk      ),
	.reset(     reset    ),
	//
	.uart_rxd(  uart_rxd ),
	.uart_txd(  uart_txd ),
	//
	.rx_data(   rx_data  ),
	.rx_avail(  rx_avail ),
	.rx_error(  rx_error ),
	.rx_ack(    rx_ack   ),
	.tx_data(   tx_data  ),
	.tx_wr(     tx_wr    ),
	.tx_busy(   tx_busy  )
);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
wire [7:0] ucr = { 3'b0, tx_busy, 2'b0, rx_error, rx_avail };

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

reg  ack;

assign wb_ack_o       = wb_stb_i & wb_cyc_i & ack;


always @(posedge clk)
begin
	if (reset) begin
		wb_dat_o[31:8] <= 24'b0;
		tx_wr  <= 0;
		rx_ack <= 0;
		ack    <= 0;
		// Handle WISHBONE access
	end else begin
		wb_dat_o[31:8] <= 24'b0;
		tx_wr  <= 0;
		rx_ack <= 0;
		ack    <= 0;

		if (wb_rd & ~ack) begin //Ciclo lectura
			ack <= 1;
			case (wb_adr_i[7:0])
				'h00: begin
					wb_dat_o[7:0] <= ucr;
				end
				'h04: begin
					wb_dat_o[7:0] <= rx_data;
					rx_ack 		  <= 1;
				end
				'h08: begin
					wb_dat_o[0] <= rx_avail;
				end
				'h0C: begin
					wb_dat_o[0] <= tx_busy;
				end
			default: begin
				wb_dat_o[7:0] <= 8'b0;
			end
			endcase
		end else if (wb_wr & ~ack ) begin //Ciclo de escritura
			ack <= 1;
			case (wb_adr_i[7:0])
		  		'h10: begin
		           tx_data <= wb_dat_i[7:0];
		  	   end
		  		'h14: begin
		  			if(~tx_busy) begin
			  			tx_wr <= wb_dat_i[0];
			  	   end
			  	   else tx_wr <= 0;
		  	   end
		  default: begin
				tx_data <= 0;
		  		end   
		  	endcase
		end
	end
end


endmodule