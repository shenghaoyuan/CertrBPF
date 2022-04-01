From compcert Require Import Integers Values AST Ctypes.
From Coq Require Import ZArith.

From bpf.comm Require Import BinrBPF.
From bpf.verifier.comm Require Import state monad.
From bpf.model Require Import Syntax.
From bpf.verifier.synthesismodel Require Import opcode_synthesis.

Open Scope nat_scope.
Open Scope monad_scope.

Definition is_well_dst (i: int64) : M bool := returnM (is_well_dst' i).

Definition is_well_src (i: int64) : M bool := returnM (is_well_src' i).

Definition is_well_jump (pc len: nat) (ofs: int) : M bool := returnM (is_well_jump' pc len ofs).

Definition is_not_div_by_zero (i: int64) : M bool := returnM (is_not_div_by_zero' i).

Definition is_shift_range (i: int64) (upper: int): M bool := returnM (is_shift_range' i upper).

Definition get_opcode (ins: int64): M nat := returnM (get_opcode ins).

Definition get_offset (i: int64): M int := returnM (get_offset i).

Definition bpf_verifier_opcode_alu (op: nat) (ins: int64) (a: int) : M bool :=
  match nat_to_opcode_alu op with
  | ALU_DIV => (**r DIV_IMM *)
    do b <- is_not_div_by_zero ins;
      returnM b
  | ALU_SHIFT => (**r SHIFT_IMM *)
    do b <- is_shift_range ins a;
      returnM b
  | ALU_IMM_Normal => (**r ALU_IMM *)
    do b <- is_well_dst ins;
      returnM b
  | ALU_REG_Normal => (**r ALU_REG *)
    do b0 <- is_well_dst ins;
      if b0 then
        do b1 <- is_well_src ins;
          returnM b1
      else
        returnM false
  | ALU_ILLEGAL => returnM false
  end.

Definition bpf_verifier_opcode_branch (pc len op: nat) (ins: int64) : M bool :=
  match nat_to_opcode_branch op with
  | JMP_IMM =>
    do ofs <- get_offset ins;
    do b0 <- is_well_dst ins;
      if b0 then
        do b   <- is_well_jump pc len ofs;
          returnM b
      else
        returnM false
  | JMP_REG =>
    do ofs <- get_offset ins;
    do b0 <- is_well_dst ins;
      if b0 then
        do b1 <- is_well_src ins;
          if b1 then
            do b   <- is_well_jump pc len ofs;
              returnM b
          else
            returnM false
      else
        returnM false
  | JMP_SP => returnM true
  | JMP_ILLEGAL => returnM false
  end.

Definition bpf_verifier_opcode_load_imm (op: nat) (ins: int64) : M bool :=
  match nat_to_opcode_load_imm op with
  | LD_IMM_Normal  =>
    do b <- is_well_dst ins;
      returnM b
  | LD_IMM_ILLEGAL => returnM false
  end.

Definition bpf_verifier_opcode_load_reg (op: nat) (ins: int64) : M bool :=
  match nat_to_opcode_load_reg op with
  | LD_REG_Normal  =>
    do b0 <- is_well_dst ins;
      if b0 then
        do b1 <- is_well_src ins;
          returnM b1
      else
        returnM false
  | LD_REG_ILLEGAL => returnM false
  end.

Definition bpf_verifier_opcode_store_imm (op: nat) (ins: int64) : M bool :=
  match nat_to_opcode_store_imm op with
  | ST_IMM_Normal  =>
    do b <- is_well_dst ins;
      returnM b
  | ST_IMM_ILLEGAL => returnM false
  end.

Definition bpf_verifier_opcode_store_reg (op: nat) (ins: int64) : M bool :=
  match nat_to_opcode_store_reg op with
  | ST_REG_Normal  =>
    do b0 <- is_well_dst ins;
      if b0 then
        do b1 <- is_well_src ins;
          returnM b1
      else
        returnM false
  | ST_REG_ILLEGAL => returnM false
  end.

Definition bpf_verifier_aux2 (pc len op: nat) (ins: int64) : M bool :=
  match nat_to_opcode op with
  | ALU64  (**r 0xX7 / 0xXf *) => bpf_verifier_opcode_alu op ins (Int.repr 64)
  | ALU32  (**r 0xX4 / 0xXc *) => bpf_verifier_opcode_alu op ins (Int.repr 32)
  | Branch (**r 0xX5 / 0xXd *) => bpf_verifier_opcode_branch pc len op ins
  | LD_IMM (**r 0xX8 *)        => bpf_verifier_opcode_load_imm op ins
  | LD_REG (**r 0xX1/0xX9 *)   => bpf_verifier_opcode_load_reg op ins
  | ST_IMM (**r 0xX2/0xXa *)   => bpf_verifier_opcode_store_imm op ins
  | ST_REG (**r 0xX3/0xXb *)   => bpf_verifier_opcode_store_reg op ins
  | ILLEGAL => returnM false
  end.

Fixpoint bpf_verifier_aux (pc: nat): M bool := (**r pc: len-1, len-2, ... 0 *)
  do len  <- eval_ins_len;
  do ins64<- eval_ins (Int.repr (Z.of_nat (len - 1 - pc))); (**r len-pc: 0, 1, 2, etc... len -1 *)
  do op   <- get_opcode ins64;
    match pc with
    | O => returnM (Int64.eq ins64 (Int64.repr 0x95))
    | S n =>
      do b <- bpf_verifier_aux2 pc len op ins64;
        if b then
          bpf_verifier_aux n
        else
          returnM false
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
