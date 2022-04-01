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

extern _Bool bpf_verifier_aux2(unsigned int, unsigned int, unsigned int, unsigned long long);

extern _Bool bpf_verifier_aux(unsigned int);

extern _Bool bpf_verifier(void);

extern unsigned int eval_ins_len(void);

extern unsigned long long eval_ins(unsigned int);

_Bool is_well_dst(unsigned long long i)
{
  return (unsigned int) ((i & 4095LLU) >> 8LLU) <= 10U;
}

_Bool is_well_src(unsigned long long i$30)
{
  return (unsigned int) ((i$30 & 65535LLU) >> 12LLU) <= 10U;
}

_Bool is_well_jump(unsigned int pc, unsigned int len, int ofs)
{
  return pc + ofs <= len - 2U;
}

_Bool is_not_div_by_zero(unsigned long long i$38)
{
  return (int) (i$38 >> 32LLU) != 0U;
}

_Bool is_shift_range(unsigned long long i$40, unsigned int upper)
{
  return 0U <= (int) (i$40 >> 32LLU) & (int) (i$40 >> 32LLU) <= upper;
}

unsigned int get_opcode(unsigned long long ins)
{
  return (unsigned char) (ins & 255LLU);
}

int get_offset(unsigned long long i$46)
{
  return (int) (short) (i$46 << 32LLU >> 48LLU);
}

unsigned char nat2opcode(unsigned int n)
{
  return n;
}

_Bool bpf_verifier_aux2(unsigned int pc$50, unsigned int len$52, unsigned int op, unsigned long long ins$56)
{
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
  _Bool b$212;
  _Bool b0$214;
  _Bool b$216;
  _Bool b0$218;
  _Bool b$220;
  _Bool b0$222;
  _Bool b$224;
  _Bool b0$226;
  _Bool b$228;
  _Bool b$230;
  _Bool b$232;
  _Bool b$234;
  _Bool b$236;
  _Bool b0$238;
  _Bool b$240;
  _Bool b0$242;
  _Bool b$244;
  _Bool b0$246;
  _Bool b$248;
  _Bool b0$250;
  int ofs$252;
  _Bool b$254;
  int ofs$256;
  _Bool b$258;
  int ofs$260;
  _Bool b$262;
  int ofs$264;
  _Bool b$266;
  int ofs$268;
  _Bool b$270;
  int ofs$272;
  _Bool b$274;
  int ofs$276;
  _Bool b$278;
  int ofs$280;
  _Bool b$282;
  int ofs$284;
  _Bool b$286;
  int ofs$288;
  _Bool b$290;
  int ofs$292;
  _Bool b$294;
  int ofs$296;
  _Bool b$298;
  int ofs$300;
  _Bool b$302;
  int ofs$304;
  _Bool b$306;
  int ofs$308;
  _Bool b$310;
  int ofs$312;
  _Bool b$314;
  int ofs$316;
  _Bool b$318;
  int ofs$320;
  _Bool b$322;
  int ofs$324;
  _Bool b$326;
  int ofs$328;
  _Bool b$330;
  int ofs$332;
  _Bool b$334;
  int ofs$336;
  _Bool b$338;
  int ofs$340;
  _Bool b$342;
  opc = nat2opcode(op);
  switch (opc) {
    case 7:
      b = is_well_dst(ins$56);
      return b;
    case 23:
      b$62 = is_well_dst(ins$56);
      return b$62;
    case 39:
      b$64 = is_well_dst(ins$56);
      return b$64;
    case 55:
      b$66 = is_not_div_by_zero(ins$56);
      return b$66;
    case 71:
      b$68 = is_well_dst(ins$56);
      return b$68;
    case 87:
      b$70 = is_well_dst(ins$56);
      return b$70;
    case 103:
      b$72 = is_shift_range(ins$56, 64U);
      return b$72;
    case 119:
      b$74 = is_shift_range(ins$56, 64U);
      return b$74;
    case 135:
      b$76 = is_well_dst(ins$56);
      return b$76;
    case 151:
      b$78 = is_not_div_by_zero(ins$56);
      return b$78;
    case 167:
      b$80 = is_well_dst(ins$56);
      return b$80;
    case 183:
      b$82 = is_well_dst(ins$56);
      return b$82;
    case 199:
      b$84 = is_shift_range(ins$56, 64U);
      return b$84;
    case 15:
      b$86 = is_well_dst(ins$56);
      if (b$86) {
        b0 = is_well_src(ins$56);
        return b0;
      } else {
        return 0;
      }
    case 31:
      b$90 = is_well_dst(ins$56);
      if (b$90) {
        b0$92 = is_well_src(ins$56);
        return b0$92;
      } else {
        return 0;
      }
    case 47:
      b$94 = is_well_dst(ins$56);
      if (b$94) {
        b0$96 = is_well_src(ins$56);
        return b0$96;
      } else {
        return 0;
      }
    case 63:
      b$98 = is_well_dst(ins$56);
      if (b$98) {
        b0$100 = is_well_src(ins$56);
        return b0$100;
      } else {
        return 0;
      }
    case 79:
      b$102 = is_well_dst(ins$56);
      if (b$102) {
        b0$104 = is_well_src(ins$56);
        return b0$104;
      } else {
        return 0;
      }
    case 95:
      b$106 = is_well_dst(ins$56);
      if (b$106) {
        b0$108 = is_well_src(ins$56);
        return b0$108;
      } else {
        return 0;
      }
    case 111:
      b$110 = is_well_dst(ins$56);
      if (b$110) {
        b0$112 = is_well_src(ins$56);
        return b0$112;
      } else {
        return 0;
      }
    case 127:
      b$114 = is_well_dst(ins$56);
      if (b$114) {
        b0$116 = is_well_src(ins$56);
        return b0$116;
      } else {
        return 0;
      }
    case 159:
      b$118 = is_well_dst(ins$56);
      if (b$118) {
        b0$120 = is_well_src(ins$56);
        return b0$120;
      } else {
        return 0;
      }
    case 175:
      b$122 = is_well_dst(ins$56);
      if (b$122) {
        b0$124 = is_well_src(ins$56);
        return b0$124;
      } else {
        return 0;
      }
    case 191:
      b$126 = is_well_dst(ins$56);
      if (b$126) {
        b0$128 = is_well_src(ins$56);
        return b0$128;
      } else {
        return 0;
      }
    case 207:
      b$130 = is_well_dst(ins$56);
      if (b$130) {
        b0$132 = is_well_src(ins$56);
        return b0$132;
      } else {
        return 0;
      }
    case 4:
      b$134 = is_well_dst(ins$56);
      return b$134;
    case 20:
      b$136 = is_well_dst(ins$56);
      return b$136;
    case 36:
      b$138 = is_well_dst(ins$56);
      return b$138;
    case 52:
      b$140 = is_not_div_by_zero(ins$56);
      return b$140;
    case 68:
      b$142 = is_well_dst(ins$56);
      return b$142;
    case 84:
      b$144 = is_well_dst(ins$56);
      return b$144;
    case 100:
      b$146 = is_shift_range(ins$56, 32U);
      return b$146;
    case 116:
      b$148 = is_shift_range(ins$56, 32U);
      return b$148;
    case 132:
      b$150 = is_well_dst(ins$56);
      return b$150;
    case 148:
      b$152 = is_not_div_by_zero(ins$56);
      return b$152;
    case 164:
      b$154 = is_well_dst(ins$56);
      return b$154;
    case 180:
      b$156 = is_well_dst(ins$56);
      return b$156;
    case 196:
      b$158 = is_shift_range(ins$56, 32U);
      return b$158;
    case 12:
      b$160 = is_well_dst(ins$56);
      if (b$160) {
        b0$162 = is_well_src(ins$56);
        return b0$162;
      } else {
        return 0;
      }
    case 28:
      b$164 = is_well_dst(ins$56);
      if (b$164) {
        b0$166 = is_well_src(ins$56);
        return b0$166;
      } else {
        return 0;
      }
    case 44:
      b$168 = is_well_dst(ins$56);
      if (b$168) {
        b0$170 = is_well_src(ins$56);
        return b0$170;
      } else {
        return 0;
      }
    case 60:
      b$172 = is_well_dst(ins$56);
      if (b$172) {
        b0$174 = is_well_src(ins$56);
        return b0$174;
      } else {
        return 0;
      }
    case 76:
      b$176 = is_well_dst(ins$56);
      if (b$176) {
        b0$178 = is_well_src(ins$56);
        return b0$178;
      } else {
        return 0;
      }
    case 92:
      b$180 = is_well_dst(ins$56);
      if (b$180) {
        b0$182 = is_well_src(ins$56);
        return b0$182;
      } else {
        return 0;
      }
    case 108:
      b$184 = is_well_dst(ins$56);
      if (b$184) {
        b0$186 = is_well_src(ins$56);
        return b0$186;
      } else {
        return 0;
      }
    case 124:
      b$188 = is_well_dst(ins$56);
      if (b$188) {
        b0$190 = is_well_src(ins$56);
        return b0$190;
      } else {
        return 0;
      }
    case 156:
      b$192 = is_well_dst(ins$56);
      if (b$192) {
        b0$194 = is_well_src(ins$56);
        return b0$194;
      } else {
        return 0;
      }
    case 172:
      b$196 = is_well_dst(ins$56);
      if (b$196) {
        b0$198 = is_well_src(ins$56);
        return b0$198;
      } else {
        return 0;
      }
    case 188:
      b$200 = is_well_dst(ins$56);
      if (b$200) {
        b0$202 = is_well_src(ins$56);
        return b0$202;
      } else {
        return 0;
      }
    case 204:
      b$204 = is_well_dst(ins$56);
      if (b$204) {
        b0$206 = is_well_src(ins$56);
        return b0$206;
      } else {
        return 0;
      }
    case 24:
      b$208 = is_well_dst(ins$56);
      return b$208;
    case 16:
      b$210 = is_well_dst(ins$56);
      return b$210;
    case 97:
      b$212 = is_well_dst(ins$56);
      if (b$212) {
        b0$214 = is_well_src(ins$56);
        return b0$214;
      } else {
        return 0;
      }
    case 105:
      b$216 = is_well_dst(ins$56);
      if (b$216) {
        b0$218 = is_well_src(ins$56);
        return b0$218;
      } else {
        return 0;
      }
    case 113:
      b$220 = is_well_dst(ins$56);
      if (b$220) {
        b0$222 = is_well_src(ins$56);
        return b0$222;
      } else {
        return 0;
      }
    case 121:
      b$224 = is_well_dst(ins$56);
      if (b$224) {
        b0$226 = is_well_src(ins$56);
        return b0$226;
      } else {
        return 0;
      }
    case 98:
      b$228 = is_well_dst(ins$56);
      return b$228;
    case 106:
      b$230 = is_well_dst(ins$56);
      return b$230;
    case 114:
      b$232 = is_well_dst(ins$56);
      return b$232;
    case 122:
      b$234 = is_well_dst(ins$56);
      return b$234;
    case 99:
      b$236 = is_well_dst(ins$56);
      if (b$236) {
        b0$238 = is_well_src(ins$56);
        return b0$238;
      } else {
        return 0;
      }
    case 107:
      b$240 = is_well_dst(ins$56);
      if (b$240) {
        b0$242 = is_well_src(ins$56);
        return b0$242;
      } else {
        return 0;
      }
    case 115:
      b$244 = is_well_dst(ins$56);
      if (b$244) {
        b0$246 = is_well_src(ins$56);
        return b0$246;
      } else {
        return 0;
      }
    case 123:
      b$248 = is_well_dst(ins$56);
      if (b$248) {
        b0$250 = is_well_src(ins$56);
        return b0$250;
      } else {
        return 0;
      }
    case 5:
      ofs$252 = get_offset(ins$56);
      b$254 = is_well_jump(pc$50, len$52, ofs$252);
      return b$254;
    case 21:
      ofs$256 = get_offset(ins$56);
      b$258 = is_well_jump(pc$50, len$52, ofs$256);
      return b$258;
    case 37:
      ofs$260 = get_offset(ins$56);
      b$262 = is_well_jump(pc$50, len$52, ofs$260);
      return b$262;
    case 53:
      ofs$264 = get_offset(ins$56);
      b$266 = is_well_jump(pc$50, len$52, ofs$264);
      return b$266;
    case 165:
      ofs$268 = get_offset(ins$56);
      b$270 = is_well_jump(pc$50, len$52, ofs$268);
      return b$270;
    case 181:
      ofs$272 = get_offset(ins$56);
      b$274 = is_well_jump(pc$50, len$52, ofs$272);
      return b$274;
    case 69:
      ofs$276 = get_offset(ins$56);
      b$278 = is_well_jump(pc$50, len$52, ofs$276);
      return b$278;
    case 85:
      ofs$280 = get_offset(ins$56);
      b$282 = is_well_jump(pc$50, len$52, ofs$280);
      return b$282;
    case 101:
      ofs$284 = get_offset(ins$56);
      b$286 = is_well_jump(pc$50, len$52, ofs$284);
      return b$286;
    case 117:
      ofs$288 = get_offset(ins$56);
      b$290 = is_well_jump(pc$50, len$52, ofs$288);
      return b$290;
    case 197:
      ofs$292 = get_offset(ins$56);
      b$294 = is_well_jump(pc$50, len$52, ofs$292);
      return b$294;
    case 213:
      ofs$296 = get_offset(ins$56);
      b$298 = is_well_jump(pc$50, len$52, ofs$296);
      return b$298;
    case 29:
      ofs$300 = get_offset(ins$56);
      b$302 = is_well_jump(pc$50, len$52, ofs$300);
      return b$302;
    case 45:
      ofs$304 = get_offset(ins$56);
      b$306 = is_well_jump(pc$50, len$52, ofs$304);
      return b$306;
    case 61:
      ofs$308 = get_offset(ins$56);
      b$310 = is_well_jump(pc$50, len$52, ofs$308);
      return b$310;
    case 173:
      ofs$312 = get_offset(ins$56);
      b$314 = is_well_jump(pc$50, len$52, ofs$312);
      return b$314;
    case 189:
      ofs$316 = get_offset(ins$56);
      b$318 = is_well_jump(pc$50, len$52, ofs$316);
      return b$318;
    case 77:
      ofs$320 = get_offset(ins$56);
      b$322 = is_well_jump(pc$50, len$52, ofs$320);
      return b$322;
    case 93:
      ofs$324 = get_offset(ins$56);
      b$326 = is_well_jump(pc$50, len$52, ofs$324);
      return b$326;
    case 109:
      ofs$328 = get_offset(ins$56);
      b$330 = is_well_jump(pc$50, len$52, ofs$328);
      return b$330;
    case 125:
      ofs$332 = get_offset(ins$56);
      b$334 = is_well_jump(pc$50, len$52, ofs$332);
      return b$334;
    case 205:
      ofs$336 = get_offset(ins$56);
      b$338 = is_well_jump(pc$50, len$52, ofs$336);
      return b$338;
    case 221:
      ofs$340 = get_offset(ins$56);
      b$342 = is_well_jump(pc$50, len$52, ofs$340);
      return b$342;
    case 133:
      return 1;
    case 149:
      return 1;
    default:
      return 0;
    
  }
}

_Bool bpf_verifier_aux(unsigned int pc$344)
{
  unsigned int len$346;
  unsigned long long ins64;
  unsigned int op$350;
  unsigned int n$352;
  _Bool b$354;
  len$346 = eval_ins_len();
  ins64 = eval_ins(pc$344 - 1U - len$346);
  op$350 = get_opcode(ins64);
  if (pc$344 == 0U) {
    return ins64 == 149LLU;
  } else {
    n$352 = pc$344 - 1U;
    b$354 = bpf_verifier_aux2(pc$344, len$346, op$350, ins64);
    if (b$354) {
      return bpf_verifier_aux(n$352);
    } else {
      return 0;
    }
  }
}

_Bool bpf_verifier(void)
{
  unsigned int len$356;
  len$356 = eval_ins_len();
  if (1U <= len$356) {
    if (len$356 <= 4294967295U / 8) {
      return bpf_verifier_aux(len$356 - 1);
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}


