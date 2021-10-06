#ifndef Trust_Database_h
#define Trust_Database_h

#include <cstdint>
#include <optional>
#include "sqlite_modern_cpp/hdr/sqlite_modern_cpp.h"
#include <string>


namespace Trust
{

class Database
{
    private:
        sqlite::database db;

        void pragmas();
        void create_tables();
        void create_indices();

    public:
        Database(const std::string& path = "data/trust.db");
        Database(const Database& other) = delete;
        Database(Database&& other) = delete;
        Database& operator = (const Database& other) = delete;

        void insert_channel(const std::string& claim_hash,
                            std::uint64_t amount);

        void upsert_edge(const std::string& from_channel,
                         const std::string& to_channel,
                         long long amount);

        void update_trust(const std::string& claim_hash);

        // Update all trust scores once
        void update_trust();
};


} // namespace

#endif
