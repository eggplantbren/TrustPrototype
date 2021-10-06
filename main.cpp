#include <iostream>
#include "Database.h"

using namespace Trust;

int main()
{
    Database database;
    database.add_channel("abc", 1000000);
    database.add_channel("def", 1000000);
    database.add_support("abc", "def", 123456);

    return 0;
}
