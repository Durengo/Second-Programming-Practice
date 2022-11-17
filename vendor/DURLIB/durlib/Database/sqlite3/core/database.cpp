#include "database.h"

namespace SQLWRAP
{

  database::database(const std::string &path)
      : FILEPATH(path.c_str()), fpath(path)
  {
    sqlite3_open(FILEPATH, &SQLDB);
    if (SQLDB == nullptr)
    {
      std::cout << "COULD NOT ESTABLISH LINK WITH DATABASE\n";
      delete (this);
    }
    else
    {
      std::cout << "DATABASE LINK ESTABLISHED\n";
      return;
    }
    this->close();
  }

  database::~database()
  {
  }

  void database::open()
  {
    if (sqlite3_open(fpath.c_str(), &SQLDB))
    {
      std::cout << "\nFAILED TO OPEN DATABASE\n";
    }
    else
    {
      return;
    };
  }

  void database::close()
  {
    sqlite3_close(SQLDB);
  }

  int database::rc()
  {
    if (sqlite3_open(fpath.c_str(), &SQLDB))
    {
      std::cout << "\nFAILED TO OPEN DATABASE\n";
      return 1;
    }
    else
    {
      std::cout << "\nDATABASE OPENED SUCCESSFULLY\n";
      return sqlite3_open(fpath.c_str(), &SQLDB);
    };
  }

  void database::clear()
  {
    /*std::string app = "rm ";
    app.append(fpath);
    system(app.c_str());
    system("ls");*/
    remove(fpath.c_str());
  }

  void database::createTable()
  {

    std::string sql;
    char *zErrMsg = nullptr;

    int rc = this->rc();

    /* Create SQL statement */
    sql = "CREATE TABLE COMPANY("
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT,"
          "NAME           TEXT    NOT NULL,"
          "AGE            INT     NOT NULL,"
          "ADDRESS        TEXT	  NOT NULL,"
          "SALARY         REAL );";

    /* Execute SQL statement */
    rc = sqlite3_exec(SQLDB, sql.c_str(), callback, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
    else
    {
      fprintf(stdout, "Table created successfully\n");
    }
    this->close();
  }

  int database::callback(void *NotUsed, int argc, char **argv, char **azColName)
  {

    for (int i = 0; i < argc; i++)
    {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    /*for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " ";
    }*/

    std::cout << std::endl;

    return 0;
  }

  void database::insert(item &item)
  {
    this->open();
    const char *sql = "INSERT INTO COMPANY VALUES (?,?,?,?,?)";

    if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
      printf("\nCould not execute insert func.\n");
      return;
    }
    if (sqlite3_bind_null(stmt, 1) != SQLITE_OK)
    {
      printf("\nCould not bind null.\n");
      return;
    }
    if (sqlite3_bind_text(stmt, 2, item.getName().c_str(), (int)item.getName().length(), SQLITE_STATIC) != SQLITE_OK)
    {
      printf("\nCould not bind text.\n");
      return;
    }
    if (sqlite3_bind_int(stmt, 3, item.getAge()) != SQLITE_OK)
    {
      printf("\nCould not bind int.\n");
      return;
    }
    if (sqlite3_bind_text(stmt, 4, item.getAddress().c_str(), (int)item.getAddress().length(), SQLITE_STATIC) != SQLITE_OK)
    {
      printf("\nCould not bind text.\n");
      return;
    }
    if (sqlite3_bind_int(stmt, 5, (int)item.getSalary()) != SQLITE_OK)
    {
      printf("\nCould not bind int.\n");
      return;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      printf("\nCould not step (execute) stmt.\n");
      return;
    }
    printf("\n");
    // select_stmt("select * from foo");
    this->close();
  }

  void database::display()
  {

    char *zErrMsg = nullptr;
    const char *data = "Callback function called";

    /* Create SQL statement */
    std::string sql = "SELECT * from COMPANY";

    /* Execute SQL statement */
    int rc = sqlite3_exec(SQLDB, sql.c_str(), callback, (void *)data, &zErrMsg);

    if (rc != SQLITE_OK)
    {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
    else
    {
      fprintf(stdout, "Operation done successfully\n");
    }
  }

  item *database::getItem(int ID)
  {
    this->open();
    item *itemtemp = nullptr;
    const char *sql = "SELECT * FROM COMPANY WHERE ID=?";
    int rc = (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr));

    if (sqlite3_bind_int(stmt, 1, ID) != SQLITE_OK)
    {
      printf("\nCould not bind int in ID\n");
      return nullptr;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      auto name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
      int age = sqlite3_column_int(stmt, 2);
      auto address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
      double salary = sqlite3_column_double(stmt, 4);
      itemtemp = new item(name, age, address, salary);
    }
    sqlite3_finalize(stmt);
    this->close();
    return itemtemp;
  }
}