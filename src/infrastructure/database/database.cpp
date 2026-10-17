#include "database.hxx"
#include <pqxx/pqxx>
#include <iostream>


/**
 * Static methods should be defined outside the class.
 */

Database *Database::pinstance_{nullptr};
std::mutex Database::mutex_;

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value. RU:
 */
Database *Database::GetInstance(const std::string &connection_str)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Database(connection_str);
    }
    return pinstance_;
}


std::string Database::AddUser() {
    try
    {
        // In libpqxx, you always work in transaction. Start it like:
        pqxx::work tx(cx_);

        std::string first_name = "hassan";
        std::string last_name = "ostad";
        std::string birthday = "1992-07-18";
        std::string username = "hassan";
        std::string bio = "very good";
        std::string url = "some/where";
        std::string email = "hassan@gmail.com";
        std::string pwd_hash = "78910";

        // pqxx::row r = tx.exec("SELECT * from "); //.one_row();
        pqxx::result r = tx.exec("INSERT INTO public.person(first_name, last_name, birth_date, bio, photo_url)"
                "VALUES ($1, $2, $3, $4, $5)"
                "RETURNING id", pqxx::params{first_name, last_name, birthday, bio, url});
        std::string uuid = r[0][0].as<std::string>();
        
        tx.exec("INSERT INTO public.account(person_id, username, email, password_hash)"
                "VALUES ($1, $2, $3, $4)", pqxx::params{uuid, username, email, pwd_hash});
    
        // Commit your transaction.  If an exception occurred before this point, execution will have left the block, and the
        // transaction will have been destroyed along the way.  
        // In that case, the failed transaction would implicitly abort instead of getting to this point.
        tx.commit();
    
        // "r[0]" returns the first field, which has an "as<...>()" member
        // function template to convert its contents from string to a type you say
        std::cout << "USER ADDED! " /* r[0].as<int>() */ << std::endl;
        return "OK";
  }
  catch (std::exception const &e)
  {
    std::cerr << e.what() << std::endl;
    return "damn";
  }
}