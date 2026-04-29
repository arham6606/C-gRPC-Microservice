#pragma once
#include <pqxx/pqxx>
#include <string>
#include <stdexcept>
using namespace std;

class Database
{
public:
    pqxx::connection conn;
    Database(const string &conn_str) : conn(conn_str) {}

    int32_t createUser(const string &name, const string &email)
    {
        pqxx::work txn(conn);
        pqxx::result r = txn.exec_params("INSERT INTO users (name, email) VALUES ($1, $2) RETURNING id", name, email);
        txn.commit();
        return r[0][0].as<int32_t>();
    }

    tuple<int32_t, string, string> getUser(int32_t id)
    {
        pqxx::work txn(conn);
        pqxx::result r = txn.exec_params("SELECT id, name,email FROM users WHERE id = $1", id);
        txn.commit();
        if (r.empty())
        {
            throw runtime_error("User not found");
        }
        return {r[0][0].as<int32_t>(), r[0][1].as<string>(), r[0][2].as<string>()};
    }

    bool emailExists(const string &email)
    {
        pqxx::work txn(conn);
        pqxx::result r = txn.exec_params("SELECT 1 FROM  users WHERE email = $1", email);
        txn.commit();
        return !r.empty();
    }
};
