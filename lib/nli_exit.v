module exit(clk, rst, req, a);
  input clk;
  input rst;
  input req;
  input a;

  always @(posedge clk) begin
    if (rst) begin
    end else begin
      if (req) begin
        $display("exit!");
        $finish();
      end
    end
  end

endmodule
