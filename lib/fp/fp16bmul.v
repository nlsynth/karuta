// bfloat16 (FP16B) multiplier.
module FP16BMulS0Of2(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input [15:0]  arg_1,
 output        ret_0,
 output [7:0]  ret_1,
 output [7:0]  ret_2,
 output [8:0] ret_3);

   wire        s0;
   wire        s1;
   wire [7:0]  e0;
   wire [7:0]  e1;
   wire [6:0]  f0;
   wire [6:0]  f1;
   wire [7:0] ff0;
   wire [7:0] ff1;
   wire [15:0] z;
   wire [8:0] zz;

   assign s0 = arg_0[15:15];
   assign s1 = arg_1[15:15];
   assign e0 = arg_0[14:7];
   assign e1 = arg_1[14:7];
   assign f0 = arg_0[6:0];
   assign f1 = arg_1[6:0];

   // sign
   assign ret_0 = s0 ^ s1;
   // exponent
   assign ret_1 = e0;
   assign ret_2 = e1;

   assign ff0 = {(e0 == 0 ? 1'b0 : 1'b1), f0};
   assign ff1 = {(e1 == 0 ? 1'b0 : 1'b1), f1};

   assign z = ff0 * ff1;
   assign zz = z[15:7];
   // fraction
   assign ret_3 = zz;

endmodule // FP16BMulS0Of2

module FP16BMulS1Of2(
 input 	       clk,
 input 	       rst,
 input 	       arg_0,
 input [7:0]   arg_1,
 input [7:0]   arg_2,
 input [8:0]  arg_3,
 output [15:0] ret_0);

   wire        s;
   wire        c;
   wire [6:0] fc;
   wire [6:0] uc;
   wire [9:0]  e10;
   wire [7:0]  e;
   wire        underflow;
   wire        overflow;
   wire        infinput;

   assign s = arg_0;
   assign c = arg_3[8:8];
   assign e10 = arg_1 + arg_2 - 127 + c;
   assign fc = c ? arg_3[7:1] : arg_3[6:0];
   assign infinput = (arg_1 == 255) || (arg_2 == 255);
   // e10[9:9] negative by subtraction.
   // e10[8:8] overflow (> 255) by addition.
   assign underflow = e10[9:9];
   assign overflow = !underflow && (e10[8:8] || e10[7:0] == 255 || infinput);

   assign e = underflow ? 0 : (overflow ? 255 : e10[7:0]);
   assign uc = (underflow || e10[7:0] == 0) ? 0 : fc;

   assign ret_0 = {s, e, uc};

endmodule // FP16BMulS1Of2
