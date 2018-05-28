
#include "git/common.h"

#include "all.h"

CRAFT_TYPE_DEFINE(git_attr_t)
{
	_.add<GraphPropertyName>("got/attr");
	_.add<GraphPropertyCppName>("::git_attr_t");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_attr_t> _this) { 
		switch (*_this)
		{
		case GIT_ATTR_UNSPECIFIED_T: return "Unspecified";
		case GIT_ATTR_TRUE_T: return "True";
		case GIT_ATTR_FALSE_T: return "False";
		case GIT_ATTR_VALUE_T: return "Value";
		default:
			return "Unknown";
		}
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_attr_t> _this) { 
		switch (*_this)
		{
		case GIT_ATTR_UNSPECIFIED_T: return "GIT_ATTR_UNSPECIFIED_T";
		case GIT_ATTR_TRUE_T: return "GIT_ATTR_TRUE_T";
		case GIT_ATTR_FALSE_T: return "GIT_ATTR_FALSE_T";
		case GIT_ATTR_VALUE_T: return "GIT_ATTR_VALUE_T";
		default:
			return "GIT_ATTR_UNSPECIFIED_T";
		}
	});
	_.use<PConstructor>().singleton<DefaultConstructor>();
}

using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::git;


#define lMM sem->builtin_implementMultiMethod
#define MoD "git"

instance<Module> cultlang::git::make_bindings(instance<lisp::Namespace> ns, instance<> loader)
{
  auto ret = instance<Module>::make(ns, loader);
  auto sem = instance<CultSemantics>::make(ret);
  ret->builtin_setSemantics(sem);

  lMM(MoD, []() { 
	  return instance<bool>::make();
  });
  
  return ret;
}

BuiltinModuleDescription cultlang::git::BuiltinGit("cultlang/git", cultlang::git::make_bindings);


#include "types/dll_entry.inc"
