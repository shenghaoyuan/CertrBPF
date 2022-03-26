struct verifier_state;
struct verifier_state {
  unsigned int ins_len;
  unsigned long long *ins$756645;
};

extern _Bool is_well_dst(unsigned long long);

extern _Bool is_well_src(unsigned long long);

extern _Bool is_well_jump(unsigned int, unsigned int, int);

extern _Bool is_not_div_by_zero(unsigned long long);

extern _Bool is_shift_range(unsigned long long, unsigned int);

extern unsigned int get_opcode(unsigned long long);

extern int get_offset(unsigned long long);

extern unsigned char nat2opcode(unsigned int);

extern _Bool bpf_verifier_aux(unsigned int);

extern _Bool bpf_verifier(void);

extern unsigned int eval_ins_len(void);

extern unsigned long long eval_ins(unsigned int);

_Bool is_well_dst(unsigned long long i)
{
  return (unsigned int) ((i & 4095LLU) >> 8LLU) <= 10U;
}

_Bool is_well_src(unsigned long long i$28)
{
  return (unsigned int) ((i$28 & 65535LLU) >> 12LLU) <= 10U;
}

_Bool is_well_jump(unsigned int pc, unsigned int len, int ofs)
{
  return pc + ofs <= len - 2U;
}

_Bool is_not_div_by_zero(unsigned long long i$36)
{
  return (int) (i$36 >> 32LLU) != 0U;
}

_Bool is_shift_range(unsigned long long i$38, unsigned int upper)
{
  return 0U <= (int) (i$38 >> 32LLU) & (int) (i$38 >> 32LLU) <= upper;
}

unsigned int get_opcode(unsigned long long ins)
{
  return (unsigned char) (ins & 255LLU);
}

int get_offset(unsigned long long i$44)
{
  return (int) (short) (i$44 << 32LLU >> 48LLU);
}

unsigned char nat2opcode(unsigned int n)
{
  return n;
}

_Bool bpf_verifier_aux(unsigned int pc$48)
{
  unsigned int len$50;
  unsigned long long ins64;
  unsigned int op;
  unsigned int n$56;
  unsigned char opc;
  _Bool b;
  _Bool b$62;
  _Bool b$64;
  _Bool b$66;
  _Bool b$68;
  _Bool b$70;
  _Bool b$72;
  _Bool b$74;
  _Bool b$76;
  _Bool b$78;
  _Bool b$80;
  _Bool b$82;
  _Bool b$84;
  _Bool b$86;
  _Bool b0;
  _Bool b$90;
  _Bool b0$92;
  _Bool b$94;
  _Bool b0$96;
  _Bool b$98;
  _Bool b0$100;
  _Bool b$102;
  _Bool b0$104;
  _Bool b$106;
  _Bool b0$108;
  _Bool b$110;
  _Bool b0$112;
  _Bool b$114;
  _Bool b0$116;
  _Bool b$118;
  _Bool b0$120;
  _Bool b$122;
  _Bool b0$124;
  _Bool b$126;
  _Bool b0$128;
  _Bool b$130;
  _Bool b0$132;
  _Bool b$134;
  _Bool b$136;
  _Bool b$138;
  _Bool b$140;
  _Bool b$142;
  _Bool b$144;
  _Bool b$146;
  _Bool b$148;
  _Bool b$150;
  _Bool b$152;
  _Bool b$154;
  _Bool b$156;
  _Bool b$158;
  _Bool b$160;
  _Bool b0$162;
  _Bool b$164;
  _Bool b0$166;
  _Bool b$168;
  _Bool b0$170;
  _Bool b$172;
  _Bool b0$174;
  _Bool b$176;
  _Bool b0$178;
  _Bool b$180;
  _Bool b0$182;
  _Bool b$184;
  _Bool b0$186;
  _Bool b$188;
  _Bool b0$190;
  _Bool b$192;
  _Bool b0$194;
  _Bool b$196;
  _Bool b0$198;
  _Bool b$200;
  _Bool b0$202;
  _Bool b$204;
  _Bool b0$206;
  _Bool b$208;
  _Bool b$210;
  _Bool b0$212;
  _Bool b$214;
  _Bool b0$216;
  _Bool b$218;
  _Bool b0$220;
  _Bool b$222;
  _Bool b0$224;
  _Bool b$226;
  _Bool b$228;
  _Bool b$230;
  _Bool b$232;
  _Bool b$234;
  _Bool b0$236;
  _Bool b$238;
  _Bool b0$240;
  _Bool b$242;
  _Bool b0$244;
  _Bool b$246;
  _Bool b0$248;
  int ofs$250;
  _Bool b$252;
  int ofs$254;
  _Bool b$256;
  int ofs$258;
  _Bool b$260;
  int ofs$262;
  _Bool b$264;
  int ofs$266;
  _Bool b$268;
  int ofs$270;
  _Bool b$272;
  int ofs$274;
  _Bool b$276;
  int ofs$278;
  _Bool b$280;
  int ofs$282;
  _Bool b$284;
  int ofs$286;
  _Bool b$288;
  int ofs$290;
  _Bool b$292;
  int ofs$294;
  _Bool b$296;
  int ofs$298;
  _Bool b$300;
  int ofs$302;
  _Bool b$304;
  int ofs$306;
  _Bool b$308;
  int ofs$310;
  _Bool b$312;
  int ofs$314;
  _Bool b$316;
  int ofs$318;
  _Bool b$320;
  int ofs$322;
  _Bool b$324;
  int ofs$326;
  _Bool b$328;
  int ofs$330;
  _Bool b$332;
  int ofs$334;
  _Bool b$336;
  int ofs$338;
  _Bool b$340;
  len$50 = eval_ins_len();
  ins64 = eval_ins(pc$48 - 1U - len$50);
  op = get_opcode(ins64);
  if (pc$48 == 0U) {
    return op == 149;
  } else {
    n$56 = pc$48 - 1U;
    opc = nat2opcode(op);
    switch (opc) {
      case 7:
        b = is_well_dst(ins64);
        if (b) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 23:
        b$62 = is_well_dst(ins64);
        if (b$62) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 39:
        b$64 = is_well_dst(ins64);
        if (b$64) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 55:
        b$66 = is_not_div_by_zero(ins64);
        if (b$66) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 71:
        b$68 = is_well_dst(ins64);
        if (b$68) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 87:
        b$70 = is_well_dst(ins64);
        if (b$70) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 103:
        b$72 = is_shift_range(ins64, 64U);
        if (b$72) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 119:
        b$74 = is_shift_range(ins64, 64U);
        if (b$74) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 135:
        b$76 = is_well_dst(ins64);
        if (b$76) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 151:
        b$78 = is_not_div_by_zero(ins64);
        if (b$78) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 167:
        b$80 = is_well_dst(ins64);
        if (b$80) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 183:
        b$82 = is_well_dst(ins64);
        if (b$82) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 199:
        b$84 = is_shift_range(ins64, 64U);
        if (b$84) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 15:
        b$86 = is_well_dst(ins64);
        if (b$86) {
          b0 = is_well_src(ins64);
          if (b0) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 31:
        b$90 = is_well_dst(ins64);
        if (b$90) {
          b0$92 = is_well_src(ins64);
          if (b0$92) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 47:
        b$94 = is_well_dst(ins64);
        if (b$94) {
          b0$96 = is_well_src(ins64);
          if (b0$96) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 63:
        b$98 = is_well_dst(ins64);
        if (b$98) {
          b0$100 = is_well_src(ins64);
          if (b0$100) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 79:
        b$102 = is_well_dst(ins64);
        if (b$102) {
          b0$104 = is_well_src(ins64);
          if (b0$104) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 95:
        b$106 = is_well_dst(ins64);
        if (b$106) {
          b0$108 = is_well_src(ins64);
          if (b0$108) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 111:
        b$110 = is_well_dst(ins64);
        if (b$110) {
          b0$112 = is_well_src(ins64);
          if (b0$112) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 127:
        b$114 = is_well_dst(ins64);
        if (b$114) {
          b0$116 = is_well_src(ins64);
          if (b0$116) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 159:
        b$118 = is_well_dst(ins64);
        if (b$118) {
          b0$120 = is_well_src(ins64);
          if (b0$120) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 175:
        b$122 = is_well_dst(ins64);
        if (b$122) {
          b0$124 = is_well_src(ins64);
          if (b0$124) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 191:
        b$126 = is_well_dst(ins64);
        if (b$126) {
          b0$128 = is_well_src(ins64);
          if (b0$128) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 207:
        b$130 = is_well_dst(ins64);
        if (b$130) {
          b0$132 = is_well_src(ins64);
          if (b0$132) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 4:
        b$134 = is_well_dst(ins64);
        if (b$134) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 20:
        b$136 = is_well_dst(ins64);
        if (b$136) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 36:
        b$138 = is_well_dst(ins64);
        if (b$138) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 52:
        b$140 = is_not_div_by_zero(ins64);
        if (b$140) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 68:
        b$142 = is_well_dst(ins64);
        if (b$142) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 84:
        b$144 = is_well_dst(ins64);
        if (b$144) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 100:
        b$146 = is_shift_range(ins64, 32U);
        if (b$146) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 116:
        b$148 = is_shift_range(ins64, 32U);
        if (b$148) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 132:
        b$150 = is_well_dst(ins64);
        if (b$150) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 148:
        b$152 = is_not_div_by_zero(ins64);
        if (b$152) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 164:
        b$154 = is_well_dst(ins64);
        if (b$154) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 180:
        b$156 = is_well_dst(ins64);
        if (b$156) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 196:
        b$158 = is_shift_range(ins64, 32U);
        if (b$158) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 12:
        b$160 = is_well_dst(ins64);
        if (b$160) {
          b0$162 = is_well_src(ins64);
          if (b0$162) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 28:
        b$164 = is_well_dst(ins64);
        if (b$164) {
          b0$166 = is_well_src(ins64);
          if (b0$166) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 44:
        b$168 = is_well_dst(ins64);
        if (b$168) {
          b0$170 = is_well_src(ins64);
          if (b0$170) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 60:
        b$172 = is_well_dst(ins64);
        if (b$172) {
          b0$174 = is_well_src(ins64);
          if (b0$174) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 76:
        b$176 = is_well_dst(ins64);
        if (b$176) {
          b0$178 = is_well_src(ins64);
          if (b0$178) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 92:
        b$180 = is_well_dst(ins64);
        if (b$180) {
          b0$182 = is_well_src(ins64);
          if (b0$182) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 108:
        b$184 = is_well_dst(ins64);
        if (b$184) {
          b0$186 = is_well_src(ins64);
          if (b0$186) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 124:
        b$188 = is_well_dst(ins64);
        if (b$188) {
          b0$190 = is_well_src(ins64);
          if (b0$190) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 156:
        b$192 = is_well_dst(ins64);
        if (b$192) {
          b0$194 = is_well_src(ins64);
          if (b0$194) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 172:
        b$196 = is_well_dst(ins64);
        if (b$196) {
          b0$198 = is_well_src(ins64);
          if (b0$198) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 188:
        b$200 = is_well_dst(ins64);
        if (b$200) {
          b0$202 = is_well_src(ins64);
          if (b0$202) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 204:
        b$204 = is_well_dst(ins64);
        if (b$204) {
          b0$206 = is_well_src(ins64);
          if (b0$206) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 24:
        b$208 = is_well_jump(pc$48, len$50, 2);
        if (b$208) {
          return bpf_verifier_aux(n$56 - 1);
        } else {
          return 0;
        }
      case 97:
        b$210 = is_well_dst(ins64);
        if (b$210) {
          b0$212 = is_well_src(ins64);
          if (b0$212) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 105:
        b$214 = is_well_dst(ins64);
        if (b$214) {
          b0$216 = is_well_src(ins64);
          if (b0$216) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 113:
        b$218 = is_well_dst(ins64);
        if (b$218) {
          b0$220 = is_well_src(ins64);
          if (b0$220) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 121:
        b$222 = is_well_dst(ins64);
        if (b$222) {
          b0$224 = is_well_src(ins64);
          if (b0$224) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 98:
        b$226 = is_well_dst(ins64);
        if (b$226) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 106:
        b$228 = is_well_dst(ins64);
        if (b$228) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 114:
        b$230 = is_well_dst(ins64);
        if (b$230) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 122:
        b$232 = is_well_dst(ins64);
        if (b$232) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 99:
        b$234 = is_well_dst(ins64);
        if (b$234) {
          b0$236 = is_well_src(ins64);
          if (b0$236) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 107:
        b$238 = is_well_dst(ins64);
        if (b$238) {
          b0$240 = is_well_src(ins64);
          if (b0$240) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 115:
        b$242 = is_well_dst(ins64);
        if (b$242) {
          b0$244 = is_well_src(ins64);
          if (b0$244) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 123:
        b$246 = is_well_dst(ins64);
        if (b$246) {
          b0$248 = is_well_src(ins64);
          if (b0$248) {
            return bpf_verifier_aux(n$56);
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      case 5:
        ofs$250 = get_offset(ins64);
        b$252 = is_well_jump(pc$48, len$50, ofs$250);
        if (b$252) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 21:
        ofs$254 = get_offset(ins64);
        b$256 = is_well_jump(pc$48, len$50, ofs$254);
        if (b$256) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 37:
        ofs$258 = get_offset(ins64);
        b$260 = is_well_jump(pc$48, len$50, ofs$258);
        if (b$260) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 53:
        ofs$262 = get_offset(ins64);
        b$264 = is_well_jump(pc$48, len$50, ofs$262);
        if (b$264) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 165:
        ofs$266 = get_offset(ins64);
        b$268 = is_well_jump(pc$48, len$50, ofs$266);
        if (b$268) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 181:
        ofs$270 = get_offset(ins64);
        b$272 = is_well_jump(pc$48, len$50, ofs$270);
        if (b$272) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 69:
        ofs$274 = get_offset(ins64);
        b$276 = is_well_jump(pc$48, len$50, ofs$274);
        if (b$276) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 85:
        ofs$278 = get_offset(ins64);
        b$280 = is_well_jump(pc$48, len$50, ofs$278);
        if (b$280) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 101:
        ofs$282 = get_offset(ins64);
        b$284 = is_well_jump(pc$48, len$50, ofs$282);
        if (b$284) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 117:
        ofs$286 = get_offset(ins64);
        b$288 = is_well_jump(pc$48, len$50, ofs$286);
        if (b$288) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 197:
        ofs$290 = get_offset(ins64);
        b$292 = is_well_jump(pc$48, len$50, ofs$290);
        if (b$292) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 213:
        ofs$294 = get_offset(ins64);
        b$296 = is_well_jump(pc$48, len$50, ofs$294);
        if (b$296) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 29:
        ofs$298 = get_offset(ins64);
        b$300 = is_well_jump(pc$48, len$50, ofs$298);
        if (b$300) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 45:
        ofs$302 = get_offset(ins64);
        b$304 = is_well_jump(pc$48, len$50, ofs$302);
        if (b$304) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 61:
        ofs$306 = get_offset(ins64);
        b$308 = is_well_jump(pc$48, len$50, ofs$306);
        if (b$308) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 173:
        ofs$310 = get_offset(ins64);
        b$312 = is_well_jump(pc$48, len$50, ofs$310);
        if (b$312) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 189:
        ofs$314 = get_offset(ins64);
        b$316 = is_well_jump(pc$48, len$50, ofs$314);
        if (b$316) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 77:
        ofs$318 = get_offset(ins64);
        b$320 = is_well_jump(pc$48, len$50, ofs$318);
        if (b$320) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 93:
        ofs$322 = get_offset(ins64);
        b$324 = is_well_jump(pc$48, len$50, ofs$322);
        if (b$324) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 109:
        ofs$326 = get_offset(ins64);
        b$328 = is_well_jump(pc$48, len$50, ofs$326);
        if (b$328) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 125:
        ofs$330 = get_offset(ins64);
        b$332 = is_well_jump(pc$48, len$50, ofs$330);
        if (b$332) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 205:
        ofs$334 = get_offset(ins64);
        b$336 = is_well_jump(pc$48, len$50, ofs$334);
        if (b$336) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 221:
        ofs$338 = get_offset(ins64);
        b$340 = is_well_jump(pc$48, len$50, ofs$338);
        if (b$340) {
          return bpf_verifier_aux(n$56);
        } else {
          return 0;
        }
      case 133:
        return bpf_verifier_aux(n$56);
      case 149:
        return bpf_verifier_aux(n$56);
      default:
        return 0;
      
    }
  }
}

_Bool bpf_verifier(void)
{
  unsigned int len$342;
  len$342 = eval_ins_len();
  if (1U <= len$342) {
    if (len$342 <= 4294967295U / 8) {
      return bpf_verifier_aux(len$342 - 1);
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}


