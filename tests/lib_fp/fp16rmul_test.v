`timescale 1ns/1ns

// $ iverilog fp16rmul.v fp16rmul_test.v

module FP16RMul_Test;

   reg clk, rst;

   reg [15:0] s0_arg_0;
   reg [15:0] s0_arg_1;
   wire       s0_ret_0;
   wire [4:0] s0_ret_1;
   wire [4:0] s0_ret_2;
   wire [11:0] s0_ret_3;
   reg 	       s1_arg_0;
   reg [4:0]   s1_arg_1;
   reg [4:0]   s1_arg_2;
   reg [11:0]  s1_arg_3;
   wire [15:0] s1_ret_0;

   reg 	       xs;
   reg [4:0]   xe;
   reg [9:0]   xf;
   reg 	       ys;
   reg [4:0]   ye;
   reg [9:0]   yf;
   wire        rs;
   wire [4:0]  re;
   wire [9:0]  rf;

   assign rs = s1_ret_0[15:15];
   assign re = s1_ret_0[14:10];
   assign rf = s1_ret_0[9:0];

   FP16RMulS0Of2
     inst_0(.clk(clk), .rst(rst),
	    .arg_0(s0_arg_0), .arg_1(s0_arg_1),
	    .ret_0(s0_ret_0), .ret_1(s0_ret_1), .ret_2(s0_ret_2), .ret_3(s0_ret_3));

   FP16RMulS1Of2
     inst_1(.clk(clk), .rst(rst),
	    .arg_0(s1_arg_0), .arg_1(s1_arg_1),  .arg_2(s1_arg_2), .arg_3(s1_arg_3),
	    .ret_0(s1_ret_0));

   always @(s0_ret_0 or s0_ret_1 or s0_ret_2 or s0_ret_3) begin
      s1_arg_0 <= s0_ret_0;
      s1_arg_1 <= s0_ret_1;
      s1_arg_2 <= s0_ret_2;
      s1_arg_3 <= s0_ret_3;
      $display("S0: %d %d %d %d", s0_ret_0, s0_ret_1, s0_ret_2, s0_ret_3);
   end

   always @(xs or xe or xf or ys or ye or yf) begin
      s0_arg_0 = {xs, xe, xf};
      s0_arg_1 = {ys, ye, yf};
   end

   initial begin
      clk <= 0;
      rst <= 1;
      #105
      rst <= 0;
      // 0 * 0
      s0_arg_0 <= 0;
      s0_arg_1 <= 0;
      #1
      $display("0.0*0.0= %d %s", s1_ret_0, (s1_ret_0 == 0) ? "OK" : "FAIL");

      // 1.0 * 1.0
      xs <= 0; xe <= 15; xf <= 0;
      ys <= 0; ye <= 15; yf <= 0;
      #1
      $display("1.0*1.0= %d %s", s1_ret_0, (rs == 0 && re == 15 && rf == 0) ? "OK" : "FAIL");

      // 1.5 * 1.5
      xs <= 0; xe <= 15; xf <= 512;
      ys <= 0; ye <= 15; yf <= 512;
      #1
      $display("1.5*1.5= %d %s", s1_ret_0, (rs == 0 && re == 16 && rf == 128) ? "OK" : "FAIL");
      $display("%d %d %d", rs, re, rf);

      // 1.25 * 1.25
      xs <= 0; xe <= 15; xf <= 256;
      ys <= 0; ye <= 15; yf <= 256;
      #1
      $display("1.5*1.5= %d %s", s1_ret_0, (rs == 0 && re == 15 && rf == 576) ? "OK" : "FAIL");

      // 0.75 * 0.75
      xs <= 0; xe <= 14; xf <= 512;
      ys <= 0; ye <= 14; yf <= 512;
      #1
      $display("0.75*0.75= %d %s", s1_ret_0, (rs == 0 && re == 14 && rf == 128) ? "OK" : "FAIL");

      // Use this line to debug a specific case.
      $display("%d %d %d", rs, re, rf);

      #10000
      $display("test done");
      $finish;
   end


endmodule // FP16RMul_Test
