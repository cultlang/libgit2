
#include "git/common.h"

#include "all.h"

namespace _impl {
	struct walk_context{
		craft::instance<craft::lisp::PSubroutine> walk;
	};
}
CRAFT_TYPE_DEFINE(git_attr_t)
{
	_.add<GraphPropertyName>("git/attr");
	_.add<GraphPropertyCppName>("::git_attr_t");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_attr_t> _this) { 
		return "Attribute";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_attr_t> _this) { 
		return "Attribute";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_repository)
{
	_.add<GraphPropertyName>("git/repository");
	_.add<GraphPropertyCppName>("::git_repository");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_repository> _this) {
		return "Repository";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_repository> _this) {
		return "Repository";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_oid)
{
	_.add<GraphPropertyName>("git/oid");
	_.add<GraphPropertyCppName>("::git_oid");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_oid> _this) {
		auto res = std::string(GIT_OID_HEXSZ + 1, '0');
		git_oid_tostr(res.data(), GIT_OID_HEXSZ + 1, _this.get());
		return res;

	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_oid> _this) {
		auto res = std::string(GIT_OID_HEXSZ + 1, '0');
		git_oid_tostr(res.data(), GIT_OID_HEXSZ + 1, _this.get());
		return res;
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_commit)
{
	_.add<GraphPropertyName>("git/commit");
	_.add<GraphPropertyCppName>("::git_commit");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_commit> _this) {
		return "Commit";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_commit> _this) {
		return "Commit";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_tree)
{
	_.add<GraphPropertyName>("git/tree");
	_.add<GraphPropertyCppName>("::git_tree");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_tree> _this) {
		return "Tree";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_tree> _this) {
		return "Tree";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_tree_entry)
{
	_.add<GraphPropertyName>("git/tree-entry");
	_.add<GraphPropertyCppName>("::git_tree_entry");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_tree_entry> _this) {
		return "Tree Entry";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_tree_entry> _this) {
		return "Tree Entry";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}


CRAFT_TYPE_DEFINE(git_blob)
{
	_.add<GraphPropertyName>("git/blob");
	_.add<GraphPropertyCppName>("::git_blob");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_blob> _this) {
		return "Blob";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_blob> _this) {
		return "Blob";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_tag)
{
	_.add<GraphPropertyName>("git/tag");
	_.add<GraphPropertyCppName>("::git_tag");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_tag> _this) {
		return "Tag";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_tag> _this) {
		return "Tag";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}

CRAFT_TYPE_DEFINE(git_signature)
{
	_.add<GraphPropertyName>("git/signature");
	_.add<GraphPropertyCppName>("::git_signature");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<git_signature> _this) {
		return "Signature";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<git_signature> _this) {
		return "Signature";
	});
	//_.use<PConstructor>().singleton<DefaultConstructor>();
}
using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::git;


#define lMM sem->builtin_implementMultiMethod
#define MoD "git"



instance<Module> cultlang::git::make_bindings(instance<lisp::Namespace> ns, instance<> loader)
{
	git_libgit2_init();

	auto ret = instance<Module>::make(ns, loader);
	auto sem = instance<CultSemantics>::make(ret);
	ret->builtin_setSemantics(sem);

	sem->builtin_defineType<git_repository>("git/Repository");
	sem->builtin_defineType<git_commit>("git/Commit");
	sem->builtin_defineType<git_tag>("git/Tag");
	sem->builtin_defineType<git_tree>("git/Tree");
	sem->builtin_defineType<git_blob>("git/Blob");
	sem->builtin_defineType<git_oid>("git/Oid");

	lMM(MoD"/open", [](instance<std::string> s) {
		git_repository *repo = NULL;
		auto err = git_repository_open_ext(&repo, s->c_str(), 0, NULL);
		if (!err) {
			return instance<git_repository>::makeFromPointerAndMemoryManager(repo, repo);
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/close", [](instance<git_repository> s) { git_repository_free(s.get());});

	lMM(MoD"/oid", [](instance<std::string> s) {
		auto res = instance<git_oid>::make();
		git_oid_fromstr(res.get(), s->c_str());
		return res;
	});
	lMM(MoD"/sha", [](instance<git_oid> s) {
		auto res = instance<std::string>::make(GIT_OID_HEXSZ + 1, '0');
		git_oid_tostr(res->data(), GIT_OID_HEXSZ + 1, s.get());
	});
	
	lMM(MoD"/commit", [](instance<git_repository> r, instance<git_oid> s) {
		git_commit *commit = NULL;
		auto err = git_commit_lookup(&commit, r.get(), s.get());
		if (!err) {
			return instance<git_commit>::makeFromPointerAndMemoryManager(commit, commit);
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/commit/parents", [](instance<git_commit> r) {
		unsigned int count = git_commit_parentcount(r.get());
		auto res = instance<library::List>::make();

		for (unsigned int i = 0; i < count; i++) {
			const git_oid *nth_parent_id = git_commit_parent_id(r.get(), i);

			res->push(instance<git_oid>::makeFromPointerAndMemoryManager(
				const_cast<git_oid *>(nth_parent_id),
				const_cast<git_oid *>(nth_parent_id)
			));
		}
		return res;
	});

	lMM(MoD"/commit/id", [](instance<git_commit> c) {
		auto res = git_commit_id(c.get());

		return instance<git_oid>::makeFromPointerAndMemoryManager(
			const_cast<git_oid*>(res), 
			const_cast<git_oid*>(res));
	});

	lMM(MoD"/commit/encoding", [](instance<git_commit> c) {
		auto res = git_commit_message_encoding(c.get());
		return instance<std::string>::make(res);
	});

	lMM(MoD"/commit/encoding", [](instance<git_commit> c) {
		auto res = git_commit_message(c.get());
		return instance<std::string>::make(res);
	});

	lMM(MoD"/commit/summary", [](instance<git_commit> c) {
		auto res = git_commit_summary(c.get());
		return instance<std::string>::make(res);
	});

	lMM(MoD"/commit/time", [](instance<git_commit> c) {
		auto res = git_commit_time(c.get());
		return instance<int64_t>::make(res);
	});

	lMM(MoD"/commit/timeoffset", [](instance<git_commit> c) {
		auto res = git_commit_time_offset(c.get());
		return instance<int32_t>::make(res);
	});

	lMM(MoD"/commit/committer", [](instance<git_commit> c) {
		auto res = git_commit_committer(c.get());
		return instance<git_signature>::makeFromPointerAndMemoryManager(
			const_cast<git_signature*>(res),
			const_cast<git_signature*>(res));
	});

	lMM(MoD"/commit/author", [](instance<git_commit> c) {
		auto res = git_commit_author(c.get());
		return instance<git_signature>::makeFromPointerAndMemoryManager(
			const_cast<git_signature*>(res),
			const_cast<git_signature*>(res));
	});

	lMM(MoD"/commit/raw-header", [](instance<git_commit> c) {
		auto res = git_commit_raw_header(c.get());
		return instance<std::string>::make(res);
	});

	lMM(MoD"/commit/tree-id", [](instance<git_commit> c) {
		auto res = git_commit_tree_id(c.get());

		return instance<git_oid>::makeFromPointerAndMemoryManager(
			const_cast<git_oid*>(res),
			const_cast<git_oid*>(res));
	});

	lMM(MoD"/tree", [](instance<git_repository> r, instance<git_oid> s) {
		git_tree *tree = NULL;
		auto err = git_tree_lookup(&tree, r.get(), s.get());
		if (!err) {
			return instance<git_tree>::makeFromPointerAndMemoryManager(tree, tree);
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/blob", [](instance<git_repository> r, instance<git_oid> s) {
		git_blob *blob = NULL;
		auto err = git_blob_lookup(&blob, r.get(), s.get());
		if (!err) {
			return instance<git_blob>::makeFromPointerAndMemoryManager(blob, blob);
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/tag", [](instance<git_repository> r, instance<git_oid> s) {
		git_tag *tag = NULL;
		auto err = git_tag_lookup(&tag, r.get(), s.get());
		if (!err) {
			return instance<git_tag>::makeFromPointerAndMemoryManager(tag, tag);
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/revparse-single", [](instance<git_repository> r, instance<types::Graph::Node> t, instance<std::string> s) {
		git_object *res;

		auto err = git_revparse_single(&res, r.get(), s->c_str());
		if (!err) {
			TypeId id = t.get();
			if (id == instance<git_commit>().typeId())
				return (instance<>)instance<git_commit>::makeFromPointerAndMemoryManager((git_commit*)res, res);
			else if (id == instance<git_tag>().typeId())
				return (instance<>)instance<git_tag>::makeFromPointerAndMemoryManager((git_tag*)res, res);
			else if (id == instance<git_tree>().typeId())
				return (instance<>)instance<git_tree>::makeFromPointerAndMemoryManager((git_tree*)res, res);
			else if (id == instance<git_blob>().typeId())
				return (instance<>)instance<git_blob>::makeFromPointerAndMemoryManager((git_blob*)res, res);
			else
			{
				git_object_free(res);
				throw stdext::exception("Cannot Dynamic Dispatch to Type: {0}", t.toString());
			}
		}
		const git_error *e = giterr_last();
		throw stdext::exception("{0} {1}", e->klass, e->message);
	});

	lMM(MoD"/tree/walk", [](instance<git_repository> r, instance<git_tree> s, instance<PSubroutine> cb) {
		
		_impl::walk_context w;
		w.walk = cb;
		git_tree_walk(s.get(), GIT_TREEWALK_PRE, [](const char *root,
			const git_tree_entry *entry,
			void *payload)
		{
			instance<PSubroutine> p = *(instance<PSubroutine>*)payload;
			auto arg = instance<git_tree_entry>::makeFromPointerAndMemoryManager(
				const_cast<git_tree_entry*>(entry),
				const_cast<git_tree_entry*>(entry));
			p->execute(p, { arg });

			return 0;
		}, &cb);
	});

	return ret;
}

BuiltinModuleDescription cultlang::git::BuiltinGit("cultlang/git", cultlang::git::make_bindings);


#include "types/dll_entry.inc"
