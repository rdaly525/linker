module top(
  input [17:0] in,
  output [4:0] pop
);

  (* lib="rosslib" *)
  PopCount #(.width(18)) popcount_inst(
    .I(in),
    .O(pop)
  );

endmodule
