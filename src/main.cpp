#include <iostream>
#include <random>
#include <cstdlib>
#include <assert.h>

#include "search.hpp"

// Use the search library hash map implementation
static HashMap map;

static const size_t MAX_ENTRIES = 1024;
static const int MAX_VALUE = 1000000;

int main(int argc, char **argv)
{
    int *vals = new int[MAX_ENTRIES];
    float data;

    int seed = 0xdeadbeef;
    if (argc >= 2)
    {
        char *end = argv[1];
        int argval = std::strtol(argv[1], &end, 10);
        if (*end != '\0')
        {
            std::cerr << "Couldn't parse <" << argv[1] << ">: ignoring"
                      << std::endl;
        }
        else
            seed = argval;
    }

    std::mt19937 generator(0xdeadbeef);
    std::uniform_int_distribution<int> noise(0, MAX_VALUE);

    // Populate the map
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        int val = noise(generator);
        data = static_cast<float>(val);
        map.update(val, data);
        // remember the entries in vals so we can search for them later
        vals[i] = val;
    }

    map.show("Initial map");

    for (int i = 0; i < 1000000; i++)
    {
        /* The main test loop:
         * On each iteration
         * - randomly pick an index from vals
         * - randomly pick search or delete
         *   . if search - check that the val exists
         *   . if delete - delete the val, then replace it
         */
        int op = noise(generator);
        size_t index = noise(generator) % MAX_ENTRIES;
        int val = vals[index];

        if (op & 1)
        {
            auto result = map.get(val);
        }
        else
        {
            map.remove(val);

            val = noise(generator);
            vals[index] = val;
            data = static_cast<float>(val);
            map.update(val, data);
        }
    }

    map.show("Final map");

    // remove all the vals from the map
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        auto removed = map.remove(vals[i]);
        if (!removed.has_value())
        {
            bool duplicate = false;
            for (int j = 0; j < i; j++)
            {
                if (vals[j] == vals[i])
                {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
                std::cout << "remove " << vals[i] << ": not found?" << std::endl;
        }
    }

    map.show("Done");

    delete[] vals;
    return 0;
}
