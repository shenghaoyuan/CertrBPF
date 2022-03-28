From compcert Require Import Integers Values AST Ctypes.
From Coq Require Import ZArith Lia.

From bpf.comm Require Import BinrBPF.
From bpf.verifier.comm Require Import state monad.
From bpf.verifier.proofmodel Require Import opcode verifier.
From bpf.isolation Require Import VerifierInv.


Open Scope Z_scope.
(**r verifier = true should imply
Definition verifier_inv' (l: list int64): Prop :=
  well_list_range l /\
  forall i, i < List.length l ->
    match List.nth_error l i with
    | Some ins =>
        well_dst ins /\ well_src ins /\
        well_lddw ins i (List.length l) /\
        well_jump ins i (List.length l)
    | None => False
    end.

Definition verifier_inv (st: state): Prop :=
  (ins_len st) = (List.length (ins st))  /\
  verifier_inv' (ins st).

*)

Lemma verifier_imply:
  forall st,
    (ins_len st) = (List.length (ins st)) ->
    bpf_verifier st = Some (true, st) ->
      well_list_range (ins st).
Proof.
  unfold bpf_verifier, well_list_range, eval_ins_len, state.eval_ins_len.
  unfold bindM, returnM.
  intros.
  rewrite <- H.
  match goal with
  | H: (if ?X then _ else _) _ = Some _ |- _ =>
    destruct X eqn: Hle_low; [ rewrite Nat.leb_le in Hle_low| inversion H]
  end.
  split; [lia |].
  match goal with
  | H: (if ?X then _ else _) _ = Some _ |- _ =>
    destruct X eqn: Hle_high; [ rewrite Nat.leb_le in Hle_high| inversion H]
  end.
  assert (Hle: Z.of_nat (ins_len st) <= Z.of_nat (Z.to_nat Ptrofs.max_unsigned / 8)) by lia.
  rewrite div_Zdiv in Hle; [| lia].
  change (Z.of_nat 8) with 8 in Hle.
  rewrite Z2Nat.id in Hle; [ | change Ptrofs.max_unsigned with 4294967295; lia].
  apply Zmult_gt_0_le_compat_r with (p:=8) in Hle; [| lia].
  change Ptrofs.max_unsigned with 4294967295 in *.
  change (4294967295 / 8 * 8) with 4294967288 in Hle.
  split.
  lia.
  unfold BinrBPF.get_opcode, List64.MyListIndexs32, List64.MyList.index_s32.
  assert (Hbpf0: bpf_verifier_aux 0 st = Some (true, st)). {
    clear - H0.
    revert H0.
    generalize (ins_len st - 1)%nat.
    intros.
    induction n.
    assumption.
    apply IHn.
    clear IHn.
    simpl in H0.
    unfold eval_ins_len, eval_ins, get_opcode,
    is_shift_range, is_not_div_by_zero, is_well_jump,
    is_well_dst, is_well_src, get_offset, bindM, returnM in H0.
    destruct nat2opcode eqn: Hop; try
    match goal with
    | H: (if ?X then _ else _) _ = Some _ |- _ =>
      destruct X eqn: Hif0; [ try assumption | inversion H]
    end.
    all: try
    match goal with
    | H: (if ?X then _ else _) _ = Some _ |- _ =>
      destruct X eqn: Hif1; [ try assumption | inversion H]
    end.
    all: try assumption.
    all: try inversion H0.
    match goal with
    | H: (if ?X then _ else _) _ = Some _ |- _ =>
      destruct X; [ assumption | inversion H]
    end.
    admit.
  }
  simpl in Hbpf0.
  unfold eval_ins_len, eval_ins, get_opcode, bindM, returnM in Hbpf0.
  unfold BinrBPF.get_opcode, state.eval_ins, List64.MyListIndexs32, state.eval_ins_len, List64.MyList.index_s32 in Hbpf0.
  rewrite ! Nat.sub_0_r in Hbpf0.
  rewrite Int.unsigned_repr in Hbpf0.
  inversion Hbpf0.
  clear Hbpf0.
  apply Int64.same_if_eq in H2.
  rewrite Nat2Z.id in H2.
  destruct List.nth_error eqn: Hnth.
  subst i.
  reflexivity.
  inversion H2.
  change Int.max_unsigned with 4294967295.
  lia.
Qed.

Close Scope Z_scope.
