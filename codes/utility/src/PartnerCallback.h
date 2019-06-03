#pragma once

namespace utility {

class PartnerCallback {
public:
    virtual ~PartnerCallback() {}

    virtual void OnRecv(const char *data, int len) = 0;
};

class PartnerCallbackEcho : public PartnerCallback {
public:
    void OnRecv(const char *data, int len) override;
};

}