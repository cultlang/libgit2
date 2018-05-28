
#include "curses/common.h"

#include "all.h"

using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::curses;


#define lMM sem->builtin_implementMultiMethod
#define MoD "curses"

instance<Module> cultlang::curses::make_bindings(instance<lisp::Namespace> ns, instance<> loader)
{
  auto ret = instance<Module>::make(ns, loader);
  auto sem = instance<CultSemantics>::make(ret);
  ret->builtin_setSemantics(sem);

  lMM(MoD, []() { return instance<bool>::make();});
  
  return ret;
}

BuiltinModuleDescription cultlang::curses::BuiltinCurses("cultlang/curses", cultlang::curses::make_bindings);


#include "types/dll_entry.inc"
