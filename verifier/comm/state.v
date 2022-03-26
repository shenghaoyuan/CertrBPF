From compcert.cfrontend Require Csyntax Ctypes Cop.
From compcert.common Require Import Values Memory AST.
From compcert.lib Require Import Integers.

From bpf.comm Require Import List64 BinrBPF.

From Coq Require Import List ZArith.
Import ListNotations.

Record state := mkst {
  ins_len : nat;
  ins     : MyListType;
}.

Definition init_state: state := {|
  ins_len := 0;
  ins     := default_list;
 |}.


Definition eval_ins_len (st: state): nat := ins_len st.
Definition eval_ins (idx: int) (st: state): int64 := MyListIndexs32 (ins st) idx.

Definition is_well_dst' (i: int64) : bool := Int.cmpu Cle (Int.repr (get_dst i)) (Int.repr 10).

Definition is_well_src' (i: int64) : bool := Int.cmpu Cle (Int.repr (get_src i)) (Int.repr 10).

Definition is_well_jump' (pc len: nat) (ofs: int) : bool :=
  Int.cmpu Cle (Int.add (Int.repr (Z.of_nat pc)) ofs) (Int.repr (Z.of_nat (len - 2))).

Definition is_not_div_by_zero' (i: int64) : bool :=
  Int.cmp Cne (get_immediate i) Int.zero.

Definition is_shift_range' (i: int64) (upper: int): bool :=
  (Int.cmp Cle Int.zero (get_immediate i)) && (Int.cmp Cle (get_immediate i) upper).

Definition nat2int2 (pc len: nat) : int := Int.repr (Z.of_nat (len - 1 - pc)).