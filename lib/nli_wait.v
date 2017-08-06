module wait_cycles(clk, rst, req_valid, req_0, req_ready);
   input 	clk;
   input 	rst;
   input 	req_valid;
   input [31:0] req_0;
   output 	req_ready;

   reg 		req_ready;

   reg [1:0] 	st;
   reg [31:0] 	cycles_left;

   always @(posedge clk) begin
      if (rst) begin
	 st <= 0;
	 cycles_left <= 0;
	 req_ready <= 0;
      end else begin
	 case (st)
	   0: begin
	      if (req_valid == 1) begin
		 cycles_left <= req_0;
		 st <= 1;
	      end
	   end
	   1: begin
	      cycles_left <= cycles_left - 1;
	      if (cycles_left == 0) begin
		 st <= 2;
		 req_ready <= 1;
	      end
	   end
	   2: begin
	      st <= 0;
	      req_ready <= 0;
	   end
	 endcase
      end
   end

endmodule
