`timescale 1ns/1ns

// This assumes the DUT to has 1 master and 1 slave AXI IF.
// // e.g.
// @AxiMaster()
// var M.a int[16]
//
// @AxiSlave()
// var M.b int[16]
//
// @ThreadEntry()
// def M.t() { ... }
//
// M.compile()
// M.writeHdl("/tmp/a.v")

module axi_tb;
   reg clk, rst;
   wire [31:0] ARADDR;
   wire        ARVALID;
   wire        ARREADY;
   wire [7:0]  ARLEN;
   wire [2:0]  ARSIZE;
   wire        RVALID;
   wire [31:0] RDATA;
   wire        RREADY;
   wire        RLAST;
   wire [31:0] AWADDR;
   wire        AWVALID;
   wire        AWREADY;
   wire [7:0]  AWLEN;
   wire [2:0]  AWSIZE;
   wire        WVALID;
   wire        WREADY;
   wire [31:0] WDATA;
   wire        WLAST;
   wire        BVALID;
   wire        BREADY;
   wire [1:0]  BRESP;

  initial begin
    clk <= 0;
    rst <= 1;
    #15
    rst <= ~rst;
    #10000
    $finish;
  end

  always begin
    #10 clk = ~clk;
  end

   main main_inst(.clk(clk), .rst(rst),
		  .a_ARADDR(ARADDR), .b_ARADDR(ARADDR),
		  .a_ARVALID(ARVALID),. b_ARVALID(ARVALID),
		  .a_ARREADY(ARREADY), .b_ARREADY(ARREADY),
		  .a_ARLEN(ARLEN), .b_ARLEN(ARLEN),
		  .a_ARSIZE(ARSIZE), .b_ARSIZE(ARSIZE),
		  .a_RVALID(RVALID), .b_RVALID(RVALID),
		  .a_RDATA(RDATA), .b_RDATA(RDATA),
		  .a_RREADY(RREADY), .b_RREADY(RREADY),
		  .a_RLAST(RLAST), .b_RLAST(RLAST),
		  .a_AWADDR(AWADDR), .b_AWADDR(AWADDR),
		  .a_AWVALID(AWVALID), .b_AWVALID(AWVALID),
		  .a_AWREADY(AWREADY), .b_AWREADY(AWREADY),
		  .a_AWLEN(AWLEN), .b_AWLEN(AWLEN),
		  .a_AWSIZE(AWSIZE), .b_AWSIZE(AWSIZE),
		  .a_WVALID(WVALID), .b_WVALID(WVALID),
		  .a_WREADY(WREADY), .b_WREADY(WREADY),
		  .a_WDATA(WDATA), .b_WDATA(WDATA),
		  .a_WLAST(WLAST), .b_WLAST(WLAST),
		  .a_BVALID(BVALID), .b_BVALID(BVALID),
		  .a_BREADY(BREADY), .b_BREADY(BREADY),
		  .a_BRESP(BRESP), .b_BRESP(BRESP)
);
   initial begin
     $dumpfile("/tmp/axi.vcd");
     $dumpvars(0, main_inst);
   end

endmodule // axi_tb
