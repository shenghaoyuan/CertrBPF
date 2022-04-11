From compcert Require Import Integers Values AST Ctypes.
From Coq Require Import ZArith Lia.

From bpf.comm Require Import BinrBPF.
From bpf.verifier.comm Require Import state monad.
From bpf.verifier.synthesismodel Require Import opcode_synthesis verifier_synthesis.


Open Scope Z_scope.


Lemma bpf_verifier_aux_never_none:
  forall st k,
      bpf_verifier_aux k (ins_len st) st <> None.
Proof.
  intros.
  induction k.
  - simpl.
    unfold returnM.
    intro Hfalse; inversion Hfalse.
  - simpl.
    unfold eval_ins, get_opcode, bpf_verifier_aux2, bindM, returnM.
    unfold is_shift_range, is_not_div_by_zero, state.eval_ins, is_well_dst, is_well_src, get_offset, is_well_jump, bindM, returnM.
    destruct nat_to_opcode.
    * unfold bpf_verifier_opcode_alu64.
      unfold is_well_dst, is_not_div_by_zero64, is_shift_range64, is_well_src, bindM, returnM.
      destruct nat_to_opcode_alu.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_alu32.
      unfold is_well_dst, is_not_div_by_zero, is_shift_range, is_well_src, bindM, returnM.
      destruct nat_to_opcode_alu.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_branch.
      unfold get_offset, is_well_dst, is_well_jump, is_well_src, is_dst_R0, bindM, returnM.
      destruct nat_to_opcode_branch.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_load_imm.
      unfold is_well_dst, bindM, returnM.
      destruct nat_to_opcode_load_imm.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_load_reg.
      unfold is_well_dst, is_well_src, bindM, returnM.
      destruct nat_to_opcode_load_reg.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_store_imm.
      unfold is_well_dst, bindM, returnM.
      destruct nat_to_opcode_store_imm.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * unfold bpf_verifier_opcode_store_reg.
      unfold is_well_dst, is_well_src, bindM, returnM.
      destruct nat_to_opcode_store_reg.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end <> _ =>
        destruct X; [ | intro Hfalse; inversion Hfalse]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ <> _ =>
        destruct X; [assumption | intro Hfalse; inversion Hfalse]
      end.
      intro Hfalse; inversion Hfalse.
    * intro Hfalse; inversion Hfalse.
Qed.

Lemma bpf_verifier_aux_some:
  forall st k,
    exists res,
      bpf_verifier_aux k (ins_len st) st = Some res.
Proof.
  intros.
  destruct bpf_verifier_aux eqn: Haux.
  exists p; reflexivity.
  eapply bpf_verifier_aux_never_none in Haux.
  inversion Haux.
Qed.

Theorem verifier_never_none:
  forall st,
      bpf_verifier st <> None.
Proof.
  intros.
  unfold bpf_verifier.
  unfold eval_ins_len, bindM, returnM.
  unfold state.eval_ins_len.
  match goal with
  | |- (if ?X then _ else _) _ <> _ =>
    destruct X; [| intro Hfalse; inversion Hfalse]
  end.
  match goal with
  | |- (if ?X then _ else _) _ <> _ =>
    destruct X; [| intro Hfalse; inversion Hfalse]
  end.
  destruct bpf_verifier_aux eqn: Haux.
  destruct p.
  destruct b; [| intro Hfalse; inversion Hfalse].
  unfold eval_ins.
  intro Hfalse; inversion Hfalse.
  eapply bpf_verifier_aux_never_none in Haux; inversion Haux.
Qed.

From bpf.isolation Require Import VerifierInv.

Lemma verifier_aux_inv_iff:
  forall st k,
    verifier_synthesis.bpf_verifier_aux k (ins_len st) st =
      Some (bpf_verifier_aux k (ins_len st) st, st).
Proof.
  intros.
  induction k; simpl.
  - unfold returnM; reflexivity.
  - unfold eval_ins, get_opcode, bpf_verifier_aux2, bindM, returnM.
    unfold is_shift_range, is_not_div_by_zero, is_not_div_by_zero64, is_shift_range64, state.eval_ins, is_well_dst, is_well_src, get_offset, is_well_jump, verifier_synthesis.bpf_verifier_aux2, bindM, returnM.
    destruct nat_to_opcode.
    + unfold bpf_verifier_opcode_alu64.
      unfold verifier_synthesis.is_well_dst, verifier_synthesis.is_not_div_by_zero64, verifier_synthesis.is_shift_range64, verifier_synthesis.is_well_src, bindM, returnM.
      unfold is_well_dst', is_not_div_by_zero64', is_shift_range64', is_well_src', bindM, returnM.
      destruct nat_to_opcode_alu.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      unfold Int.cmpu.
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_alu32.
      unfold verifier_synthesis.is_well_dst, verifier_synthesis.is_not_div_by_zero, verifier_synthesis.is_shift_range, verifier_synthesis.is_well_src, bindM, returnM.
      unfold is_well_dst', is_not_div_by_zero', is_shift_range', is_well_src', bindM, returnM.
      destruct nat_to_opcode_alu.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_branch.
      unfold get_offset, verifier_synthesis.is_well_dst, verifier_synthesis.is_well_jump, verifier_synthesis.is_well_src, bindM, returnM.
      unfold is_well_dst', is_well_jump', is_well_src', is_dst_R0, is_dst_R0', bindM, returnM.
      destruct nat_to_opcode_branch.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_load_imm.
      unfold verifier_synthesis.is_well_dst, is_well_dst', bindM, returnM.
      destruct nat_to_opcode_load_imm.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_load_reg.
      unfold verifier_synthesis.is_well_dst, is_well_dst', verifier_synthesis.is_well_src, is_well_src', bindM, returnM.
      destruct nat_to_opcode_load_reg.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_store_imm.
      unfold verifier_synthesis.is_well_dst, is_well_dst', bindM, returnM.
      destruct nat_to_opcode_store_imm.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + unfold bpf_verifier_opcode_store_reg.
      unfold verifier_synthesis.is_well_dst, is_well_dst', verifier_synthesis.is_well_src, is_well_src', bindM, returnM.
      destruct nat_to_opcode_store_reg.
      all: try
      match goal with
      | |- match (if ?X then _ else _) _ with _ => _ end = _ =>
        destruct X; [rewrite Bool.andb_true_l | rewrite Bool.andb_false_l; reflexivity ]
      end.
      all: try
      match goal with
      | |- (if ?X then _ else _) _ = _ =>
        destruct X; [assumption | reflexivity]
      end.
      reflexivity.
    + reflexivity.
Qed.

Lemma verifier_inv_iff:
  forall st,
    (ins_len st) = (List.length (ins st)) ->
      verifier_synthesis.bpf_verifier st = Some (VerifierInv.bpf_verifier st, st).
Proof.
  unfold verifier_synthesis.bpf_verifier, bpf_verifier, eval_ins_len, state.eval_ins_len.
  unfold bindM, returnM.
  intros.
  match goal with
  | |- (if ?X then _ else _) _ = Some _ =>
    destruct X eqn: Hle_low; [ rewrite Nat.leb_le in Hle_low| reflexivity]
  end.
  match goal with
  | |- (if ?X then _ else _) _ = Some _ =>
    destruct X eqn: Hle_high; [ rewrite Nat.leb_le in Hle_high| reflexivity]
  end.

  rewrite verifier_aux_inv_iff.
  unfold eval_ins.
  destruct bpf_verifier_aux eqn: Haux; [| reflexivity].
  unfold state.eval_ins.
  reflexivity.
Qed.

Close Scope Z_scope.