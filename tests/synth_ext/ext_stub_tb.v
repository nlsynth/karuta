`timescale 1ns/1ns

module ext_stub_tb;
   reg clk, rst;

   // req
   wire req_valid;
   reg 	req_ready;
   wire [31:0] req_0;
   wire [31:0] req_1;
   // res
   reg 	res_valid;
   wire res_ready;
   reg [31:0] res_0;

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
	 st <= 0;
	 req_ready <= 0;
	 res_valid <= 0;
	 res_0 <= 0;
      end else begin
	 case (st)
	   0: begin
	      if (req_valid && req_ready) begin
		 st <= 1;
		 req_ready <= 0;
		 res_0 <= req_0 + req_1;
	      end else begin
		 req_ready <= 1;
	      end
	   end
	   1: begin
	      if (res_valid && res_ready) begin
		 res_valid <= 0;
		 st <= 2;
	      end else begin
		 res_valid <= 1;
	      end
	   end
	   2: begin
	   end
	 endcase
      end
   end

   mod_main m(.clk(clk), .rst(rst),
              .f_req_valid(req_valid),
              .f_req_ready(req_ready),
              .f_req_0(req_0),
              .f_req_1(req_1),
              .f_res_valid(res_valid),
              .f_res_ready(res_ready),
              .f_res_0(res_0));

endmodule // ext_stub_tb
