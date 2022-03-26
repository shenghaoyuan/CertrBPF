From compcert Require Import Integers Values AST Ctypes.
From Coq Require Import ZArith.

From bpf.comm Require Import BinrBPF.
From bpf.verifier.comm Require Import state monad.
From bpf.verifier.synthesismodel Require Import opcode.

Open Scope nat_scope.
Open Scope monad_scope.

Definition is_well_dst (i: int64) : M bool := returnM (is_well_dst' i).

Definition is_well_src (i: int64) : M bool := returnM (is_well_src' i).

Definition is_well_jump (pc len: nat) (ofs: int) : M bool := returnM (is_well_jump' pc len ofs).

Definition is_not_div_by_zero (i: int64) : M bool := returnM (is_not_div_by_zero' i).

Definition is_shift_range (i: int64) (upper: int): M bool := returnM (is_shift_range' i upper).

Definition get_opcode (ins: int64): M nat := returnM (get_opcode ins).

Definition get_offset (i: int64): M int := returnM (get_offset i).

Fixpoint bpf_verifier_aux (pc: nat): M bool := (**r pc: len-1, len-2, ... 0 *)
  do len  <- eval_ins_len;
  do ins64<- eval_ins (Int.repr (Z.of_nat (len - 1 - pc))); (**r len-pc: 0, 1, 2, etc... len -1 *)
  do op   <- get_opcode ins64;
    match pc with
    | O => returnM (Nat.eqb op 0x95)
    | S n =>
      match nat2opcode op with
      (**r ALU_IMM *)
      | ADD64_IMM | SUB64_IMM | MUL64_IMM | OR64_IMM | AND64_IMM | NEG64 | XOR64_IMM | MOV64_IMM
      | ADD32_IMM | SUB32_IMM | MUL32_IMM | OR32_IMM | AND32_IMM | NEG32 | XOR32_IMM | MOV32_IMM
      | STW | STH | STB | STDW =>
        do b <- is_well_dst ins64;
          if b then
            bpf_verifier_aux n
          else
            returnM false
      (**r DIV_IMM *)
      | DIV64_IMM | DIV32_IMM | MOD64_IMM | MOD32_IMM =>
        do b <- is_not_div_by_zero ins64;
          if b then
            bpf_verifier_aux n
          else
            returnM false
      (**r SHIFT64_IMM *)
      | LSH64_IMM | RSH64_IMM | ARSH64_IMM =>
        do b <- is_shift_range ins64 (Int.repr 64%Z);
          if b then
            bpf_verifier_aux n
          else
            returnM false
      (**r SHIFT32_IMM *)
      | LSH32_IMM | RSH32_IMM | ARSH32_IMM =>
        do b <- is_shift_range ins64 (Int.repr 32%Z);
          if b then
            bpf_verifier_aux n
          else
            returnM false
      (**r LDDW *)
      | LDDW =>
        (**r avoid lddw imm; imm; null: pc + 2 >= len *)
        do b   <- is_well_jump pc len (Int.repr 2%Z);
          if b then
            bpf_verifier_aux (n-1)
          else
            returnM false
      (**r we don't need to check pc + 1, check the len-1 is exit is enough *)
      (**r JMP *)
      | JA | JEQ_IMM | JGT_IMM | JGE_IMM | JLT_IMM | JLE_IMM | JSET_IMM
      | JNE_IMM | JSGT_IMM | JSGE_IMM | JSLT_IMM | JSLE_IMM
      | JEQ_REG | JGT_REG | JGE_REG | JLT_REG | JLE_REG | JSET_REG
      | JNE_REG | JSGT_REG | JSGE_REG | JSLT_REG | JSLE_REG =>
        do ofs <- get_offset ins64;
        do b   <- is_well_jump pc len ofs;
          if b then
            bpf_verifier_aux (n-1)
          else
            returnM false
      | ADD64_REG | SUB64_REG | MUL64_REG | DIV64_REG | OR64_REG | AND64_REG | LSH64_REG
      | RSH64_REG | MOD64_REG | XOR64_REG | MOV64_REG | ARSH64_REG
      | ADD32_REG | SUB32_REG | MUL32_REG | DIV32_REG | OR32_REG | AND32_REG | LSH32_REG
      | RSH32_REG | MOD32_REG | XOR32_REG | MOV32_REG | ARSH32_REG
      | LDXW | LDXH | LDXB | LDXDW | STXW | STXH | STXB | STXDW =>
        do b0 <- is_well_dst ins64;
          if b0 then
            do b1 <- is_well_src ins64;
            if b1 then
              bpf_verifier_aux n
            else
              returnM false
          else
            returnM false

      | CALL | EXIT => bpf_verifier_aux (n-1)

      | ILLGEL => returnM false
      end
    end.

Definition bpf_verifier: M bool :=
  do len  <- eval_ins_len;
  (**r (0, Int.max_unsigned/8): at least one instruction, and at most Int.max_unsigned/8 because of memory region *)
    if Nat.leb 1 len then
      if Nat.leb len ((Z.to_nat Ptrofs.max_unsigned)/8) then
        bpf_verifier_aux (len - 1)
      else
        returnM false
    else
      returnM false.

Close Scope monad_scope.
Close Scope nat_scope.
