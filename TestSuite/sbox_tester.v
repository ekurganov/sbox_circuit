`include "header.v"
`include "sbox.v"
`include "decoders.v"
`include "phi.v"
`include "all_functions.v"

module sbox_tester ();
    reg clk;
    reg [`width - 1:0] input_data [0:2**`width - 1];
    reg [`width - 1:0] output_data [0:2**`width - 1];
    reg [`width - 1:0] a;
    wire [`width - 1:0] res;
    integer i;

    initial begin
        // initialize clock
        clk = 1'b0;
        // read input data from a file
        $readmemh ("inputs.txt", input_data);
        // read output data from a file
        $readmemh ("outputs.txt", output_data);
        // initalize the counter
        i = 0;
    end

    always begin
        #10 clk = ~clk; // next clock phase
    end

    sbox9 module_inst (.a (a), .z (res));

    always @(negedge clk) begin
        a = input_data [i];
        i = i + 1;
    end

    always @(posedge clk) begin
        if (res != output_data [i - 1]) begin
            $display ("Error: inputs %b", a); 
            $display ("Module output %b, expected output %b", res,
                                                    output_data [i - 1]);
        end
        if (i == (2**`width)) begin
            $display ("No more tests left");
            $finish;
        end
    end

endmodule
