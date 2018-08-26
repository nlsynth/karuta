`timescale 1ns/1ns

// $ iverilog fp16bmul.v fp16bmul_test.v

module FP16BMul_Test;

   reg clk, rst;

   reg [15:0] s0_arg_0;
   reg [15:0] s0_arg_1;
   wire       s0_ret_0;
   wire [7:0] s0_ret_1;
   wire [7:0] s0_ret_2;
   wire [8:0] s0_ret_3;
   reg 	       s1_arg_0;
   reg [7:0]   s1_arg_1;
   reg [7:0]   s1_arg_2;
   reg [8:0]  s1_arg_3;
   wire [15:0] s1_ret_0;

   reg 	       xs;
   reg [7:0]   xe;
   reg [6:0]   xf;
   reg 	       ys;
   reg [7:0]   ye;
   reg [6:0]   yf;
   wire        rs;
   wire [7:0]  re;
   wire [6:0]  rf;

   assign rs = s1_ret_0[15:15];
   assign re = s1_ret_0[14:7];
   assign rf = s1_ret_0[6:0];

   FP16BMulS0Of2
     inst_0(.clk(clk), .rst(rst),
	    .arg_0(s0_arg_0), .arg_1(s0_arg_1),
	    .ret_0(s0_ret_0), .ret_1(s0_ret_1), .ret_2(s0_ret_2), .ret_3(s0_ret_3));

   FP16BMulS1Of2
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
      xs <= 0; xe <= 127; xf <= 0;
      ys <= 0; ye <= 127; yf <= 0;
      #1
      $display("1.0*1.0= %d %s", s1_ret_0, (rs == 0 && re == 127 && rf == 0) ? "OK" : "FAIL");

      // 1.5 * 1.5
      xs <= 0; xe <= 127; xf <= 64;
      ys <= 0; ye <= 127; yf <= 64;
      #1
      $display("1.5*1.5= %d %s", s1_ret_0, (rs == 0 && re == 128 && rf == 16) ? "OK" : "FAIL");

      // 1.25 * 1.25
      xs <= 0; xe <= 127; xf <= 32;
      ys <= 0; ye <= 127; yf <= 32;
      #1
      $display("1.25*1.25= %d %s", s1_ret_0, (rs == 0 && re == 127 && rf == 72) ? "OK" : "FAIL");

      // 0.75 * 0.75
      xs <= 0; xe <= 126; xf <= 64;
      ys <= 0; ye <= 126; yf <= 64;
      #1
      $display("0.75*0.75= %d %s", s1_ret_0, (rs == 0 && re == 126 && rf == 16) ? "OK" : "FAIL");
      $display("%d %d %d", rs, re, rf);

      // 2^-14 * 0.5
      xs <= 0; xe <= 1; xf <= 0;
      ys <= 0; ye <= 14; yf <= 0;
      #1
      $display("2^-14*0.5= %d %s", s1_ret_0, (rs == 0 && re == 0 && rf == 0) ? "OK" : "FAIL");

      // 2^192 * 2^192
      xs <= 0; xe <= 192; xf <= 0;
      ys <= 0; ye <= 192; yf <= 0;
      #1
      $display("2^192*2^192= %d %s", s1_ret_0, (rs == 0 && re == 255 && rf == 0) ? "OK" : "FAIL");

      // Use this line to debug a specific case.
      $display("%d %d %d", rs, re, rf);

      #10000
      $display("test done");
      $finish;
   end


endmodule // FP16BMul_Test
