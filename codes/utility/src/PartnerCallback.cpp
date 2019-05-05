#include "PartnerCallback.h"
#include <cstdio>

namespace utility {

void PartnerCallbackEcho::OnRecv(const char *data, int len)
{
    printf("%s", data);
}

}