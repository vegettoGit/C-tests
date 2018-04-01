

#include <type_traits>
#include <tuple>
#include <cassert>

template <class T, class... TArgs> 
decltype(T{ std::declval<TArgs>()... }, std::true_type{}) 
test();

template <class, class...> 
std::false_type 
test(...);

template <class T, class... TArgs>
using isBracesConstructible = decltype(test<T, TArgs...>());

struct anyType 
{
    template<class T>
    constexpr operator T();
};

template<class T>
auto toTuple(T&& object) noexcept 
{
    using type = std::decay_t<T>;
    if constexpr(isBracesConstructible<type, anyType, anyType>{}) 
	{
        auto&&[member1, member2] = object;
        return std::make_tuple(member1, member2);
    }
}

int main()
{
    struct myStruct
	{
        float  myFloat;
        double myDouble;
    };

    auto myTuple = toTuple(myStruct{ 1.0f, 2.0 });
		
    static_assert(std::is_same<std::tuple<float, double>, decltype(myTuple)>{}, "The structToTuple type is not the same as the tuple type");
    assert(std::get<0>(myTuple) == 1.0f && std::get<1>(myTuple) == 2.0);

    return 0;
}

