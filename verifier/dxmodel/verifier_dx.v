From Coq Require Import BinNums List Ascii String Nat ZArith.
From Coq Require Import Numbers.AltBinNotations.
Import List.ListNotations.

From compcert.cfrontend Require Csyntax Ctypes.
From compcert.common Require Import Errors Values.
From compcert.lib Require Import Integers.
 

From dx Require Import ResultMonad IR CoqIR IRtoC DXModule DumpAsC.
From dx.Type Require Bool Nat.

From bpf.comm Require Import CoqIntegers.
From bpf.dxmodel Require Import DxIntegers DxList64 DxNat DxBinrBPF.
From bpf.verifier.dxmodel Require Import Dxopcode Dxstate Dxmonad Dxverifier.

(***************************************)

GenerateIntermediateRepresentation SymbolIRs
  M bindM returnM
  Bool.Exports
  Nat.Exports
  DxIntegers.Exports
  DxList64.Exports
  DxNat.Exports
  DxBinrBPF.Exports
  Dxopcode.Exports
  Dxstate.Exports
  eval_ins_len
  eval_ins
  __
  is_well_dst
  is_well_src
  is_well_jump
  is_not_div_by_zero
  is_shift_range
  get_opcode
  get_offset
  nat2opcode
  bpf_verifier_aux
  bpf_verifier
.

Open Scope string.
Definition dxModuleTest := makeDXModuleWithUserIds
  [ state_struct_def ]
  [ "verifier_state"; "ins_len"; "ins" ] SymbolIRs.
Close Scope string.
