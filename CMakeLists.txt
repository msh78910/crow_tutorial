cmake_minimum_required(VERSION 3.10.0)
project(crow VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main main.cpp)

find_package(Crow CONFIG REQUIRED)
target_link_libraries(main PRIVATE Crow::Crow)


# find_package(boost_asio CONFIG REQUIRED)
# target_link_libraries(main PRIVATE Boost::asio)

# find_package(libpqxx CONFIG REQUIRED)
# target_link_libraries(main PRIVATE libpqxx::pqxx)

# find_package(bsoncxx CONFIG REQUIRED)
# target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

# find_package(mongocxx CONFIG REQUIRED)
# target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

include(CTest)
enable_testing()

