`ifndef __DECODERS_V_
`define __DECODERS_V_

module decoder2_4(a, z);
	input [1:0] a;
	output [3:0] z;
	
	assign z[3] = a[1] & a[0];
	assign z[2] = a[1] & !a[0];
	assign z[1] = !a[1] & a[0];
	assign z[0] = !a[1] & !a[0];
endmodule

module decoder3_8(a, z);
	input [2:0] a;
	output [7:0] z;
	wire [3:0] x;
	wire [1:0] y;
	genvar i, j;
	
	assign y = {a[2], !a[2]};
	decoder2_4 d_inst(.a(a[1:0]), .z(x));
	
	for (i = 0; i < 2; i = i + 1) begin
      for (j = 0; j < 4; j = j + 1) begin
		assign z[i * 4 + j] = x[j] & y[i];
	  end
    end
endmodule

module decoder4_16(a, z);
	input [3:0] a;
	output [15:0] z;
	wire [3:0] x;
	wire [3:0] y;
	genvar i, j;
	
	decoder2_4 d_inst1(.a(a[1:0]), .z(x));
	decoder2_4 d_inst2(.a(a[3:2]), .z(y));
	
	for (i = 0; i < 4; i = i + 1) begin
      for (j = 0; j < 4; j = j + 1) begin
		assign z[i * 4 + j] = x[j] & y[i];
	  end
    end	
endmodule

module decoder5_32(a, z);
  input [4:0] a;
  output [31:0] z;
  wire [7:0] x;
  wire [3:0] y;
  genvar i, j;

  decoder3_8 d_inst1(.a(a[2:0]), .z(x));
  decoder2_4 d_inst2(.a(a[4:3]), .z(y));

  for(i = 0; i < 4; i = i + 1) begin
    for(j = 0; j < 8; j = j + 1) begin
      assign z[i * 8 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder6_64(a, z);
  input [5:0] a;
  output [63:0] z;
  wire [7:0] x;
  wire [7:0] y;
  genvar i, j;

  decoder3_8 d_inst1(.a(a[2:0]), .z(x));
  decoder3_8 d_inst2(.a(a[5:3]), .z(y));

  for(i = 0; i < 8; i = i + 1) begin
    for(j = 0; j < 8; j = j + 1) begin
      assign z[i * 8 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder7_128(a, z);
  input [6:0] a;
  output [127:0] z;
  wire [15:0] x;
  wire [7:0] y;
  genvar i, j;

  decoder4_16 d_inst1(.a(a[3:0]), .z(x));
  decoder3_8 d_inst2(.a(a[6:4]), .z(y));

  for(i = 0; i < 8; i = i + 1) begin
    for(j = 0; j < 16; j = j + 1) begin
      assign z[i * 16 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder8_256(a, z);
  input [7:0] a;
  output [255:0] z;
  wire [15:0] x;
  wire [15:0] y;
  genvar i, j;

  decoder4_16 d_inst1(.a(a[3:0]), .z(x));
  decoder4_16 d_inst2(.a(a[7:4]), .z(y));

  for(i = 0; i < 16; i = i + 1) begin
    for(j = 0; j < 16; j = j + 1) begin
      assign z[i * 16 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder9_512(a, z);
  input [8:0] a;
  output [511:0] z;
  wire [31:0] x;
  wire [15:0] y;
  genvar i, j;

  decoder5_32 d_inst1(.a(a[4:0]), .z(x));
  decoder4_16 d_inst2(.a(a[8:5]), .z(y));

  for(i = 0; i < 16; i = i + 1) begin
    for(j = 0; j < 32; j = j + 1) begin
      assign z[i * 32 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder10_1024(a, z);
  input [9:0] a;
  output [1023:0] z;
  wire [31:0] x;
  wire [31:0] y;
  genvar i, j;

  decoder5_32 d_inst1(.a(a[4:0]), .z(x));
  decoder5_32 d_inst2(.a(a[9:5]), .z(y));

  for(i = 0; i < 32; i = i + 1) begin
    for(j = 0; j < 32; j = j + 1) begin
      assign z[i * 32 + j] = x[j] & y[i];
    end
  end
endmodule

module decoder11_2048(a, z);
  input [10:0] a;
  output [2047:0] z;
  wire [63:0] x;
  wire [31:0] y;
  genvar i, j;

  decoder6_64 d_inst1(.a(a[5:0]), .z(x));
  decoder5_32 d_inst2(.a(a[10:6]), .z(y));

  for(i = 0; i < 32; i = i + 1) begin
    for(j = 0; j < 64; j = j + 1) begin
      assign z[i * 64 + j] = x[j] & y[i];
    end
  end
endmodule

`endif 
