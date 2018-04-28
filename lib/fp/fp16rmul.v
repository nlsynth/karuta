// FP16 Regular/Relaxed version.
// TODO: Implement overflow/underflow.
module FP16RMulS0Of2(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input [15:0]  arg_1,
 output        ret_0,
 output [4:0]  ret_1,
 output [4:0]  ret_2,
 output [11:0] ret_3);

   wire        s0;
   wire        s1;
   wire [4:0]  e0;
   wire [4:0]  e1;
   wire [9:0]  f0;
   wire [9:0]  f1;
   wire [10:0] ff0;
   wire [10:0] ff1;
   wire [21:0] z;
   wire [11:0] zz;

   assign s0 = arg_0[15:15];
   assign s1 = arg_1[15:15];
   assign e0 = arg_0[14:10];
   assign e1 = arg_1[14:10];
   assign f0 = arg_0[9:0];
   assign f1 = arg_1[9:0];

   // sign
   assign ret_0 = s0 ^ s1;
   // exponent
   assign ret_1 = e0;
   assign ret_2 = e1;

   assign ff0 = {(e0 == 0 ? 1'b0 : 1'b1), f0};
   assign ff1 = {(e1 == 0 ? 1'b0 : 1'b1), f1};

   assign z = ff0 * ff1;
   assign zz = z[21:10];
   // fraction
   assign ret_3 = zz;

endmodule // FP16RMulS0Of2

module FP16RMulS1Of2(
 input 	       clk,
 input 	       rst,
 input 	       arg_0,
 input [4:0]   arg_1,
 input [4:0]   arg_2,
 input [11:0]  arg_3,
 output [15:0] ret_0);

   wire        s;
   wire        c;
   wire [9:0] zc;
   wire [6:0]  e7;
   wire [4:0]  e;

   assign s = arg_0;
   assign c = arg_3[11:11];
   assign zc = c ? arg_3[10:1] : arg_3[9:0];
   assign e7 = arg_1 + arg_2 - 15 + c;

   // e7[6:6] negative by subtraction.
   // e7[5:5] overflow (> 31) by addition.
   assign e = e7[6:6] ? 0 : (e7[5:5] ? 31 : e7[4:0]);

   assign ret_0 = {s, e, zc};

endmodule // FP16RMulS1Of2
