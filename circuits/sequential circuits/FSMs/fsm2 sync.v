module top_module(
    input clk,
    input areset,
    input j,
    input k,
    output out
);

parameter OFF = 1'b0,
          ON  = 1'b1;

reg state, next_state;

// State register
always @(posedge clk or posedge areset) begin
    if (areset)
        state <= OFF;
    else
        state <= next_state;
end

// Next-state logic
always @(*) begin
    case (state)
        OFF: next_state = (j) ? ON : OFF;
        ON : next_state = (k) ? OFF : ON;
    endcase
end

// Output logic
assign out = (state == ON);

endmodule
