module control_led( clk , rst , init , done , data , out, address );


 input clk;
 input rst;
 input init; 
 input [23:0] data;

 output reg done;
 output reg out;
 output reg [5:0] address;
 

 parameter READY  = 3'b000;
 parameter READ  = 3'b001;
 parameter H0  = 3'b010;
 parameter L0  = 3'b011;
 parameter H1  = 3'b100;
 parameter L1  = 3'b101;
 parameter COUNT= 3'b110;
 parameter RESET  = 3'b111;
 parameter T0H = 18;
 parameter T1H = 35;
 parameter T0L = 40;
 parameter T1L = 30;
 parameter RES = 2500;
 
 reg [2:0] state;
 reg [15:0] timer;
 reg [4:0] i;
 reg en;
 reg [5:0] count_led;
 
 initial begin
  done = 0;
  state = READY;
  timer= 0;
  i=0;
  out=0;
  address = 0;
  en = init;
  count_led=0;
 end

reg [3:0] count;

always @(posedge clk) begin
    
    if (rst) begin
      state = READY;
    end else begin

    case(state)

     READY:begin
     i=0;
  	en = init; 
     if(en)begin
       state = READ; 
       end    
     else
     state = READY;    
        end

     READ: 
      if(data[i])begin
        state = H1;
        timer = T1H;
        done=0;
        end
      else
        begin     
        state = H0;
        timer = T0H;
        done=0;
        end
     H0: begin
     done=0;
     out = 1'bz;
     timer=timer-1;
      if(timer==0)begin
        state = L1;
        timer = T0L;
        end
      else
        state = H0; 
     end    
     L0: begin
     done=0;
     out=0;
     timer=timer-1;
      if(timer==0)begin
     i = i+1;
     if (i==24)begin       
        state = COUNT;
        timer = RES;
        end
        else state = READ;
        end
      else
        state = L0;
     end   
     H1: begin
     done=0;
     out = 1'bz;
     timer=timer-1;
      if(timer==0)begin
        state = L1;
        timer = T1L;
        end
      else
        state = H1;
     end
     L1: begin
     done=0;
     out=0;
     timer=timer-1;
      if(timer==0)begin
     i = i+1;
     if (i==24)begin       
        state = COUNT;
        timer = RES;
        end
        else state = READ;
        end
      else
        state = L1;
     end
     COUNT:begin
			i=0;
          if(count_led==15)begin
    			state=RESET;
    			count_led=0;
   		end
    		else begin
    			count_led = count_led + 1;
    			state=READ;
    		end

    address=address+1;
    done=0;
     end

     RESET: begin
      done=0;
      timer = timer - 1;
      
      if (timer==0)begin
  		done = 1;  
   		address=0;
      	state = READY;
      end
     end

     default: state = READY;
     
   endcase
   end
 end

endmodule
