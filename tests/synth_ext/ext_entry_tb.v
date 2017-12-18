`timescale 1ns/1ns

module ext_io_tb;
   reg clk, rst;

   // req
   reg req_valid;
   wire req_ready;
   wire req_busy;
   reg [31:0] req_0;
   reg [31:0] req_1;
   // res
   wire res_valid;
   reg 	res_ready;
   wire [63:0] res_0;

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

   reg [2:0] st;
   always @(posedge clk) begin
      if (rst) begin
	 req_valid <= 0;
	 req_0 <= 0;
	 req_1 <= 0;
	 res_ready <= 0;
	 st <= 0;
      end else begin
	 case (st)
           0: begin
	      req_valid <= 1;
	      req_0 <= 1;
	      req_1 <= 2;
	      st <= 1;
	   end
	   1: begin
	      if (req_ready) begin
		 req_valid <= 0;
		 res_ready <= 1;
		 st <= 2;
	      end
	   end
	   2: begin
	      if (res_valid) begin
		 res_ready <= 0;
		 if (res_0 != 64'h0000000100000002) begin
		    $display("ASSERTION FAILURE %x", res_0);
		 end
		 st <= 2;
	      end
	   end
	   3: begin
	   end
	 endcase
      end
   end

   mod_main m(.clk(clk), .rst(rst),
	      .f_req_valid(req_valid), .f_req_ready(req_ready),
	      .f_req_busy(req_busy),
	      .f_req_0(req_0), .f_req_1(req_1),
	      .f_res_valid(res_valid), .f_res_ready(res_ready),
	      .f_res_0(res_0));

endmodule // ext_io_tb
