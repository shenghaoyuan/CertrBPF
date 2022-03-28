From Coq Require Import List ZArith.
Import ListNotations.

From compcert Require Import Integers.

From dx Require Import ResultMonad IR.

From bpf.comm Require Import InfComp GenMatchable CoqIntegers.
From bpf.verifier.proofmodel Require Import opcode.
From bpf.dxmodel Require Import DxNat.

(******************** Dx related *******************)

Open Scope Z_scope.

Definition opcodeCompilableType :=
  MkCompilableType opcode C_U8.

Definition opcodeCompilableTypeMatchableType : MatchableType:=
  Eval compute in
 (mkEnumMatchableType
    opcodeCompilableType  opcode_eqb
    (     (ADD64_IMM, 0x07)
       :: (SUB64_IMM, 0x17)
       :: (MUL64_IMM, 0x27)
       :: (DIV64_IMM, 0x37)
       :: (OR64_IMM,  0x47)
       :: (AND64_IMM, 0x57)
       :: (LSH64_IMM, 0x67)
       :: (RSH64_IMM, 0x77)
       :: (NEG64, 0x87)
       :: (MOD64_IMM, 0x97)
       :: (XOR64_IMM, 0xa7)
       :: (MOV64_IMM, 0xb7)
       :: (ARSH64_IMM,0xc7)

       :: (ADD64_REG, 0x0f)
       :: (SUB64_REG, 0x1f)
       :: (MUL64_REG, 0x2f)
       :: (DIV64_REG, 0x3f)
       :: (OR64_REG,  0x4f)
       :: (AND64_REG, 0x5f)
       :: (LSH64_REG, 0x6f)
       :: (RSH64_REG, 0x7f)
       :: (MOD64_REG, 0x9f)
       :: (XOR64_REG, 0xaf)
       :: (MOV64_REG, 0xbf)
       :: (ARSH64_REG,0xcf)


       :: (ADD32_IMM, 0x04)
       :: (SUB32_IMM, 0x14)
       :: (MUL32_IMM, 0x24)
       :: (DIV32_IMM, 0x34)
       :: (OR32_IMM,  0x44)
       :: (AND32_IMM, 0x54)
       :: (LSH32_IMM, 0x64)
       :: (RSH32_IMM, 0x74)
       :: (NEG32, 0x84)
       :: (MOD32_IMM, 0x94)
       :: (XOR32_IMM, 0xa4)
       :: (MOV32_IMM, 0xb4)
       :: (ARSH32_IMM,0xc4)

       :: (ADD32_REG, 0x0c)
       :: (SUB32_REG, 0x1c)
       :: (MUL32_REG, 0x2c)
       :: (DIV32_REG, 0x3c)
       :: (OR32_REG,  0x4c)
       :: (AND32_REG, 0x5c)
       :: (LSH32_REG, 0x6c)
       :: (RSH32_REG, 0x7c)
       :: (MOD32_REG, 0x9c)
       :: (XOR32_REG, 0xac)
       :: (MOV32_REG, 0xbc)
       :: (ARSH32_REG,0xcc)


       :: (LDDW_LOW, 0x18)
       :: (LDDW_HIGH,0x10)
       :: (LDXW,0x61)
       :: (LDXH,0x69)
       :: (LDXB,0x71)
       :: (LDXDW,0x79)
       :: (STW,0x62)
       :: (STH,0x6a)
       :: (STB,0x72)
       :: (STDW,0x7a)
       :: (STXW,0x63)
       :: (STXH,0x6b)
       :: (STXB,0x73)
       :: (STXDW,0x7b)


       :: (JA,0x05)
       :: (JEQ_IMM,0x15)
       :: (JGT_IMM,0x25)
       :: (JGE_IMM,0x35)
       :: (JLT_IMM,0xa5)
       :: (JLE_IMM,0xb5)
       :: (JSET_IMM,0x45)
       :: (JNE_IMM,0x55)
       :: (JSGT_IMM,0x65)
       :: (JSGE_IMM,0x75)
       :: (JSLT_IMM,0xc5)
       :: (JSLE_IMM,0xd5)

       :: (JEQ_REG,0x1d)
       :: (JGT_REG,0x2d)
       :: (JGE_REG,0x3d)
       :: (JLT_REG,0xad)
       :: (JLE_REG,0xbd)
       :: (JSET_REG,0x4d)
       :: (JNE_REG,0x5d)
       :: (JSGT_REG,0x6d)
       :: (JSGE_REG,0x7d)
       :: (JSLT_REG,0xcd)
       :: (JSLE_REG,0xdd)

       :: (CALL,0x85)
       :: (EXIT,0x95) :: nil)
    ILLGEL
    (fun m A => opcode_rect (fun _ => m A))).

Instance CINT : CType nat := mkCType _ (cType nat8CompilableType).
Instance COP : CType opcode := mkCType _ (cType opcodeCompilableType).


Definition nat2opcode_aluSymbolType :=
  MkCompilableSymbolType [nat8CompilableType] (Some opcodeCompilableType).

Definition Const_nat2opcode :=
  ltac: (mkprimitive nat2opcode
                (fun es => match es with
                           | [e1] => Ok (e1)
                           | _       => Err PrimitiveEncodingFailed
                           end)).
Close Scope Z_scope.

Module Exports.
  Definition opcodeCompilableTypeMatchableType  := opcodeCompilableTypeMatchableType.
  Definition Const_nat2opcode                   := Const_nat2opcode.
End Exports.