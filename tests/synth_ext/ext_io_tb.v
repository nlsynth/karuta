`timescale 1ns/1ns

module ext_io_tb;

   reg clk, rst;
   wire [3:0] led;

   initial begin
      clk <= 0;
      rst <= 1;
      #105;
      rst <= 0;
      #10000
      $display("test_tb done");
      $finish;
   end

   always begin
      #10 clk = ~clk;
   end

   mod_main m(.clk(clk), .rst(rst), .led(led), .in(led));

endmodule // ext_io_tb
