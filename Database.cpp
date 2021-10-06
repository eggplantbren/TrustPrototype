#include "Database.h"
#include "Soften.h"

namespace Trust
{

Database::Database(const std::string& path)
:db(path.c_str())
{
    pragmas();
    create_tables();
    create_indices();
}

void Database::pragmas()
{
    db << "PRAGMA FOREIGN_KEYS = OFF;";
    db << "PRAGMA JOURNAL_MODE = WAL;";
    db << "PRAGMA SYNCHRONOUS = 0;";
}

void Database::create_tables()
{
    db << "CREATE TABLE IF NOT EXISTS edges\
(to_channel   BLOB NOT NULL,\
 from_channel BLOB NOT NULL,\
 amount       INTEGER NOT NULL,\
 PRIMARY KEY (to_channel, from_channel))\
WITHOUT ROWID;";
}


void Database::create_indices()
{

}

void Database::add_channel(const std::string& claim_hash,
                           std::uint64_t amount)
{
    // Insert the edge with null origin
    db << "INSERT INTO edges VALUES (?, ?, ?);"
       << claim_hash << "" << amount;
}

void Database::add_support(const std::string& from_channel,
                           const std::string& to_channel,
                           std::uint64_t amount)
{
    // Inssert the edge with null origin
    db << "INSERT INTO edges VALUES (?, ?, ?);"
       << from_channel << to_channel << amount;
}

} // namespace
