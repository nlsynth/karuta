//
module print(clk, rst, req, v);
  input clk;
  input rst;
  input req;
  input [31:0] v;

  always @(posedge clk) begin
    if (rst) begin
    end else begin
      if (req) begin
        $display("print %d(%x)", v, v);
      end
    end
  end

endmodule