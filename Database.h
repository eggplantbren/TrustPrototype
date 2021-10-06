#ifndef Trust_Database_h
#define Trust_Database_h

#include <cstdint>
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

        void add_channel(const std::string& claim_hash,
                         std::uint64_t amount);

        void add_support(const std::string& from_channel,
                         const std::string& to_channel,
                         std::uint64_t amount);
};


} // namespace

#endif
