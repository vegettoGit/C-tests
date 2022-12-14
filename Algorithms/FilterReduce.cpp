#include <execution>
#include <ranges>
#include <vector>

int main()
{
   std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };
   
   auto r = std::views::filter(
      v,
      [](auto e) { return e > 4; }
   );

   auto sumOfElements = std::reduce(
      std::execution::par_unseq,
      begin(r),
      end(r)
   );

   return 0;
}