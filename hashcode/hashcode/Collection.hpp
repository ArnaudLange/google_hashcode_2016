#pragma once

#include <vector>
#include <array>
#include <ostream>
#include "Photograph.hpp"
#include "TimeRange.hpp"
#include <string>

using CollectionLine = std::array<std::string, 3>;

// necessary because of mutual inclusion
class Photograph;

class Collection{
	private:
		unsigned short m_value;
		unsigned short m_number_of_locations;
		unsigned short m_number_of_time_ranges;

		// TODO : optimized with an array  by passing number of photograph to
		// constructor
		std::vector<Photograph*> m_photographs;

		/**
		 * time ranges during which the collection's photographs can be taken
		 */
		const std::vector<TimeRange*> m_time_ranges;

		friend std::ostream& operator<<(std::ostream&, const Collection&);

	public:
		Collection(unsigned short);
		Collection(CollectionLine);
		~Collection();
		Collection(const Collection &collection);
		Collection& operator=(const Collection &collection);

		void add_photograph(Photograph*);
};
