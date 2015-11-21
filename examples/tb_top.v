//
// iverilog -DNO_DEBUG tb_top.v ...
//
//
`timescale 1ns/1ns
module tb_top;

 reg clk, rst;
 wire [31:0] addr;
 wire write_en;
 wire [31:0] wdata;
 wire [31:0] rdata;

 initial begin
   clk <= 0;
   rst <= 1;
   #105
   rst <= 0;
   #1000
   $finish;
 end

 always begin
   #10 clk = ~clk;
 end

`ifndef NO_DEBUG
 always @(posedge clk) begin
   $display("time %t, %d %d", $time, rst, dut.top_main_inst.cur_st);
 end
`endif

 top dut(.clk(clk), .rst(rst)
`ifndef NO_MEMORY
       ,
       .addr_o(addr), .write_en_o(write_en),
       .data_o(wdata), .data_i(rdata)
`endif
      );

`ifndef NO_MEMORY
 mem16k mem(.clk_i(clk), .rst_i(rst),
            .addr_i(addr[31:2]), .write_en_i(write_en),
            .wdata_i(wdata), .rdata_o(rdata));
`endif

endmodule


// 1word = 4bytes
module mem16k(clk_i, rst_i, addr_i, write_en_i, wdata_i, rdata_o);
  input clk_i, rst_i;
  input [29:0] addr_i;
  input write_en_i;
  input [31:0] wdata_i;
  output [31:0] rdata_o;

  reg [31:0] storage[0:4095];

  integer i;

  initial begin
`ifndef NO_DEBUG
    $display("mem16k init");
`endif
    for (i = 0; i < 4096; i = i + 1) begin
      storage[i] = 0;
    end
  end

  always @(posedge clk_i) begin
    if (rst_i) begin
    end else begin
//      $display("%t mem:read addr=%x,data=%x", $time, addr_i<<2, storage[addr_i[11:0]]);
      if (write_en_i) begin
//        $display("%t mem:write addr=%x,data=%x\n", $time, addr_i<<2, wdata_i);
        storage[addr_i[11:0]] <= wdata_i;
      end
    end
  end

  assign rdata_o = storage[addr_i[11:0]];

endmodule
