module LEDproject(
	input button,
	input clk,
	output reg LED
);
		
	/* DEBOUNCING BUTTON */
	
	reg[31:0] button_counter;
	reg button_signal;
	
	always @(posedge clk) begin
		button_signal <= button;
//		if (button == 0) begin
//			button_counter <= 0;
//		else
//			button_counter <= (button_counter >= 1500) ? 0 : button_counter+1;
//		end
	end

	/* STATE MACHINE TRANSITIONS */
	
	reg[2:0] current_state;
	
	always @(negedge button_signal) begin
		current_state <= (current_state == 4) ? 0 : current_state + 1;
	end
	
	/* OUTPUT CONTROL */
	
	wire off = 1'b0;
	wire full_bright = 1'b1; 
	reg half_bright, flashing, low_bright;
	
	reg[31:0] flashing_counter;
	reg low_counter;
	
	always @(posedge clk) begin
	
		half_bright <= ~half_bright;
		
		low_counter <= low_counter + 1;
		low_bright <= (low_counter == 1) ? low_bright : ~low_bright;

		flashing_counter <= (flashing_counter == 12500000) ? 0 : flashing_counter + 1;
		flashing <= (flashing_counter == 12500000) ? flashing : ~flashing;
		
		case (current_state)
			3'b000 : LED = off;
			3'b001 : LED = full_bright;
			3'b010 : LED = half_bright;
			3'b011 : LED = low_bright;
			3'b100 : LED = flashing;
			default : LED = off;
		endcase
		
	end

endmodule
