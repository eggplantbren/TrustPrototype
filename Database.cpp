#include "Database.h"

namespace Trust
{

Database::Database()
:db("data/trust.db")
{
    pragmas();
    create_tables();
    create_indices();
}

void Database::pragmas()
{
    
}


} // namespace
