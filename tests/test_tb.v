// This script is invoked from run-test script
//

`timescale 1ns/1ns
`ifdef KARUTA_RAM
`include "mem16k.v"
`endif

module test_tb;

  reg clk, rst;

  initial begin
    clk <= 0;
    rst <= 1;
    #105
    $display("test_tb start");
    rst <= 0;
    #100000
`ifdef LONG_SIM
    #1000000
`endif
    $display("test_tb done");
    $finish;
  end

  always begin
`ifdef KARUTA_DEBUG
    #10 clk = ~clk;
    #9 clk = ~clk;
     $display("--------");
`else
    #10 clk = ~clk;
`endif
  end

`ifdef KARUTA_RAM
  wire [31:0] addr;
  wire write_en;
  wire [31:0] wdata;
  wire [31:0] rdata;
  mem16k mem(.clk_i(clk), .rst_i(rst),
   .addr_i(addr[31:2]), .write_en_i(write_en),
   .wdata_i(wdata), .rdata_o(rdata));
`endif

  mod_main m(.clk(clk), .rst(rst)
`ifdef KARUTA_RAM1
, .addr_o(addr), .write_en_o(write_en), .data_o(wdata), .data_i(rdata)
`endif
`ifdef KARUTA_RAM2
, .sram_addr(addr), .sram_wdata_en(write_en), .sram_wdata(wdata), .sram_rdata(rdata)
`endif
  );

endmodule
