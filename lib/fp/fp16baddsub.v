// bfloat16
// TODO: Write tests and fix obvious bugs first.
module FP16BAddSubS0Of5(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input [15:0]  arg_1,
 input 	       arg_2,
 output [15:0] ret_0,
 output [15:0] ret_1,
 output        ret_2,
 output        ret_3);

   wire [15:0] x;
   wire [15:0] y;
   wire        is_sub;
   wire        ys;
   wire        yys;
   wire [15:0] yy;
   wire        diff_sign;
   wire [7:0]  xe;
   wire [7:0]  ye;
   wire        swap;
   wire        neg_lhs;
   wire        neg_rhs;
   wire [15:0] lhs;
   wire [15:0] rhs;


   assign x = arg_0;
   assign y = arg_1;
   assign is_sub = arg_2;
   assign ys = y[15];
   assign yys = is_sub ? ~ys : ys;
   assign yy = {yys, y[14:0]};
   assign xe = x[14:7];
   assign ye = y[14:7];

   assign diff_sign = x[15] ^ yy[15];

   assign swap = xe < ye;
   assign lhs = swap ? yy : x;
   assign rhs = swap ? x : yy;

   assign neg_lhs = diff_sign ? lhs[15] : 0;
   assign neg_rhs = diff_sign ? rhs[15] : 0;

   assign ret_0 = lhs;
   assign ret_1 = rhs;
   assign ret_2 = neg_lhs;
   assign ret_3 = neg_rhs;

endmodule // FP16BAddSubS0Of5

module FP16BAddSubS1Of5(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input [15:0]  arg_1,
 input 	       arg_2,
 input 	       arg_3,
 output        ret_0,
 output        ret_1,
 output [14:0] ret_2,
 output [14:0] ret_3,
 output [7:0]  ret_4,
 output        ret_5,
 output        ret_6);

   wire [15:0] x;
   wire [15:0] y;
   wire        xn;
   wire        yn;
   wire [7:0]  xe;
   wire [7:0]  ye;
   wire        x1;
   wire        y1;
   wire [6:0]  xf;
   wire [6:0]  yf;
   wire [14:0] xr;
   wire [14:0] xrn;
   wire [14:0] yr10;
   wire [8:0]  d;
   wire [14:0] yr1;
   wire [14:0] yr2;
   wire [14:0] yr4;
   wire [14:0] yr8;
   wire [14:0] yrn;

   assign x = arg_0;
   assign y = arg_1;
   assign xn = arg_2;
   assign yn = arg_3;
   assign xe = x[14:7];
   assign ye = y[14:7];
   assign xf = x[6:0];
   assign yf = y[6:0];

   assign x1 = xe > 0;
   assign y1 = ye > 0;
   assign xr = {x1, xf, 7'b0};
   assign xrn = xn ? ~xr : xr;
   assign yr10 = {y1, yf, 7'b0};
   assign d = xe - ye;
   // barrel shifter to adjust y.
   assign yr1 = d[0:0] ? {1'b0, yr10[14:1]} : yr10;
   assign yr2 = d[1:1] ? {2'b0, yr1[14:2]} : yr1;
   assign yr4 = d[2:2] ? {4'b0, yr2[14:4]} : yr2;
   assign yr8 = d[3:3] ? {8'b0, yr4[14:8]} : yr4;

   assign yrn = yn ? ~yr8 : yr8;

   assign ret_0 = x[15];
   assign ret_1 = y[15];
   assign ret_2 = xrn;
   assign ret_3 = yrn;
   assign ret_4 = xe;
   assign ret_5 = xn;
   assign ret_6 = yn;

endmodule // FP16BAddSubS1Of5

module FP16BAddSubS2Of5(
 input 	       clk,
 input 	       rst,
 input 	       arg_0,
 input 	       arg_1,
 input [14:0]  arg_2,
 input [14:0]  arg_3,
 input [7:0]   arg_4,
 input 	       arg_5,
 input 	       arg_6,
 output [15:0] ret_0,
 output        ret_1,
 output        ret_2,
 output [7:0]  ret_3,
 output        ret_4,
 output        ret_5);

   wire        xn;
   wire        yn;
   wire [15:0] rxy;
   wire        diff_sign;
   wire [15:0] r_final;


   assign xn = arg_5;
   assign yn = arg_6;
   assign diff_sign = (xn != yn);

   assign rxy = arg_2 + arg_3;
   assign r_final = diff_sign ? (rxy + 1) : rxy;

   assign ret_0 = r_final;
   assign ret_1 = arg_0;
   assign ret_2 = arg_1;
   assign ret_3 = arg_4;
   assign ret_4 = arg_5;
   assign ret_5 = arg_6;


endmodule // FP16BAddSubS2Of5

module FP16BAddSubS3Of5(
 input 	       clk,
 input 	       rst,
 input [15:0]  arg_0,
 input 	       arg_1,
 input 	       arg_2,
 input [7:0]   arg_3,
 input 	       arg_4,
 input 	       arg_5,
 output [14:0] ret_0,
 output        ret_1,
 output        ret_2,
 output [7:0]  ret_3,
 output        ret_4,
 output        ret_5,
 output        ret_6);

   wire [15:0] r;
   wire        xs;
   wire        ys;
   wire [7:0]  e;
   wire        xn;
   wire        yn;
   wire        diff_sign;
   wire        with_carry;
   wire        neg;
   wire [14:0] neg_r;
   wire [14:0] half_r;
   wire [14:0] r_diff;
   wire [14:0] r_same;
   wire [14:0] r_final;
   wire [7:0]  eplus;
   wire [7:0]  e_final;


   assign r = arg_0;
   assign xs = arg_1;
   assign ys = arg_2;
   assign e = arg_3;
   assign xn = arg_4;
   assign yn = arg_5;
   assign diff_sign = (xn != yn);
   assign with_carry = r[15:15];
   assign neg_r = (~r) + 1;
   assign half_r = r[15:1];
   assign neg = diff_sign & !with_carry;
   assign eplus = e + 1;

   assign r_diff = with_carry ? r[14:0] : neg_r;
   assign r_same = with_carry ? half_r : r[14:0];
   assign r_final = diff_sign ? r_diff : r_same;
   assign e_final = (!diff_sign && with_carry) ? eplus : e;

   assign ret_0 = r_final;
   assign ret_1 = xs;
   assign ret_2 = ys;
   assign ret_3 = e_final;
   assign ret_4 = neg;
   assign ret_5 = xn;
   assign ret_6 = yn;

endmodule // FP16BAddSubS3Of5

module FP16BAddSubS4Of5(
 input 	       clk,
 input 	       rst,
 input [14:0]  arg_0,
 input 	       arg_1,
 input 	       arg_2,
 input [7:0]   arg_3,
 input 	       arg_4,
 input 	       arg_5,
 input 	       arg_6,
 output [15:0] ret_0);

   wire [15:0] r;
   wire        xs;
   wire        ys;
   wire [7:0]  e;
   wire [7:0]  e_final;
   wire [8:0]  e_l0adjust;
   wire        underflow;
   wire [7:0]  e_adjust;
   wire        neg;
   wire        xn;
   wire        yn;
   wire [7:0] rr;
   wire [6:0] r_final;
   wire [15:0] r8;
   wire [15:0] r4;
   wire [15:0] r2;
   wire [15:0] r1;
   wire [3:0]  l0count;
   wire        s;

   assign r = arg_0;
   assign xs = arg_1;
   assign ys = arg_2;
   assign e = arg_3;
   assign neg = arg_4;
   assign xn = arg_5;
   assign yn = arg_6;
   assign s = (xn == yn) ? xs : (yn ? (neg ^ xs): (neg ^ ys));

   assign r8 = (r[14:7] == 0) ? {r[6:0], 8'b0} : r;
   assign r4 = (r8[14:11] == 0) ? {r8[10:0], 4'b0} : r8;
   assign r2 = (r4[14:13] == 0) ? {r4[12:0], 2'b0} : r4;
   assign r1 = (r2[14:14] == 0) ? {r2[13:0], 1'b0} : r2;

   assign l0count = {r[14:7] == 0, r8[14:11] == 0, r4[14:13] == 0, r2[14:14] == 0};
   assign rr = (xn == yn) ? r[14:7] : r1;
   assign e_l0adjust = e - l0count;
   assign underflow = e_l0adjust[8:8];
   assign e_adjust = underflow ? 0 : e_l0adjust[7:0];
   assign e_final = (xn == yn) ? e : e_adjust[7:0];
   assign r_final = underflow ? 0 : rr[6:0];

   assign ret_0 = {s, e_final, r_final};

endmodule // FP16BAddSubS4Of5
