module top_module(
    input [31:0] a,
    input [31:0] b,
    input sub,
    output [31:0] sum
);
    wire c;
    wire [31:0]b_new;
    assign b_new=b^{32{sub}};
    add16 adder1(.a(a[15:0]),.b(b_new[15:0]),.cin(sub),.sum(sum[15:0]),.cout(c));
    add16 adder2(.a(a[31:16]),.b(b_new[31:16]),.cin(c),.sum(sum[31:16]),.cout());

endmodule
