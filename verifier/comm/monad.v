From compcert Require Import AST Integers Values Memory.

From bpf.comm Require Import BinrBPF.
From bpf.verifier.comm Require Import state.
From Coq Require Import ZArith.

Definition M (A: Type) := state -> option (A * state).

Definition returnM {A: Type} (a: A) : M A := fun st => Some (a, st).
Definition returnS: M state := fun st => Some (st, st).
Definition errorM {A: Type} : M A := fun st => None.
Definition bindM {A B: Type} (x: M A) (f: A -> M B) : M B :=
  fun st =>
    match x st with
    | None => None
    | Some (x', st') => (f x') st'
    end.

Definition eval_ins_len : M nat := fun st => Some (eval_ins_len st, st).

Definition eval_ins (idx: int) : M int64 := fun st => Some (eval_ins idx st, st).


Declare Scope monad_scope.
Notation "'do' x <- a ; b" :=
  (bindM a (fun x => b))
    (at level 200, x name, a at level 100, b at level 200)
  : monad_scope.