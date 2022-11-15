add_executable(print_ip_cli main.cpp)

set_target_properties(print_ip_cli PROPERTIES 
    CMAKE_CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

#rename the executable to "ip_filter"
set_target_properties(print_ip_cli PROPERTIES OUTPUT_NAME print_ip)

#BEGIN release
install(TARGETS print_ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END