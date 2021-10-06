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
    db << "PRAGMA FOREIGN_KEYS = OFF;";
    db << "PRAGMA JOURNAL_MODE = WAL;";
    db << "PRAGMA SYNCHRONOUS = 0;";
}

void Database::create_tables()
{
    db << "CREATE TABLE IF NOT EXISTS nodes\
(claim_hash BLOB NOT NULL PRIMARY KEY,\
 amount     INTEGER NOT NULL,\
 trust      REAL NOT NULL)\
WITHOUT ROWID;";

    db << "CREATE TABLE IF NOT EXISTS edges\
(to     BLOB NOT NULL REFERENCES nodes (claim_hash),\
 from   BLOB REFERENCES nodes (claim_hash),\
 amount INTEGER NOT NULL,\
 trust  REAL NOT NULL,\
 PRIMARY KEY (to, from))\
WITHOUT ROWID;";

}


void Database::create_indices()
{

}

} // namespace
