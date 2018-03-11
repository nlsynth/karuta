module karuta_exit(clk, rst, req_valid, req_ready);
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
        $display("exit!");
        $finish();
      end
    end
  end

endmodule
