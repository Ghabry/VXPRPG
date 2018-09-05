//
// Created by gabriel on 5/09/18.
//

#ifndef VXPRPG_PLAYER_BINDING_UTIL_H
#define VXPRPG_PLAYER_BINDING_UTIL_H

#include <ruby/ruby.h>
#include <ruby/version.h>

// Ruby 1.8 and Ruby 1.9+ use different version macros
#ifndef RUBY_API_VERSION_MAJOR
#define RUBY_API_VERSION_MAJOR RUBY_VERSION_MAJOR
#endif

#ifndef RUBY_API_VERSION_MINOR
#define RUBY_API_VERSION_MINOR RUBY_VERSION_MINOR
#endif

#if RUBY_API_VERSION_MAJOR == 1
#define PRIsVALUE "s"
#define RB_OBJ_CLASSNAME(obj) rb_obj_classname(obj)
#define RB_OBJ_STRING(obj) StringValueCStr(obj)

NORETURN(void rb_error_arity(int, int, int));

#define OBJ_INIT_COPY(obj, orig) \
	((obj) != (orig) && (rb_obj_init_copy((obj), (orig)), 1))
#if RUBY_API_VERSION_MINOR == 8
// Makes version checks easier
#define RUBY_LEGACY_VERSION
// Functions and macros providing Ruby 1.8 compatibililty
#define FLONUM_P(x) 0

#define RB_FLOAT_TYPE_P(obj) (FLONUM_P(obj) || (!SPECIAL_CONST_P(obj) && BUILTIN_TYPE(obj) == T_FLOAT))

#define RB_TYPE_P(obj, type) ( \
	((type) == T_FIXNUM) ? FIXNUM_P(obj) : \
	((type) == T_TRUE) ? ((obj) == Qtrue) : \
	((type) == T_FALSE) ? ((obj) == Qfalse) : \
	((type) == T_NIL) ? ((obj) == Qnil) : \
	((type) == T_UNDEF) ? ((obj) == Qundef) : \
	((type) == T_SYMBOL) ? SYMBOL_P(obj) : \
	((type) == T_FLOAT) ? RB_FLOAT_TYPE_P(obj) : \
	(!SPECIAL_CONST_P(obj) && BUILTIN_TYPE(obj) == (type)))

#define RUBY_T_ARRAY T_ARRAY
#define RUBY_T_STRING T_STRING
#define RUBY_T_FLOAT T_FLOAT
#define RUBY_T_FIXNUM T_FIXNUM
#define RUBY_T_TRUE T_TRUE
#define RUBY_T_FALSE T_FALSE
#define RUBY_T_NIL T_NIL

#define rb_str_new_cstr rb_str_new2

#endif
#endif

#define ARRAY_SIZE(obj) (sizeof(obj) / sizeof((obj)[0]))

struct evalArg
{
	VALUE string;
	VALUE filename;
};

static VALUE evalHelper(evalArg *arg)
{
	VALUE argv[] = { arg->string, Qnil, arg->filename };
	return rb_funcall2(Qnil, rb_intern("eval"), ARRAY_SIZE(argv), argv);
}

static VALUE evalString(VALUE string, VALUE filename, int *state)
{
	evalArg arg = { string, filename };
	return rb_protect((VALUE (*)(VALUE))evalHelper, (VALUE)&arg, state);
}

#endif //VXPRPG_PLAYER_BINDING_UTIL_H
