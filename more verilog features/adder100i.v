module top_module( 
    input [99:0] a, b,
    input cin,
    output [99:0] cout,
    output [99:0] sum );
    genvar i;
    generate
        for(i=0;i<100;i=i+1)begin:FA
            if(i==0)
                add1 fa(a[i],b[i],cin,sum[i],cout[i]);
            else
                add1 fa(a[i],b[i],cout[i-1],sum[i],cout[i]);
        end
    endgenerate

endmodule
module add1(
    input a,b,cin,output sum,cout);
    assign sum=a^b^cin;
    assign cout=(a&b)|(a&cin)|(b&cin);
endmodule
