// FP16 Regular/Relaxed version.
// TODO: Finish the implementation.
// TODO: Write tests and fix obvious bugs first.
module FP16RAddSubS0Of4(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input [15:0]  arg_1,
 input 	       arg_2,
 output [15:0] ret_0, // lhs
 output [15:0] ret_1, // rhs
 output        ret_2, // is_sub
 output        ret_3, // neg_lhs
 output        ret_4  // neg_rhs
);

   wire        is_sub;
   wire [4:0]  e0;
   wire [4:0]  e1;
   wire        s0;
   wire        s1;
   wire        swap;
   wire        diff_sign;

   assign is_sub = arg_2;
   assign e0 = arg_0[14:10];
   assign e1 = arg_0[14:10];
   assign s0 = arg_0[15];
   assign s1 = arg_0[15];
   assign diff_sign = s0 ^ s1;
   assign swap = e0 < e1;

   assign ret_0 = swap ? arg_1 : arg_0;
   assign ret_1 = swap ? arg_0 : arg_1;
   assign ret_2 = arg_2;
   // neg lhs
   assign ret_3 = (swap & is_sub) || (swap && !is_sub && diff_sign && s1);
   // neg rhs
   assign ret_4 = (!swap & is_sub) || (swap && !is_sub && diff_sign && s0);
   
endmodule // FP16RAddSubS0Of4

module FP16RAddSubS1Of4(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0, // LHS
 input [15:0]  arg_1, // RHS
 input 	       arg_2, // is_sub
 input 	       arg_3, // neg_lhs
 input 	       arg_4, // neg_rhs
 output [11:0] ret_0, // xf
 output [20:0] ret_1, // yf
 output [4:0]  ret_2, // xe
 output        ret_3  // is_sub
);

   wire [4:0] xe;
   wire [10:0] xf;
   wire        x1;
   wire [4:0]  ye;
   wire [10:0] yf;
   wire        y1;
   wire [20:0] yr0;
   wire        is_sub;
   wire [4:0]  d;
   wire [20:0] yr1;
   wire [20:0] yr2;
   wire [20:0] yr4;
   wire [20:0] yr8;
   wire [20:0] yr16;
   
   assign xe = arg_0[4:0];
   assign ye = arg_1[4:0];
   assign x1 = (xe != 0);
   assign y1 = (xe != 0);
   assign xf = {x1,arg_0[9:0]};
   assign yf = {y1,arg_1[9:0]};
   assign d = xe - ye;
   assign yr0 = {yf, 10'b0};
   assign is_sub = arg_2;
   // barrel shifter.
   assign yr1 = d[0:0] ? {1'b0, yr0[20:1]} : yr0;
   assign yr2 = d[1:1] ? {2'b0, yr1[20:2]} : yr1;
   assign yr4 = d[2:2] ? {4'b0, yr2[20:4]} : yr2;
   assign yr8 = d[3:3] ? {8'b0, yr4[20:8]} : yr4;
   assign yr16 = d[4:4] ? {16'b0, yr8[20:16]} : yr8;

   assign ret_0 = arg_3 ? xf : ~xf;
   assign ret_1 = arg_4 ? yr16 : ~yr16;
   assign ret_2 = xe;
   assign ret_3 = is_sub;

endmodule // FP16RAddSubS1Of4

module FP16RAddSubS2Of4(
 input 	       clk,
 input 	       rst,
 input [11:0]  arg_0, // xf
 input [20:0]  arg_1, // yf
 input [4:0]   arg_2, // xe
 input 	       arg_3, // is_sub
 output [4:0]  ret_0,
 output [21:0] ret_1,
 output        ret_2
);
   wire [21:0] r;
   wire [4:0]  xe;
   wire [11:0] xf;
   wire [20:0] yf;
   wire        is_sub;

   assign xf = arg_0;
   assign yf = arg_1;
   assign xe = arg_2;
   assign is_sub = arg_3;
   assign r = {1'b0, xf, 10'b0} + {1'b0 + yf};

   assign ret_0 = xe;
   assign ret_1 = r[21:0];
   assign ret_2 = is_sub;
   
endmodule // FP16RAddSubS2Of4

module FP16RAddSubS3Of4(
 input 	       clk,
 input 	       rst,
 input [4:0]   arg_0, // exp
 input [21:0]  arg_1, // result
 input 	       arg_2, // is_sub
 output [15:0] ret_0);

   wire        is_sub;
   wire        has_carry;
   wire [4:0]  ep;
   wire [4:0]  ep0;

   assign is_sub = arg_2;
   assign has_carry = !is_sub && arg_1[21];
   assign ep = arg_0;
   assign ep0 = has_carry ? ep + 1 : ep;

   assign ret_0 = {1'b0, ep0, arg_1[21:12]};

   // TODO: Remove leading 0s after subtraction.
   
endmodule // FP16RAddSubS3Of4
