module wait_cycles(clk, rst, req, cycles, ack);
   input 	clk;
   input 	rst;
   input 	req;
   input [31:0] cycles;
   output 	ack;

   reg 		ack;

   reg [1:0] 	st;
   reg [31:0] 	cycles_left;

   always @(posedge clk) begin
      if (rst) begin
	 st <= 0;
	 cycles_left <= 0;
	 ack <= 0;
      end else begin
	 case (st)
	   0: begin
	      if (req == 1) begin
		 cycles_left <= cycles;
		 st <= 1;
	      end
	   end
	   1: begin
	      cycles_left <= cycles_left - 1;
	      if (cycles_left == 0) begin
		 st <= 2;
		 ack <= 1;
	      end
	   end
	   2: begin
	      st <= 0;
	      ack <= 0;
	   end
	 endcase
      end
   end

endmodule
