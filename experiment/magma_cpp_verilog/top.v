module top(
  input [15:0] I0,
  input [15:0] I1,
  output [15:0] O
);

  (* namespace="rosslib" *)
  LinkerTest #(.width(16)) linker_test_inst(
    .I0(I0),
    .I1(I1),
    .O(O)
  );

endmodule
