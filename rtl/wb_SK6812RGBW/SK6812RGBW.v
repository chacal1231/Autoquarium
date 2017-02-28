`timescale 1ns / 1ps

module SK6812RGBW #(
    parameter ram_width = 35,
    parameter ram_addwidth = 6
) (                  
    input clk,
    input reset,
    input we,
    input we_ram,
    input [ram_addwidth-1:0] add,
    input [31:0] data_led,
    input [31:0] data_ram,
    input [10:0] n_bits,
    input source,
    output busy,
    output [31:0] rd,
    output led_control);
                     
                     
  reg [2:0] state, nextstate;
  reg [3:0] count;
  reg [11:0] count2;
  reg [10:0] nbits;
  reg flag300ns;
  reg flag80us;
  wire bit_trans;
  reg [31:0] data_register;
  reg [ram_addwidth-1:0] add_ram;
  reg [4:0] bit_ram;
  wire [31:0] rd2;

  parameter S0 = 3'b000;
  parameter S1 = 3'b001;
  parameter S2 = 3'b010;
  parameter S3 = 3'b011;
  parameter S4 = 3'b100;
  parameter S5 = 3'b101;
  parameter S6 = 3'b110;
  parameter S7 = 3'b111;
  
  ram #(
    .ram_width(ram_width),
    .ram_addwidth(ram_addwidth)
  ) ram(          
    .clk(clk), 
    .we(we_ram),
    .add(add),
	  .add2(add_ram),
    .wd(data_ram),
    .rd(rd),
	 .rd2(rd2)
);
  
  assign bit_trans = (source) ? rd2[bit_ram] : data_register[31];
  
  always @ (posedge clk, posedge reset)
    if (reset)begin
      flag300ns <= 0;
      count <= 0;
    end
    else if (count==14)begin
      flag300ns <= 1;
      count <= 0;
    end
    else begin
      count <= count + 1'b1;
      flag300ns <= 0;
    end

  always @ (posedge clk, posedge reset)
    if (reset)begin
      flag80us <= 0;
      count2 <= 0;
    end
    else if (count2==4000)begin
      flag80us <= 1;
      count2 <= 0;
    end
    else if (state == S7)begin
      count2 <= count2 + 1'b1;
    end
    else begin
      flag80us <= 0;
    end

  always @ (posedge clk, posedge reset)
    if (reset)begin
      data_register <= 0;
      nbits <= 0;
      add_ram <= 0;
      bit_ram <= 0;
    end
    else if (we)begin
      data_register <= data_led;
      nbits <= 0;
      add_ram <= 0;
      bit_ram <= 31;
    end
    else if (state == S6)begin
      data_register <= {data_register[30:0],bit_trans};
      nbits <= nbits + 1'b1;
      if(bit_ram == 0)begin
        add_ram <= add_ram + 1'b1;
        bit_ram <= 31;
      end
      else begin
        bit_ram <= bit_ram - 1'b1;
      end
    end

  // state register
  always @ (posedge clk, posedge reset)
    if (reset) state <= S0;
    else       state <= nextstate;
  
  
  // next state logic
  always @ (*)
    case (state)
      S0: if (we) nextstate = S1;
          else    nextstate = S0;
      S1: if (source == 0 && nbits == n_bits)                               nextstate = S7;
          else if (source == 1 && add_ram == (ram_width-1) && bit_ram == 0) nextstate = S7;
          else if (flag300ns)                                               nextstate = S2;
          else                                                              nextstate = S1;
      S2: if (bit_trans && flag300ns)       nextstate = S3;
          else if (~bit_trans && flag300ns) nextstate = S4;
          else                              nextstate = S2;
      S3: if (flag300ns) nextstate = S5;
          else           nextstate = S3;
      S4: if (flag300ns) nextstate = S5;
          else           nextstate = S4;
      S5: if (flag300ns) nextstate = S6;
          else           nextstate = S5;
      S6:                nextstate = S1;
      S7: if (flag80us)  nextstate = S0;
          else           nextstate = S7;
      default:   nextstate = S0;
    endcase
    
    
  // output logic
  assign led_control = (state == S2 || state == S3);
  assign busy = ~(state == S0);
  
endmodule
 
