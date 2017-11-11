#pragma once

#include "spans.h"

namespace dump {}
template<typename T, typename S>
static void dump_span(const std::string& name, const gsl::span<S>& span, const std::string& indent)
{
	assert(sizeof(S) % sizeof(T) == 0);

	auto components = reinterpret_span<T>(span);
	const size_t groupSize = sizeof(S) / sizeof(T);

	cout << indent << quoted(name) << ": [";

	if (groupSize == 1)
	{
		auto separator = "";

		for (auto i = 0; i<components.size(); ++i)
		{
			cout << separator << components[i];
			separator = ", ";
		}
	}
	else
	{
		auto groupSeparator = "";

		for (auto i = 0; i<components.size(); i += groupSize)
		{
			cout << groupSeparator;

			auto separator = "";
			for (auto j = 0; j<groupSize; ++j)
			{
				cout << separator << components[i+j];
				separator = ",";
			}

			groupSeparator = ",  ";
		}
	}

	cout << "]";
}

void dump_array(const std::string& name, const MStringArray& items, const std::string& indent);
