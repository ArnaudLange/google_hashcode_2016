#pragma once

#include <vector>
#include <array>
#include <ostream>
#include <string>

#include "Photograph.hpp"
#include "TimeRange.hpp"

using CollectionLine = std::array<std::string, 3>;

class Collection{
	private:
		unsigned short m_id;

		unsigned short m_value;
		unsigned short m_number_of_locations;
		unsigned short m_number_of_time_ranges;

		// TODO : optimized with an array  by passing number of photograph to
		// constructor
		std::vector<Photograph*> m_photographs;

		/**
		 * time ranges during which the collection's photographs can be taken
		 */
		std::vector<TimeRange*> m_time_ranges;

		friend std::ostream& operator<<(std::ostream&, const Collection&);

	public:
		Collection(unsigned short);
		Collection(unsigned short id, CollectionLine);
		~Collection();
		Collection(const Collection &collection);
		Collection& operator=(const Collection &collection);

		inline unsigned short getNumberOfPhotographs() {
			return m_number_of_locations;
		}

		inline unsigned short getNumberOfTimeRanges() {
			return m_number_of_time_ranges;
		}

		void add_photograph(Photograph*);
		void add_timeRange(TimeRange*);
};
