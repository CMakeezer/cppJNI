find_package(Java 1.6 REQUIRED)

SET(CMAKE_FIND_LIBRARY_SUFFIXES_COPY ${CMAKE_FIND_LIBRARY_SUFFIXES})
if(WIN32)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".lib")
endif()
find_package(JNI REQUIRED)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_COPY})

find_package(hana REQUIRED)
include(UseJava)

set(SOURCES
    jni_wrappers/call_object_method.cpp
    jni_wrappers/call_static_method.cpp
    jni_wrappers/environment.cpp
    jni_wrappers/exception_check.cpp
    jni_wrappers/find_class.cpp
    jni_wrappers/method_id_cache.cpp
    types/string.cpp
    virtual_machine.cpp
)
set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(HEADERS_DIR_CPPJNI ${HEADERS_DIR}/cppjni)
set(HEADERS
    ${HEADERS_DIR_CPPJNI}/concepts/is_java_class_definition.hpp
    ${HEADERS_DIR_CPPJNI}/concepts/is_jni_reference_type.hpp
    ${HEADERS_DIR_CPPJNI}/concepts/is_jni_reference_wrapper_type.hpp
    ${HEADERS_DIR_CPPJNI}/concepts/static_list.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/call_constructor.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/call_object_method.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/call_static_method.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/class_loader.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/current_environment.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/environment.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/exception_check.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/find_class.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/generate_jni_signature_string.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/global_reference.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/global_reference.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/local_reference.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/local_reference.hpp
    ${HEADERS_DIR_CPPJNI}/jni_wrappers/method_id_cache.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/generate_overloaded_constructor_declarations.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/generate_overloaded_method_declarations.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/jni_constructor_signature_hack.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/method_declaration.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/method_scope_category.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/scoped_declaration.hpp
    ${HEADERS_DIR_CPPJNI}/meta_declaration/signature_info.hpp
    ${HEADERS_DIR_CPPJNI}/method_call/method_caller.hpp
    ${HEADERS_DIR_CPPJNI}/mpl/list.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/class.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/class.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/comparable.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/object.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/string.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/lang/throwable.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/util/iterator.hpp
    ${HEADERS_DIR_CPPJNI}/predefined/java/util/list.hpp
    ${HEADERS_DIR_CPPJNI}/types/base_object_container.hpp
    ${HEADERS_DIR_CPPJNI}/types/class.hpp
    ${HEADERS_DIR_CPPJNI}/types/object.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/types/object.hpp
    ${HEADERS_DIR_CPPJNI}/types/object_converter.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/types/object_converter.hpp
    ${HEADERS_DIR_CPPJNI}/types/primitives.hpp
    ${HEADERS_DIR_CPPJNI}/types/string.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/types/string.hpp
    ${HEADERS_DIR_CPPJNI}/java_cast.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/java_cast.hpp
    ${HEADERS_DIR_CPPJNI}/jni_exception.hpp
    ${HEADERS_DIR_CPPJNI}/jni_thread_hint.hpp
    ${HEADERS_DIR_CPPJNI}/jni_version.hpp
    ${HEADERS_DIR_CPPJNI}/method_signature.hpp
    ${HEADERS_DIR_CPPJNI}/native_cast.fwd.hpp
    ${HEADERS_DIR_CPPJNI}/native_cast.hpp
    ${HEADERS_DIR_CPPJNI}/virtual_machine.hpp
    ${HEADERS_DIR_CPPJNI}/virtual_machine.fwd.hpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${HEADERS_DIR}>
    PUBLIC
        ${JNI_INCLUDE_DIRS}
)

message(INFO "JNI_LIBRARIES=${JNI_LIBRARIES}")
message(INFO "JAVA_JVM_LIBRARY=${JAVA_JVM_LIBRARY}")
message(INFO "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")

target_link_libraries(${PROJECT_NAME}
    ${JAVA_JVM_LIBRARY}
    hana
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-cmake
        ARCHIVE DESTINATION lib/
        LIBRARY DESTINATION lib/
        RUNTIME DESTINATION bin/
        INCLUDES DESTINATION include/${PROJECT_NAME})

install(
        DIRECTORY "${PROJECT_SOURCE_DIR}/include/cppjni/"
        DESTINATION include/cppjni
        FILES_MATCHING PATTERN "*.*hpp")

install(
        EXPORT ${PROJECT_NAME}-cmake
        FILE ${PROJECT_NAME}-config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION share/${PROJECT_NAME}/cmake)