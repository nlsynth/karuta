module hello(clk, rst, req);
  input clk;
  input rst;
  input req;

  always @(posedge clk) begin
    if (rst) begin
      // do nothing
    end else begin
      if (req) begin
        $display("hello world");
      end
    end
  end

endmodule
