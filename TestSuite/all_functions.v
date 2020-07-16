module all_functions_2(a, z);
  input [1:0] a;
  output [3:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];

  assign z[3] = z[1] | z[2];

endmodule

module all_functions_3(a, z);
  input [2:0] a;
  output [7:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];

  assign z[7] = z[1] | z[6];

endmodule

module all_functions_4(a, z);
  input [3:0] a;
  output [15:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];
  assign z[8] = a[3];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];
  assign z[9] = z[1] | z[8];
  assign z[10] = z[2] | z[8];
  assign z[12] = z[4] | z[8];

  assign z[7] = z[1] | z[6];
  assign z[11] = z[1] | z[10];
  assign z[13] = z[1] | z[12];
  assign z[14] = z[2] | z[12];

  assign z[15] = z[3] | z[12];

endmodule

module all_functions_5(a, z);
  input [4:0] a;
  output [31:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];
  assign z[8] = a[3];
  assign z[16] = a[4];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];
  assign z[9] = z[1] | z[8];
  assign z[10] = z[2] | z[8];
  assign z[12] = z[4] | z[8];
  assign z[17] = z[1] | z[16];
  assign z[18] = z[2] | z[16];
  assign z[20] = z[4] | z[16];
  assign z[24] = z[8] | z[16];

  assign z[7] = z[1] | z[6];
  assign z[11] = z[1] | z[10];
  assign z[13] = z[1] | z[12];
  assign z[14] = z[2] | z[12];
  assign z[19] = z[1] | z[18];
  assign z[21] = z[1] | z[20];
  assign z[22] = z[2] | z[20];
  assign z[25] = z[1] | z[24];
  assign z[26] = z[2] | z[24];
  assign z[28] = z[4] | z[24];

  assign z[15] = z[3] | z[12];
  assign z[23] = z[3] | z[20];
  assign z[27] = z[3] | z[24];
  assign z[29] = z[5] | z[24];
  assign z[30] = z[6] | z[24];

  assign z[31] = z[3] | z[28];

endmodule

module all_functions_6(a, z);
  input [5:0] a;
  output [63:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];
  assign z[8] = a[3];
  assign z[16] = a[4];
  assign z[32] = a[5];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];
  assign z[9] = z[1] | z[8];
  assign z[10] = z[2] | z[8];
  assign z[12] = z[4] | z[8];
  assign z[17] = z[1] | z[16];
  assign z[18] = z[2] | z[16];
  assign z[20] = z[4] | z[16];
  assign z[24] = z[8] | z[16];
  assign z[33] = z[1] | z[32];
  assign z[34] = z[2] | z[32];
  assign z[36] = z[4] | z[32];
  assign z[40] = z[8] | z[32];
  assign z[48] = z[16] | z[32];

  assign z[7] = z[1] | z[6];
  assign z[11] = z[1] | z[10];
  assign z[13] = z[1] | z[12];
  assign z[14] = z[2] | z[12];
  assign z[19] = z[1] | z[18];
  assign z[21] = z[1] | z[20];
  assign z[22] = z[2] | z[20];
  assign z[25] = z[1] | z[24];
  assign z[26] = z[2] | z[24];
  assign z[28] = z[4] | z[24];
  assign z[35] = z[1] | z[34];
  assign z[37] = z[1] | z[36];
  assign z[38] = z[2] | z[36];
  assign z[41] = z[1] | z[40];
  assign z[42] = z[2] | z[40];
  assign z[44] = z[4] | z[40];
  assign z[49] = z[1] | z[48];
  assign z[50] = z[2] | z[48];
  assign z[52] = z[4] | z[48];
  assign z[56] = z[8] | z[48];

  assign z[15] = z[3] | z[12];
  assign z[23] = z[3] | z[20];
  assign z[27] = z[3] | z[24];
  assign z[29] = z[5] | z[24];
  assign z[30] = z[6] | z[24];
  assign z[39] = z[3] | z[36];
  assign z[43] = z[3] | z[40];
  assign z[45] = z[5] | z[40];
  assign z[46] = z[6] | z[40];
  assign z[51] = z[3] | z[48];
  assign z[53] = z[5] | z[48];
  assign z[54] = z[6] | z[48];
  assign z[57] = z[9] | z[48];
  assign z[58] = z[10] | z[48];
  assign z[60] = z[12] | z[48];

  assign z[31] = z[3] | z[28];
  assign z[47] = z[3] | z[44];
  assign z[55] = z[3] | z[52];
  assign z[59] = z[3] | z[56];
  assign z[61] = z[5] | z[56];
  assign z[62] = z[6] | z[56];

  assign z[63] = z[7] | z[56];

endmodule

module all_functions_7(a, z);
  input [6:0] a;
  output [127:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];
  assign z[8] = a[3];
  assign z[16] = a[4];
  assign z[32] = a[5];
  assign z[64] = a[6];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];
  assign z[9] = z[1] | z[8];
  assign z[10] = z[2] | z[8];
  assign z[12] = z[4] | z[8];
  assign z[17] = z[1] | z[16];
  assign z[18] = z[2] | z[16];
  assign z[20] = z[4] | z[16];
  assign z[24] = z[8] | z[16];
  assign z[33] = z[1] | z[32];
  assign z[34] = z[2] | z[32];
  assign z[36] = z[4] | z[32];
  assign z[40] = z[8] | z[32];
  assign z[48] = z[16] | z[32];
  assign z[65] = z[1] | z[64];
  assign z[66] = z[2] | z[64];
  assign z[68] = z[4] | z[64];
  assign z[72] = z[8] | z[64];
  assign z[80] = z[16] | z[64];
  assign z[96] = z[32] | z[64];

  assign z[7] = z[1] | z[6];
  assign z[11] = z[1] | z[10];
  assign z[13] = z[1] | z[12];
  assign z[14] = z[2] | z[12];
  assign z[19] = z[1] | z[18];
  assign z[21] = z[1] | z[20];
  assign z[22] = z[2] | z[20];
  assign z[25] = z[1] | z[24];
  assign z[26] = z[2] | z[24];
  assign z[28] = z[4] | z[24];
  assign z[35] = z[1] | z[34];
  assign z[37] = z[1] | z[36];
  assign z[38] = z[2] | z[36];
  assign z[41] = z[1] | z[40];
  assign z[42] = z[2] | z[40];
  assign z[44] = z[4] | z[40];
  assign z[49] = z[1] | z[48];
  assign z[50] = z[2] | z[48];
  assign z[52] = z[4] | z[48];
  assign z[56] = z[8] | z[48];
  assign z[67] = z[1] | z[66];
  assign z[69] = z[1] | z[68];
  assign z[70] = z[2] | z[68];
  assign z[73] = z[1] | z[72];
  assign z[74] = z[2] | z[72];
  assign z[76] = z[4] | z[72];
  assign z[81] = z[1] | z[80];
  assign z[82] = z[2] | z[80];
  assign z[84] = z[4] | z[80];
  assign z[88] = z[8] | z[80];
  assign z[97] = z[1] | z[96];
  assign z[98] = z[2] | z[96];
  assign z[100] = z[4] | z[96];
  assign z[104] = z[8] | z[96];
  assign z[112] = z[16] | z[96];

  assign z[15] = z[3] | z[12];
  assign z[23] = z[3] | z[20];
  assign z[27] = z[3] | z[24];
  assign z[29] = z[5] | z[24];
  assign z[30] = z[6] | z[24];
  assign z[39] = z[3] | z[36];
  assign z[43] = z[3] | z[40];
  assign z[45] = z[5] | z[40];
  assign z[46] = z[6] | z[40];
  assign z[51] = z[3] | z[48];
  assign z[53] = z[5] | z[48];
  assign z[54] = z[6] | z[48];
  assign z[57] = z[9] | z[48];
  assign z[58] = z[10] | z[48];
  assign z[60] = z[12] | z[48];
  assign z[71] = z[3] | z[68];
  assign z[75] = z[3] | z[72];
  assign z[77] = z[5] | z[72];
  assign z[78] = z[6] | z[72];
  assign z[83] = z[3] | z[80];
  assign z[85] = z[5] | z[80];
  assign z[86] = z[6] | z[80];
  assign z[89] = z[9] | z[80];
  assign z[90] = z[10] | z[80];
  assign z[92] = z[12] | z[80];
  assign z[99] = z[3] | z[96];
  assign z[101] = z[5] | z[96];
  assign z[102] = z[6] | z[96];
  assign z[105] = z[9] | z[96];
  assign z[106] = z[10] | z[96];
  assign z[108] = z[12] | z[96];
  assign z[113] = z[17] | z[96];
  assign z[114] = z[18] | z[96];
  assign z[116] = z[20] | z[96];
  assign z[120] = z[24] | z[96];

  assign z[31] = z[3] | z[28];
  assign z[47] = z[3] | z[44];
  assign z[55] = z[3] | z[52];
  assign z[59] = z[3] | z[56];
  assign z[61] = z[5] | z[56];
  assign z[62] = z[6] | z[56];
  assign z[79] = z[3] | z[76];
  assign z[87] = z[3] | z[84];
  assign z[91] = z[3] | z[88];
  assign z[93] = z[5] | z[88];
  assign z[94] = z[6] | z[88];
  assign z[103] = z[3] | z[100];
  assign z[107] = z[3] | z[104];
  assign z[109] = z[5] | z[104];
  assign z[110] = z[6] | z[104];
  assign z[115] = z[3] | z[112];
  assign z[117] = z[5] | z[112];
  assign z[118] = z[6] | z[112];
  assign z[121] = z[9] | z[112];
  assign z[122] = z[10] | z[112];
  assign z[124] = z[12] | z[112];

  assign z[63] = z[7] | z[56];
  assign z[95] = z[7] | z[88];
  assign z[111] = z[7] | z[104];
  assign z[119] = z[7] | z[112];
  assign z[123] = z[11] | z[112];
  assign z[125] = z[13] | z[112];
  assign z[126] = z[14] | z[112];

  assign z[127] = z[7] | z[120];

endmodule

module all_functions_8(a, z);
  input [7:0] a;
  output [255:0] z;

  assign z[0] = 1'b0;

  assign z[1] = a[0];
  assign z[2] = a[1];
  assign z[4] = a[2];
  assign z[8] = a[3];
  assign z[16] = a[4];
  assign z[32] = a[5];
  assign z[64] = a[6];
  assign z[128] = a[7];

  assign z[3] = z[1] | z[2];
  assign z[5] = z[1] | z[4];
  assign z[6] = z[2] | z[4];
  assign z[9] = z[1] | z[8];
  assign z[10] = z[2] | z[8];
  assign z[12] = z[4] | z[8];
  assign z[17] = z[1] | z[16];
  assign z[18] = z[2] | z[16];
  assign z[20] = z[4] | z[16];
  assign z[24] = z[8] | z[16];
  assign z[33] = z[1] | z[32];
  assign z[34] = z[2] | z[32];
  assign z[36] = z[4] | z[32];
  assign z[40] = z[8] | z[32];
  assign z[48] = z[16] | z[32];
  assign z[65] = z[1] | z[64];
  assign z[66] = z[2] | z[64];
  assign z[68] = z[4] | z[64];
  assign z[72] = z[8] | z[64];
  assign z[80] = z[16] | z[64];
  assign z[96] = z[32] | z[64];
  assign z[129] = z[1] | z[128];
  assign z[130] = z[2] | z[128];
  assign z[132] = z[4] | z[128];
  assign z[136] = z[8] | z[128];
  assign z[144] = z[16] | z[128];
  assign z[160] = z[32] | z[128];
  assign z[192] = z[64] | z[128];

  assign z[7] = z[1] | z[6];
  assign z[11] = z[1] | z[10];
  assign z[13] = z[1] | z[12];
  assign z[14] = z[2] | z[12];
  assign z[19] = z[1] | z[18];
  assign z[21] = z[1] | z[20];
  assign z[22] = z[2] | z[20];
  assign z[25] = z[1] | z[24];
  assign z[26] = z[2] | z[24];
  assign z[28] = z[4] | z[24];
  assign z[35] = z[1] | z[34];
  assign z[37] = z[1] | z[36];
  assign z[38] = z[2] | z[36];
  assign z[41] = z[1] | z[40];
  assign z[42] = z[2] | z[40];
  assign z[44] = z[4] | z[40];
  assign z[49] = z[1] | z[48];
  assign z[50] = z[2] | z[48];
  assign z[52] = z[4] | z[48];
  assign z[56] = z[8] | z[48];
  assign z[67] = z[1] | z[66];
  assign z[69] = z[1] | z[68];
  assign z[70] = z[2] | z[68];
  assign z[73] = z[1] | z[72];
  assign z[74] = z[2] | z[72];
  assign z[76] = z[4] | z[72];
  assign z[81] = z[1] | z[80];
  assign z[82] = z[2] | z[80];
  assign z[84] = z[4] | z[80];
  assign z[88] = z[8] | z[80];
  assign z[97] = z[1] | z[96];
  assign z[98] = z[2] | z[96];
  assign z[100] = z[4] | z[96];
  assign z[104] = z[8] | z[96];
  assign z[112] = z[16] | z[96];
  assign z[131] = z[1] | z[130];
  assign z[133] = z[1] | z[132];
  assign z[134] = z[2] | z[132];
  assign z[137] = z[1] | z[136];
  assign z[138] = z[2] | z[136];
  assign z[140] = z[4] | z[136];
  assign z[145] = z[1] | z[144];
  assign z[146] = z[2] | z[144];
  assign z[148] = z[4] | z[144];
  assign z[152] = z[8] | z[144];
  assign z[161] = z[1] | z[160];
  assign z[162] = z[2] | z[160];
  assign z[164] = z[4] | z[160];
  assign z[168] = z[8] | z[160];
  assign z[176] = z[16] | z[160];
  assign z[193] = z[1] | z[192];
  assign z[194] = z[2] | z[192];
  assign z[196] = z[4] | z[192];
  assign z[200] = z[8] | z[192];
  assign z[208] = z[16] | z[192];
  assign z[224] = z[32] | z[192];

  assign z[15] = z[3] | z[12];
  assign z[23] = z[3] | z[20];
  assign z[27] = z[3] | z[24];
  assign z[29] = z[5] | z[24];
  assign z[30] = z[6] | z[24];
  assign z[39] = z[3] | z[36];
  assign z[43] = z[3] | z[40];
  assign z[45] = z[5] | z[40];
  assign z[46] = z[6] | z[40];
  assign z[51] = z[3] | z[48];
  assign z[53] = z[5] | z[48];
  assign z[54] = z[6] | z[48];
  assign z[57] = z[9] | z[48];
  assign z[58] = z[10] | z[48];
  assign z[60] = z[12] | z[48];
  assign z[71] = z[3] | z[68];
  assign z[75] = z[3] | z[72];
  assign z[77] = z[5] | z[72];
  assign z[78] = z[6] | z[72];
  assign z[83] = z[3] | z[80];
  assign z[85] = z[5] | z[80];
  assign z[86] = z[6] | z[80];
  assign z[89] = z[9] | z[80];
  assign z[90] = z[10] | z[80];
  assign z[92] = z[12] | z[80];
  assign z[99] = z[3] | z[96];
  assign z[101] = z[5] | z[96];
  assign z[102] = z[6] | z[96];
  assign z[105] = z[9] | z[96];
  assign z[106] = z[10] | z[96];
  assign z[108] = z[12] | z[96];
  assign z[113] = z[17] | z[96];
  assign z[114] = z[18] | z[96];
  assign z[116] = z[20] | z[96];
  assign z[120] = z[24] | z[96];
  assign z[135] = z[3] | z[132];
  assign z[139] = z[3] | z[136];
  assign z[141] = z[5] | z[136];
  assign z[142] = z[6] | z[136];
  assign z[147] = z[3] | z[144];
  assign z[149] = z[5] | z[144];
  assign z[150] = z[6] | z[144];
  assign z[153] = z[9] | z[144];
  assign z[154] = z[10] | z[144];
  assign z[156] = z[12] | z[144];
  assign z[163] = z[3] | z[160];
  assign z[165] = z[5] | z[160];
  assign z[166] = z[6] | z[160];
  assign z[169] = z[9] | z[160];
  assign z[170] = z[10] | z[160];
  assign z[172] = z[12] | z[160];
  assign z[177] = z[17] | z[160];
  assign z[178] = z[18] | z[160];
  assign z[180] = z[20] | z[160];
  assign z[184] = z[24] | z[160];
  assign z[195] = z[3] | z[192];
  assign z[197] = z[5] | z[192];
  assign z[198] = z[6] | z[192];
  assign z[201] = z[9] | z[192];
  assign z[202] = z[10] | z[192];
  assign z[204] = z[12] | z[192];
  assign z[209] = z[17] | z[192];
  assign z[210] = z[18] | z[192];
  assign z[212] = z[20] | z[192];
  assign z[216] = z[24] | z[192];
  assign z[225] = z[33] | z[192];
  assign z[226] = z[34] | z[192];
  assign z[228] = z[36] | z[192];
  assign z[232] = z[40] | z[192];
  assign z[240] = z[48] | z[192];

  assign z[31] = z[3] | z[28];
  assign z[47] = z[3] | z[44];
  assign z[55] = z[3] | z[52];
  assign z[59] = z[3] | z[56];
  assign z[61] = z[5] | z[56];
  assign z[62] = z[6] | z[56];
  assign z[79] = z[3] | z[76];
  assign z[87] = z[3] | z[84];
  assign z[91] = z[3] | z[88];
  assign z[93] = z[5] | z[88];
  assign z[94] = z[6] | z[88];
  assign z[103] = z[3] | z[100];
  assign z[107] = z[3] | z[104];
  assign z[109] = z[5] | z[104];
  assign z[110] = z[6] | z[104];
  assign z[115] = z[3] | z[112];
  assign z[117] = z[5] | z[112];
  assign z[118] = z[6] | z[112];
  assign z[121] = z[9] | z[112];
  assign z[122] = z[10] | z[112];
  assign z[124] = z[12] | z[112];
  assign z[143] = z[3] | z[140];
  assign z[151] = z[3] | z[148];
  assign z[155] = z[3] | z[152];
  assign z[157] = z[5] | z[152];
  assign z[158] = z[6] | z[152];
  assign z[167] = z[3] | z[164];
  assign z[171] = z[3] | z[168];
  assign z[173] = z[5] | z[168];
  assign z[174] = z[6] | z[168];
  assign z[179] = z[3] | z[176];
  assign z[181] = z[5] | z[176];
  assign z[182] = z[6] | z[176];
  assign z[185] = z[9] | z[176];
  assign z[186] = z[10] | z[176];
  assign z[188] = z[12] | z[176];
  assign z[199] = z[3] | z[196];
  assign z[203] = z[3] | z[200];
  assign z[205] = z[5] | z[200];
  assign z[206] = z[6] | z[200];
  assign z[211] = z[3] | z[208];
  assign z[213] = z[5] | z[208];
  assign z[214] = z[6] | z[208];
  assign z[217] = z[9] | z[208];
  assign z[218] = z[10] | z[208];
  assign z[220] = z[12] | z[208];
  assign z[227] = z[3] | z[224];
  assign z[229] = z[5] | z[224];
  assign z[230] = z[6] | z[224];
  assign z[233] = z[9] | z[224];
  assign z[234] = z[10] | z[224];
  assign z[236] = z[12] | z[224];
  assign z[241] = z[17] | z[224];
  assign z[242] = z[18] | z[224];
  assign z[244] = z[20] | z[224];
  assign z[248] = z[24] | z[224];

  assign z[63] = z[7] | z[56];
  assign z[95] = z[7] | z[88];
  assign z[111] = z[7] | z[104];
  assign z[119] = z[7] | z[112];
  assign z[123] = z[11] | z[112];
  assign z[125] = z[13] | z[112];
  assign z[126] = z[14] | z[112];
  assign z[159] = z[7] | z[152];
  assign z[175] = z[7] | z[168];
  assign z[183] = z[7] | z[176];
  assign z[187] = z[11] | z[176];
  assign z[189] = z[13] | z[176];
  assign z[190] = z[14] | z[176];
  assign z[207] = z[7] | z[200];
  assign z[215] = z[7] | z[208];
  assign z[219] = z[11] | z[208];
  assign z[221] = z[13] | z[208];
  assign z[222] = z[14] | z[208];
  assign z[231] = z[7] | z[224];
  assign z[235] = z[11] | z[224];
  assign z[237] = z[13] | z[224];
  assign z[238] = z[14] | z[224];
  assign z[243] = z[19] | z[224];
  assign z[245] = z[21] | z[224];
  assign z[246] = z[22] | z[224];
  assign z[249] = z[25] | z[224];
  assign z[250] = z[26] | z[224];
  assign z[252] = z[28] | z[224];

  assign z[127] = z[7] | z[120];
  assign z[191] = z[7] | z[184];
  assign z[223] = z[7] | z[216];
  assign z[239] = z[7] | z[232];
  assign z[247] = z[7] | z[240];
  assign z[251] = z[11] | z[240];
  assign z[253] = z[13] | z[240];
  assign z[254] = z[14] | z[240];

  assign z[255] = z[15] | z[240];

endmodule

