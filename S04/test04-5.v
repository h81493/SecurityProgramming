module top();
reg [7:0] cnt;
wire Fizz;
wire Buzz;
wire FizzBuzz;

initial begin
  cnt <= 1;
  #10;
  while( cnt <= 100) begin
    cnt <= cnt+1;
    #10;
  end
end

assign FizzBuzz=(cnt % 3 == 0) && (cnt % 5 == 0);
assign Fizz=(cnt % 3 == 0) && !FizzBuzz;
assign Buzz=(cnt % 5 == 0) && !FizzBuzz & !Fizz;
endmodule
