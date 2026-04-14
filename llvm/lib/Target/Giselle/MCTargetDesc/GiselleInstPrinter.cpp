//===----------------------------------------------------------------------===//
//
// This class prints an Giselle MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "GiselleInstPrinter.h"
#include "GiselleMCTargetDesc.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define GET_INSTRUCTION_NAME
#define PRINT_ALIAS_INSTR
#include "GiselleGenAsmWriter.inc"

GiselleInstPrinter::GiselleInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                                       const MCRegisterInfo &MRI)
    : MCInstPrinter(MAI, MII, MRI) {}

void GiselleInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                    StringRef Annot, const MCSubtargetInfo &STI,
                                    raw_ostream &O) {
  if (!PrintAliases || !printAliasInstr(MI, Address, O))
    printInstruction(MI, Address, O);

  printAnnotation(O, Annot);
}

void GiselleInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                       raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    unsigned Reg = Op.getReg();
    printRegName(O, Reg);
  } else if (Op.isImm()) {
    printImm(MI, OpNo, O);
  } else {
    assert(Op.isExpr() && "unknown operand kind in printOperand");
    MAI.printExpr(O, *Op.getExpr());
  }
}

void GiselleInstPrinter::printImm(const MCInst *MI, unsigned OpNo,
                                raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  markup(O, Markup::Immediate) << "#" << formatImm(Op.getImm());
}

void GiselleInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) {
  markup(OS, Markup::Register) << getRegisterName(Reg);
}

const char *GiselleInstPrinter::getRegisterName(MCRegister Reg) {
  return getRegisterName(Reg, Giselle::NoRegAltName);
}
