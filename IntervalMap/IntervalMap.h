#pragma once

#include <map>
#include <limits>
#include <iostream>

template <typename K, typename V>
class interval_map
{
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val)
    {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val)
    {
        // INSERT YOUR SOLUTION HERE
        if (!(keyBegin < keyEnd))
        {
            // CASE 1: End key is not smaller than the begin key
            std::cout << "CASE 1: End key is not smaller than the begin key\n";
            return;
        }

        // Look for the first existing occurence of the new value in the map
        auto it_notVal = m_map.begin();
        auto it_val = it_notVal;
        while (true)
        {
            it_val = it_notVal;
            while (it_val != m_map.end())
            {
                if (it_val->second == val)
                {
                    break;
                }
                ++it_val;
            }

            if (it_val == m_map.end())
            {
                const auto valEnd = (--m_map.end())->second;
                m_map.insert_or_assign(m_map.end(), keyBegin, val);
                m_map.insert_or_assign(m_map.end(), keyEnd, valEnd);
                // CASE 2: No instance of new value is found in the map
                std::cout << "CASE 2: No instance of new value is found in the map\n";
                return;
            }

            if (keyEnd < it_val->first)
            {
                const auto valEnd = (--it_val)->second;
                m_map.insert_or_assign(it_val, keyBegin, val);
                m_map.insert_or_assign(it_val, keyEnd, valEnd);
                // CASE 3: End key is smaller than the next existing occurence of the new value in the map
                std::cout << "CASE 3: End key is smaller than the next existing occurence of the new value in the map\n";
                return;
            }

            if (keyBegin < it_val->first && !(keyEnd < it_val->first))
            {
                // CASE 4: Consecutive entries have the same value
                std::cout << "CASE 4: Consecutive entries have the same value\n";
                return;
            }

            // Look for the next occurence of an unequal value in the map
            it_notVal = it_val;
            while (it_notVal != m_map.end())
            {
                if (it_notVal->second != val)
                {
                    break;
                }
                ++it_notVal;
            }

            if (it_notVal == m_map.end())
            {
                // CASE 5: All remainder values in the map are equal to new value
                std::cout << "CASE 5: All remainder values in the map are equal to new value\n";
                return;
            }

            if (!(it_notVal->first < keyBegin))
            {
                // CASE 6: Consecutive entries have the same value
                std::cout << "CASE 6: Consecutive entries have the same value\n";
                return;
            }
        }
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const
    {
        return (--m_map.upper_bound(key))->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.
