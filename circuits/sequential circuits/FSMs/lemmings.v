module top_module(
    input clk,
    input areset,
    input bump_left,
    input bump_right,
    output walk_left,
    output walk_right
);

parameter LEFT = 1'b0, RIGHT = 1'b1;

reg state, next_state;

// State register
always @(posedge clk or posedge areset) begin
    if (areset)
        state <= LEFT;
    else
        state <= next_state;
end

// Next-state logic
always @(*) begin
  case (state)
        LEFT:
            if (bump_left)
                next_state = RIGHT;
            else
                next_state = LEFT;

        RIGHT:
            if (bump_right)
                next_state = LEFT;
            else
                next_state = RIGHT;
    endcase
end

// Output logic (Moore FSM)
assign walk_left  = (state == LEFT);
assign walk_right = (state == RIGHT);

endmodule
