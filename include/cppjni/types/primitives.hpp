#pragma once
#include <cstdint>

#include <boost/hana/core/when.hpp>

#include <jni.h>

#include <cppjni/concepts/string_type.hpp>

#include "object.fwd.hpp"

namespace cppjni
{
namespace types
{
    namespace detail
    {
        template<typename native_template_t, typename jni_template_t, typename jni_signature_letter_template_t>
        struct PrimitiveConverter
        {
            using native_t = native_template_t;
            using jni_t = jni_template_t;
            using jni_type_string_t = jni_signature_letter_template_t;
            
            template<typename T>
            using isConvertible = std::is_convertible<T, native_t>;
            
            constexpr native_t convertFromJni(const jni_t& value) const
            {
                return value;
            }
            
            constexpr jni_t convertToJni(const native_t& value) const
            {
                return value;
            }
        };
    }
    
    struct Void
    {
        using native_t = void;
        using jni_t = void;
        using jni_type_string_t = string_type_is("V");
        
        template<typename T>
        struct isConvertible
        {
            static_assert(sizeof(T) != 0, "Void cannot be a function argument!");
        };
    };
    
    using Boolean = detail::PrimitiveConverter<bool, jboolean, string_type_is("Z")>;
    using Byte = detail::PrimitiveConverter<std::int8_t, jchar, string_type_is("B")>;
    using Char = detail::PrimitiveConverter<std::uint16_t, jchar, string_type_is("C")>;
    using Short = detail::PrimitiveConverter<std::int16_t, jshort, string_type_is("S")>;
    using Int = detail::PrimitiveConverter<std::int32_t, jint, string_type_is("I")>;
    using Long = detail::PrimitiveConverter<std::int64_t, jlong, string_type_is("J")>;
    using Float = detail::PrimitiveConverter<float, jfloat, string_type_is("F")>;
    using Double = detail::PrimitiveConverter<double, jdouble, string_type_is("D")>;
}
}