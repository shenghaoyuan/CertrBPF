From bpf.comm Require Import rBPFAST List64 MemRegion Regs Flag.

From Coq Require Import List Lia ZArith.
From compcert Require Import Integers Values Clight Memory AST.
Import ListNotations.

From bpf.verifier.comm Require Import state monad.
From bpf.verifier.simulation Require Import VerifierSimulation VerifierClightlogic VerifierCommonLib.

Open Scope Z_scope.

Definition int64_correct (x:int64) (v: val) :=
  Vlong x = v.

Definition val64_correct (x:val) (v: val) :=
  x = v /\ exists vl, x = Vlong vl.

Definition val32_correct (x:val) (v: val) :=
  x = v /\ exists vi, x = Vint vi.

Definition val_ptr_correct {S:special_blocks} (x:val) (v: val) (st: state.state) (m:Mem.mem) :=
  x = v /\
  match_state  st m.


Definition int32_correct (x: int) (v: val) :=
  Vint x = v.

Definition nat_correct (x: nat) (v: val) :=
  Vint (Int.repr (Z.of_nat x)) = v /\ Z.of_nat x <= Int.max_unsigned.

Definition reg_correct (r: reg) (v: val) :=
    v = Vint (Int.repr (id_of_reg r)).

Definition bool_correct (b:bool) (v:val) :=
  v = Vint (if b then Integers.Int.one else Integers.Int.zero).


Open Scope nat_scope.

Definition opcode_correct (x: nat) (v: val) :=
   Vint (Int.repr (Z.of_nat x)) = v /\ x <= 255.

Definition opcode_and_07_correct (x: nat) (v: val) :=
   Vint (Int.repr (Z.of_nat (Nat.land x 0x07))) = v /\ x <= 255.

Definition is_state_handle {S: special_blocks} (v: val) := v = Vptr st_blk Ptrofs.zero.