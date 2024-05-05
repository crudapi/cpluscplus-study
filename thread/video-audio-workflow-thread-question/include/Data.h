#pragma once
#include "memory_leak_checker.hpp"
#include <memory>

struct Data
{
public:
    Data() { }
    Data( long long v) {  id = v; }
    virtual ~Data() { }
public:
    long long id;
    void* data = nullptr;
    counter_by_copy<Data> m_checker;
};

using T = std::shared_ptr<Data>;