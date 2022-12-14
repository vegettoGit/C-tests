#include <cstring>
#include <execution>
#include <numeric>
#include <string_view>

std::size_t getWordCount(std::string_view words)
{
	if (words.empty())
	{
		return 0;
	}

	return std::transform_reduce(
		std::execution::par_unseq,
		std::begin(words),
		std::end(words) - 1,
		std::begin(words) + 1,
		std::size_t(!std::isspace(words.front()) ? 1 : 0),
		std::plus(),
		[](char left, char right) { return std::isspace(left) && !std::isspace(right); }
	);
}

int main()
{
	std::string_view example1 = "Hello world";
	std::size_t result1 = getWordCount(example1);

	std::string_view example2 = "Here we are";
	std::size_t result2 = getWordCount(example2);

	std::string_view example3 = "Let's find the dragon balls";
	std::size_t result3 = getWordCount(example3);

	return 0;
}