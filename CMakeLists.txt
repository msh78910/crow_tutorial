cmake_minimum_required(VERSION 3.10.0)
project(crow VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(database)
target_sources(database
PRIVATE
    src/infrastructure/database/database.cpp
PUBLIC
    FILE_SET    HEADERS
    BASE_DIRS   include/crow_platform
    FILES       include/crow_platform/database.hxx
)

add_executable(main src/main.cpp
    # src/api/http/router.cpp
    # include/crow_platform/auth/auth_service.hpp
    # src/models/user.hpp
    # src/models/post.hpp
    # src/infrastructure/database/connection_pool.cpp
    # src/services/auth_service.cpp
    # include/crow_platform/auth/user_repository.hpp
    # src/api/http/handlers/post_handler.cpp
    # src/repositories/user_repository.cpp
    # src/repositories/post_repository.cpp
    )

find_package(Crow CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

target_link_libraries(database PRIVATE libpqxx::pqxx)
target_link_libraries(main PRIVATE Crow::Crow database )



# find_package(boost_asio CONFIG REQUIRED)
# target_link_libraries(main PRIVATE Boost::asio)

# find_package(bsoncxx CONFIG REQUIRED)
# target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

# find_package(mongocxx CONFIG REQUIRED)
# target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

include(CTest)
enable_testing()

