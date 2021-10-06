#ifndef Trust_Database_h
#define Trust_Database_h

#include "sqlite_modern_cpp/hdr/sqlite_modern_cpp.h"

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
        Database();



};


} // namespace

#endif
