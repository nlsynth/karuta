module assert(clk, rst, req, a);
  input clk;
  input rst;
  input req;
  input a;

  always @(posedge clk) begin
    if (rst) begin
    end else begin
      if (req) begin
        if (!a) begin
          $display("ASSERTION FAILURE");
        end
	if (a !== 0 && a !== 1) begin
          $display("ASSERTION UNDEFINED(x)");
	end
`ifndef NO_DEBUG
	if (a) begin
	  $display("ASSERTION PASS %t", $time);
	end
`endif
      end
    end
  end

endmodule
