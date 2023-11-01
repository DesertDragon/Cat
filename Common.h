#define FIRST_(a, ...) a
#define SECOND_(a, b, ...) b

#define FIRST(...) FIRST_(__VA_ARGS__,)
#define SECOND(...) SECOND_(__VA_ARGS__,)

#define EMPTY()

#define EVAL(...) EVAL32(__VA_ARGS__)
//#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
//#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
//#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
//#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
//#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()

#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b
#define CAT2(a,b) CAT(a,b)

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define COMMA ,

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    COMMA DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#define STRINGIZE(x) #x
#define MAGIC_MACRO(...) EVAL(MAP(STRINGIZE, __VA_ARGS__))

#define ENUM(n, ...) enum n { __VA_ARGS__, n##_count };               \
inline std::ostream& operator<<(std::ostream& out, n val){            \
	static const char* name[] = { MAGIC_MACRO(__VA_ARGS__) };         \
	(unsigned)val < n##_count ? cout << name[val] : cout << (int)val; \
	return out;                                                       \
}

namespace SelfType
{
	template <typename T>
	struct Reader
	{
		friend auto adl_GetSelfType(Reader<T>);
	};

	template <typename T, typename U>
	struct Writer
	{
		friend auto adl_GetSelfType(Reader<T>){return U{};}
	};

	inline void adl_GetSelfType() {}

	template <typename T>
	using Read = std::remove_pointer_t<decltype(adl_GetSelfType(Reader<T>{}))>;
}

#define SELF \
    struct _self_type_tag {}; \
    constexpr auto _self_type_helper() -> decltype(::SelfType::Writer<_self_type_tag, decltype(this)>{}); \
    using Self = ::SelfType::Read<_self_type_tag>;
