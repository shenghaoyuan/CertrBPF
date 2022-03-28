From compcert Require Import Integers Values AST Ctypes.
From Coq Require Import ZArith.
From dx.Type Require Bool Nat.

From bpf.comm Require Import rBPFValues BinrBPF.
From bpf.dxmodel Require Import DxIntegers DxNat.
From bpf.verifier.comm Require Import state.
From bpf.verifier.proofmodel Require Import opcode.
From bpf.verifier.dxmodel Require Import Dxmonad.

Open Scope nat_scope.
Open Scope monad_scope.

Definition is_well_dst (i: int64_t) : M bool := returnM (is_well_dst' i).

Definition is_well_src (i: int64_t) : M bool := returnM (is_well_src' i).

Definition is_well_jump (pc len: nat) (ofs: sint32_t) : M bool := returnM (is_well_jump' pc len ofs).

Definition is_not_div_by_zero (i: int64_t) : M bool := returnM (is_not_div_by_zero' i).

Definition is_shift_range (i: int64_t) (upper: uint32_t): M bool := returnM (is_shift_range' i upper).

Definition get_opcode (ins: int64_t): M nat := returnM (get_opcode ins).

Definition get_offset (i: int64_t): M sint32_t := returnM (get_offset i).

Definition nat2opcode (n: nat): M opcode := returnM (nat2opcode n).

Fixpoint bpf_verifier_aux (pc: nat): M bool := (**r pc: len-1, len-2, ... 0 *)
  do len  <-- eval_ins_len;
  do ins64<-- eval_ins (nat2int2 pc len); (**r len-pc: 0, 1, 2, etc... len -1 *)
  do op   <-- get_opcode ins64;
    match pc with
    | O => returnM (Int64.eq ins64 int64_0x95)
    | S n =>
      do opc <-- nat2opcode op;
        match opc with
        (**r ALU_IMM *)
        | ADD64_IMM | SUB64_IMM | MUL64_IMM | OR64_IMM | AND64_IMM | NEG64 | XOR64_IMM | MOV64_IMM
        | ADD32_IMM | SUB32_IMM | MUL32_IMM | OR32_IMM | AND32_IMM | NEG32 | XOR32_IMM | MOV32_IMM
        | LDDW_LOW | LDDW_HIGH
        | STW | STH | STB | STDW =>
          do b <-- is_well_dst ins64;
            if b then
              bpf_verifier_aux n
            else
              returnM false
        (**r DIV_IMM *)
        | DIV64_IMM | DIV32_IMM | MOD64_IMM | MOD32_IMM =>
          do b <-- is_not_div_by_zero ins64;
            if b then
              bpf_verifier_aux n
            else
              returnM false
        (**r SHIFT64_IMM *)
        | LSH64_IMM | RSH64_IMM | ARSH64_IMM =>
          do b <-- is_shift_range ins64 int32_64;
            if b then
              bpf_verifier_aux n
            else
              returnM false
        (**r SHIFT32_IMM *)
        | LSH32_IMM | RSH32_IMM | ARSH32_IMM =>
          do b <-- is_shift_range ins64 int32_32;
            if b then
              bpf_verifier_aux n
            else
              returnM false
        (**r we don't need to check pc + 1, check the len-1 is exit is enough *)
        (**r JMP *)
        | JA | JEQ_IMM | JGT_IMM | JGE_IMM | JLT_IMM | JLE_IMM | JSET_IMM
        | JNE_IMM | JSGT_IMM | JSGE_IMM | JSLT_IMM | JSLE_IMM
        | JEQ_REG | JGT_REG | JGE_REG | JLT_REG | JLE_REG | JSET_REG
        | JNE_REG | JSGT_REG | JSGE_REG | JSLT_REG | JSLE_REG =>
          do ofs <-- get_offset ins64;
          do b   <-- is_well_jump pc len ofs;
            if b then
              bpf_verifier_aux n
            else
              returnM false
        | ADD64_REG | SUB64_REG | MUL64_REG | DIV64_REG | OR64_REG | AND64_REG | LSH64_REG
        | RSH64_REG | MOD64_REG | XOR64_REG | MOV64_REG | ARSH64_REG
        | ADD32_REG | SUB32_REG | MUL32_REG | DIV32_REG | OR32_REG | AND32_REG | LSH32_REG
        | RSH32_REG | MOD32_REG | XOR32_REG | MOV32_REG | ARSH32_REG
        | LDXW | LDXH | LDXB | LDXDW | STXW | STXH | STXB | STXDW =>
          do b <-- is_well_dst ins64;
            if b then
              do b0 <-- is_well_src ins64;
              if b0 then
                bpf_verifier_aux n
              else
                returnM false
            else
              returnM false

        | CALL | EXIT => bpf_verifier_aux n

        | ILLGEL => returnM false
        end
    end.

Definition bpf_verifier: M bool :=
  do len  <-- eval_ins_len;
  (**r (0, Int.max_unsigned/8): at least one instruction, and at most Int.max_unsigned/8 because of memory region *)
    if Int_leu (int32_1) (nat2int len) then
      if Int_leu (nat2int len) (Int.divu int32_max_unsigned int32_8) then
        bpf_verifier_aux (Nat.sub len nat8_1)
      else
        returnM false
    else
      returnM false.

Close Scope monad_scope.
Close Scope nat_scope.
