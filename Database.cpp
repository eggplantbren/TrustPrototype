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
    db << "PRAGMA FOREIGN_KEYS = ON;"; // TODO: Off in production
    db << "PRAGMA JOURNAL_MODE = WAL;";
    db << "PRAGMA SYNCHRONOUS = 0;";
}

void Database::create_tables()
{
    db << "CREATE TABLE IF NOT EXISTS channels\
(claim_hash BLOB NOT NULL PRIMARY KEY,\
 trust      REAL NOT NULL)\
WITHOUT ROWID;";

    db << "INSERT OR IGNORE INTO channels VALUES ('', 1.0);";

    db << "CREATE TABLE IF NOT EXISTS edges\
(to_channel   BLOB NOT NULL REFERENCES channels (claim_hash),\
 from_channel BLOB NOT NULL REFERENCES channels (claim_hash),\
 amount       INTEGER NOT NULL,\
 source_trust REAL NOT NULL,\
 PRIMARY KEY (to_channel, from_channel))\
WITHOUT ROWID;";
}


void Database::create_indices()
{
    db << "CREATE INDEX IF NOT EXISTS idx1 ON edges (from_channel);";
}

void Database::insert_channel(const std::string& claim_hash,
                              std::uint64_t amount)
{
    // Insert the channel
    db << "INSERT OR REPLACE INTO channels VALUES (?, ?);"
       << claim_hash << 1.0;

    // Insert the edge with null origin
    db << "INSERT OR REPLACE INTO edges VALUES (?, ?, ?, ?);"
       << claim_hash << "" << amount << 1.0;
}

void Database::upsert_edge(const std::string& to_channel,
                           const std::string& from_channel,
                           long long delta_amount)
{
    double source_trust = 1.0;
    db << "SELECT trust FROM channels WHERE claim_hash = ?;"
       << from_channel >> [&](double _trust) { source_trust = _trust; };

    db << "INSERT INTO edges VALUES (?, ?, ?, ?)\
            ON CONFLICT (to_channel, from_channel)\
            DO UPDATE SET amount       = amount + excluded.amount,\
                          source_trust = excluded.source_trust;"
       << to_channel << from_channel << delta_amount << source_trust;
}

void Database::update_trust(const std::string& claim_hash)
{
    double tot;
    db << "SELECT SUM(amount*source_trust) FROM edges WHERE to_channel = ?;"
       << claim_hash >> tot;

    double trust = soften(tot);

    db << "UPDATE channels SET trust = ? WHERE claim_hash = ?;"
       << trust << claim_hash;
    db << "UPDATE edges SET source_trust = ? WHERE from_channel = ?;"
       << trust << claim_hash;
}

void Database::update_trust()
{
    db << "BEGIN;";

    std::vector<std::string> channels;
    db << "SELECT claim_hash FROM channels;" >>
        [&](const std::string& ch) { channels.push_back(ch); };

    for(const auto& c: channels)
        update_trust(c);

    db << "COMMIT;";
}


} // namespace
