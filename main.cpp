#include <iostream>
#include <sstream>
#include "Database.h"

using namespace Trust;

int main()
{
    Database database;

    // Create 10000 channels
    for(int i=0; i<10000; ++i)
    {
        std::stringstream ss;
        ss << "channel" << i;
        database.insert_channel(ss.str(), i+1);
    }

    // Create 1000 supports
    for(int i=0; i<10000; ++i)
    {
        std::stringstream ss, ss2;
        ss << "channel" << i;
        ss2 << "channel" << (10000-i-1);
        database.upsert_edge(ss.str(), ss2.str(), 2*i+1);
    }

    std::cout << "Updating trust scores..." << std::flush;
    database.update_trust();
    std::cout << "done." << std::endl;

    return 0;
}
