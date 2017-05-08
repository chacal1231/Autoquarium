module ram_using_file #(             //-- Parametros
         parameter AW = 6,   //-- Bits de las direcciones (Adress width)
         parameter DW = 24)   //-- Bits de los datos (Data witdh)

       (        //-- Puertos
         input clk,                      //-- Señal de reloj global
         input [AW-1: 0] addr_out,      //-- Direcciones
         input wire rw,                  //-- Modo lectura (1) o escritura (0)
         input wire [AW-1: 0] addr_in,
         input wire [DW-1: 0] data_in,   //-- Dato de entrada
         output reg [DW-1: 0] data_out); //-- Dato a escribir

//-- Parametro: Nombre del fichero con el contenido de la RAM
parameter ROMFILE = "memory.ram";

//-- Calcular el numero de posiciones totales de memoria
localparam NPOS = 2 ** AW;

  //-- Memoria
  reg [23: 0] ram [0: 13];
//
always @(posedge clk ) begin
	if (rw) begin
		data_out = ram[addr_out];	
	end
	else begin
		ram[addr_in]=data_in;
	end
end


initial begin
  //$readmemh(ROMFILE, ram);
	ram[0]=24'hFF0000;
	ram[1]=24'hFF0000;
	ram[2]=24'hFF0000;
	ram[3]=24'hFF0000;
	ram[4]=24'hFF0000;
	ram[5]=24'hFF0000;
	ram[6]=24'hFF0000;
	ram[7]=24'hFF0000;
	ram[8]=24'hFF0000;
	ram[9]=24'hFF0000;
	ram[10]=24'hFF0000;
	ram[11]=24'hFF0000;
	ram[12]=24'hFF0000;
	ram[13]=24'hFF0000;
end

endmodule
