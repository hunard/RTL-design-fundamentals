module top_module
(input clk,reset.input[7:0]d,ouput [7:0]q);
always @(posedge clk) begin
    if (reset)
        q <= 8'h34;
    else
        q <= d;
end
endmodule