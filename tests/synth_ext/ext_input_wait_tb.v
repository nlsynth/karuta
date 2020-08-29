`timescale 1ns/1ns

module ext_input_wait_tb;

   reg clk, rst;
   reg [31:0] i;

   initial begin
      clk <= 0;
      i <= 0;
      rst <= 1;
      #105;
      rst <= 0;
      #105;
      i <= 123;
      #10000
      $display("ext_input_wait_tb done");
      $finish;
   end

   always begin
      #10 clk = ~clk;
   end

   mod_main m(.clk(clk), .rst(rst), .i(i));

endmodule // ext_input_wait_tb
