#pragma once

#include "sqlite3.h"
#include "durlib/Database/sqlite3/item/item.h"
#include <iostream>
#include <vector>

namespace SQLWRAP
{
  class database
  {
  private:
    sqlite3 *SQLDB;
    sqlite3_stmt *stmt;

    const char *FILEPATH;
    std::string fpath;

    // std::vector<int> rows;
    // std::vector<int> columns;
    int rows = 0;
    int columns = 0;

  public:
    database(const std::string &path);
    ~database();
    void open();
    void close();
    int rc();
    void clear();
    void createTable();
    void insert(item &item);
    static int callback(void *context, int columnCount, char **columnValues, char **columnName);
    void display();

    // void countRows();
    // void countColumns();
    item *getItem(int ID);
  };
}