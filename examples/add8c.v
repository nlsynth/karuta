// Combinational circuit to be embedded in add8c.karuta example.
module add8c(clk, rst, arg_0, arg_1, arg_2, ret_0, ret_1);
   input clk;
   input rst;
   input [7:0] arg_0;
   input [7:0] arg_1;
   input [0:0] arg_2;
   output [0:0] ret_0;
   output [7:0] ret_1;

   wire [8:0] 	t;
   assign t = {1'b0, arg_0} + {1'b0, arg_1} + {8'b0, arg_2};
   assign ret_0 = t[8:8];
   assign ret_1 = t[7:0];

endmodule
