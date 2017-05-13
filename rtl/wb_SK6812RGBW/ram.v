`timescale 1ns / 1ps

module ram #(
    parameter mem_file_name = "none",
    parameter ram_width = 35,
    parameter ram_addwidth = 6
) (          
    input clk, 
    input we,
    input [ram_addwidth-1:0] add,
	 input [ram_addwidth-1:0] add2,
    input [31:0] wd,
    output reg [31:0] rd,
	 output reg [31:0] rd2
);
             
  reg [31:0] BYTE[ram_width-1:0];
  
  initial
     if (mem_file_name != "none")
          $readmemh (mem_file_name, BYTE);
  
  always @ (posedge clk)begin
     rd   <= BYTE[add ];
	  rd2  <= BYTE[add2];
     if(we)begin
       BYTE[add] <= wd;
    end
  end
      
endmodule
