module top_module(
    input [399:0] a, b,
    input cin,
    output cout,
    output [399:0] sum
);

    wire [99:0] c;
    genvar i;

    generate
        for(i = 0; i < 100; i = i + 1) begin : BCD

            if(i == 0)
                bcd_fadd fa(
                    a[4*i +: 4],
                    b[4*i +: 4],
                    cin,
                    c[i],
                    sum[4*i +: 4]
                );
            else
                bcd_fadd fa(
                    a[4*i +: 4],
                    b[4*i +: 4],
                    c[i-1],
                    c[i],
                    sum[4*i +: 4]
                );

        end
    endgenerate

    assign cout = c[99];

endmodule