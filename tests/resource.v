module hello(clk, rst, req_valid, req_ready);
  input clk;
  input rst;
  input req_valid;
  output req_ready;

  reg req_ready;

  always @(posedge clk) begin
    if (rst) begin
       req_ready <= 0;
    end else begin
      if (req_valid) begin
	if (!req_ready) begin
          $display("hello world");
	end
        req_ready <= 1;
      end else begin
        req_ready <= 0;
      end
    end
  end

endmodule
