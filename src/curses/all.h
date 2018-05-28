
#pragma once
#include "curses/common.h"

namespace cultlang {
namespace curses 
{
  extern craft::lisp::BuiltinModuleDescription BuiltinCurses;

  CULTLANG_CURSES_EXPORTED craft::instance<craft::lisp::Module> make_bindings(craft::instance<craft::lisp::Namespace> ns, craft::instance<> loader);
}}  
