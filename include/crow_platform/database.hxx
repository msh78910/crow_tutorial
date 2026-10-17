#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

class Database
{

private:
    static Database *pinstance_;
    static std::mutex mutex_;
    pqxx::connection cx_;
    
    protected:
    explicit Database(const std::string connection_str) : connection_str_(connection_str), cx_(connection_str)
    {
    }
    ~Database() {}
    std::string connection_str_;
    
public:
    /**
     * Singletons should not be cloneable or assignable
     */
    Database(Database &other) = delete;
    void operator=(const Database &) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the same obj
     */

    static Database *GetInstance(const std::string &connection_str);
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */
    std::string AddUser();

    std::string connection_str() const
    {
        return connection_str_;
    }
};