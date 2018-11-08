#pragma once
namespace cppjni
{
     struct non_copyable {
        non_copyable & operator=(const non_copyable&) = delete;
        non_copyable(const non_copyable&) = delete;
        non_copyable() = default;
    };
}