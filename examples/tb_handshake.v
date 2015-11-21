//
// $ ../nli handshake.n
// $ iverilog tb_handshake.v handshake.v
//

`timescale 1ns/1ns

module tb_handshake;
   reg clk, rst;
   wire [31:0] channel_out_data;
   wire        channel_out_en;
   reg 	       channel_out_ack;
   reg [31:0]  channel_in_data;
   reg 	       channel_in_en;
   wire        channel_in_ack;

   initial begin
      clk <= 0;
      rst <= 1;
      channel_out_ack <= 0;
      channel_in_data <= 0;
      channel_in_en <= 0;
      #105
	rst <= 0;
      #1000
	$finish;
   end

   always begin
      #10 clk = ~clk;
   end

   always @(posedge clk) begin
      if (!rst) begin
	 if (!channel_in_ack) begin
	    channel_in_data <= 123;
	    channel_in_en <= 1;
	 end else begin
	    channel_in_en <= 0;
	 end
	 if (!channel_out_en) begin
	    channel_out_ack <= 1;
	 end else begin
	    channel_out_ack <= 0;
	    $display("data output %d", channel_out_data);
	 end
      end
   end

   handshake dut(.clk(clk), .rst(rst),
		 .channel_out_data(channel_out_data),
		 .channel_out_en(channel_out_en),
		 .channel_out_ack(channel_out_ack),
		 .channel_in_data(channel_in_data),
		 .channel_in_en(channel_in_en),
		 .channel_in_ack(channel_in_ack));

endmodule
