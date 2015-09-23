// 1word = 4bytes
module mem16k(clk_i, rst_i, addr_i, write_en_i, wdata_i, rdata_o);
  input clk_i, rst_i;
  input [29:0] addr_i;
  input write_en_i;
  input [31:0] wdata_i;
  output [31:0] rdata_o;

  reg [31:0] storage[0:4095];

  integer i;

  initial begin
`ifndef NO_DEBUG
    $display("mem16k init");
`endif
    for (i = 0; i < 4096; i = i + 1) begin
      storage[i] = 0;
    end
  end

  always @(posedge clk_i) begin
    if (rst_i) begin
    end else begin
//      $display("%t mem:read addr=%x,data=%x", $time, addr_i<<2, storage[addr_i[11:0]]);
      if (write_en_i) begin
//        $display("%t mem:write addr=%x,data=%x\n", $time, addr_i<<2, wdata_i);
        storage[addr_i[11:0]] <= wdata_i;
      end
    end
  end

  assign rdata_o = storage[addr_i[11:0]];

endmodule
