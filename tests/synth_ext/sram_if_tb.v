`timescale 1ns/1ns
module sram_if_tb;

   reg clk, rst;

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

   reg [3:0] addr;
   reg 	     wen;
   reg [31:0] wdata;
   wire [31:0] rdata;

   reg [2:0] st;
   always @(posedge clk) begin
      if (rst) begin
	 st <= 0;
	 addr <= 0;
	 wen <= 0;
	 wdata <= 0;
      end else begin
	 $display("st=%d", st);
	 case (st)
	   0: begin
	      addr <= 7;
	      wdata <= 5;
	      wen <= 1;
	      st <= 1;
	   end
	   1: begin
	      addr <= 7;
	      wdata <= 6;
	      wen <= 0;
	      st <= 2;
	   end
	   2: begin
	      $display("rdata %x", rdata);
	      if (rdata != 5) begin
		 $display("ASSERTION FAILURE %x", rdata);
	      end
	      st <= 3;
	   end
	   3: begin
	      $finish();
	   end
	 endcase
      end
   end

   mod_main m(.clk(clk), .rst(rst), .s_addr(addr), .s_wen(wen), .s_rdata(rdata), .s_wdata(wdata));

endmodule // sram_if_tb

