module top(
  input clk,
  output [2:0] slow
);
  wire [3:0] fast_out;

  (* namespace="mantle", has_en="Bool"*)
  counter #(.width(4), .has_en(0)) fast_inst(
    .clk(clk),
    .out(fast_out)
  );
  
  wire fast_overflow;
  assign fast_overflow = (fast_out == 4'b1111);

  (* namespace="mantle", has_en="Bool"*)
  counter #(.width(3), .has_en(1)) slow_inst(
    .clk(clk),
    .en(fast_overflow),
    .out(slow)
  );

endmodule
