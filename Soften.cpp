#include "Soften.h"
#include <cmath>

namespace Trust
{

double soften(std::uint64_t amount)
{
    return sqrt(1E-8*amount + 1.0);
}

} // namespace
