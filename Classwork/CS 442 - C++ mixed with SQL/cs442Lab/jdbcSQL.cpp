/*******************************************************************************
 * Name        : jdbcSQL.cpp
 * Author      : Ben Rose
 * Date        : November 9, 2019
 * Description : CS 442 SQL Programming Lab: Writing JDBC Applications with MySQL
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Version	   : 1.0
 ******************************************************************************/

#include <iostream> // Include input/output capabilities
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <mysqlx/xapi.h> // Include C mySQL commands
#include <mysql/jdbc.h>

/* Error processing macros */
#define CRUD_CHECK(C, S) if (!C) \
  { \
    printf("\nError! %s", mysqlx_error_message(S)); \
    return -1; \
  }
#define RESULT_CHECK(R, C) if (!R) \
  { \
    printf("\nError! %s", mysqlx_error_message(C)); \
    return -1; \
  }
#define IS_OK(R, C)  if (R != RESULT_OK) \
  { \
    printf("\nError! %s", mysqlx_error_message(C)); \
    return -1; \
  }

using namespace std;

// Database credentials
const char* USER = "root"; // The database username
const char* PASS = "password"; // The database password, also changeable

int main(int argc, char * const argv[]) {
	mysqlx_session_t *conn = NULL; // Connection
	mysqlx_stmt_t *stmt = NULL; // Statement

	mysqlx_result_t   *res;
	mysqlx_row_t      *row;
	mysqlx_error_t *error;
	// Open a connection to database
	const char *DB_URL = (argc > 1 ? argv[1] : "mysqlx://root:password@127.0.0.1");
	conn = mysqlx_get_session_from_url(DB_URL, &error);
	cout << "Connecting to database..." << endl;
	if (!conn)
	{
		printf("\nError! %s. Error Code: %d", mysqlx_error_message(error),
			   mysqlx_error_num(error));
		mysqlx_free(error);
		return -1;
	}
	if (mysqlx_session_valid(conn)) {
		cout << "Connection established. Connection number: " << conn << endl;
	}

	string sql = "DROP DATABASE IF EXISTS VehicleOffice";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);
	// Use SQL to Create Database
	cout << "Creating database..." << endl;
	sql = "CREATE DATABASE VehicleOffice";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);
	cout << "Database created successfully." << endl;

	// Use SQL to select the database
	sql = "use VehicleOffice";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Use SQL to create Tables
	// Create Table Branch
	sql = "create table branch(branch_id integer not null,\
		branch_name varchar(20) not null,\
		branch_addr varchar(50),\
		branch_city varchar(20) not null,\
		branch_phone integer,\
		PRIMARY KEY(branch_id))";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Create Table Driver
	sql = "create table driver(driver_ssn integer not null,\
		driver_name varchar(20) not null,\
		driver_addr varchar(50) not null,\
		driver_city varchar(20) not null,\
		driver_birthdate date not null,\
		driver_phone integer,\
		PRIMARY KEY (driver_ssn))";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Create Table License
	sql = "create table license(license_no integer not null,\
		driver_ssn integer not null,\
		license_type char not null,\
		license_class integer not null,\
		license_expiry date not null,\
		issue_date date not null,\
		branch_id integer not null,\
		PRIMARY KEY (license_no),\
		FOREIGN KEY (driver_ssn) REFERENCES driver(driver_ssn),\
		FOREIGN KEY (branch_id) REFERENCES branch(branch_id))";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Create Table Exam
	sql = "create table exam(driver_ssn integer not null,\
		branch_id integer not null,\
		exam_date date not null,\
		exam_type char not null,\
		exam_score integer not null,\
		PRIMARY KEY (driver_ssn, branch_id, exam_date),\
		FOREIGN KEY (driver_ssn) REFERENCES driver(driver_ssn),\
		FOREIGN KEY (branch_id) REFERENCES branch(branch_id))";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Use SQL to insert tuples into tables
	// Insert tuples into Table Branch

	sql = "insert into branch values\
		(10, 'Main', '1234 Main St.', 'Hoboken', 5551234),\
		(20, 'NYC', '23 No.3 Road', 'NYC', 5552331),\
		(30, 'West Creek', '251 Creek Rd.', 'Newark', 5552511),\
		(40, 'Blenheim', '1342 W.22 Ave.', 'Princeton', 5551342)";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Insert tuples into Table driver

	sql = "insert into driver values\
		(111111111, 'Bob Smith', '111 E.11 St.', 'Hoboken', '1975-01-01', 5551111),\
		(222222222, 'John Walters', '222 E.22 St.', 'Princeton', '1976-02-02', 5552222),\
		(333333333, 'Troy Rops', '333 W.33 Ave', 'NYC', '1970-03-03', 5553333),\
		(444444444, 'Kevin Mark', '444 E.4 Ave.', 'Hoboken', '1974-04-04', 5554444)";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Insert tuples into Table license

	sql = "insert into license values\
		(1, 111111111, 'D', 5, '2022-05-24', '2017-05-25', 20),\
		(2, 222222222, 'D', 5, '2023-08-29', '2016-08-29', 40),\
		(3, 333333333, 'L', 5, '2022-12-27', '2017-06-27', 20),\
		(4, 444444444, 'D', 5, '2022-08-30', '2017-08-30', 40)";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Insert all tuples into Table exam

	sql = "insert into exam values\
		(111111111, 20, '2017-05-25', 'D', 79),\
		(111111111, 20, '2017-12-02', 'L', 67),\
		(222222222, 30, '2016-05-06', 'L', 25),\
		(222222222, 40, '2016-06-10', 'L', 51),\
		(222222222, 40, '2016-08-29', 'D', 81),\
		(333333333, 10, '2017-07-07', 'L', 45),\
		(333333333, 20, '2017-06-27', 'L', 49),\
		(333333333, 20, '2017-07-27', 'L', 61),\
		(444444444, 10, '2017-07-27', 'L', 71),\
		(444444444, 20, '2017-08-30', 'L', 65),\
		(444444444, 40, '2017-09-01', 'L', 62)";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	// Use SQL to ask queries and retrieve data from the tables

	sql = "SELECT branch_id, branch_name, branch_addr FROM branch";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);
	int rowsCount = 0;
	while ((row = mysqlx_row_fetch_one(res))) {
		rowsCount++;
		int64_t idVal = 0;
		char nameVal[200];
		char addrVal[200];
		size_t name_array_size = sizeof(nameVal);
		size_t addr_array_size = sizeof(addrVal);
		mysqlx_get_sint(row, 0, &idVal);
		mysqlx_get_bytes(row, 1, 0, nameVal, &name_array_size);
		mysqlx_get_bytes(row, 2, 0, addrVal, &addr_array_size);
		cout << "Branch ID = " << idVal << ", Name = " << nameVal << ", Address = " << addrVal << endl;
	}
	cout << rowsCount << " rows were retrieved." << endl << endl;

	cout << "Query 1: Find the name of the drivers who got the license from the branch \"NYC\"" << endl;
	sql = "SELECT D.driver_name\
			FROM driver D\
			WHERE D.driver_ssn IN (SELECT L.driver_ssn\
								FROM license L NATURAL JOIN branch B\
								WHERE B.branch_name = 'NYC')";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	rowsCount = 0; // Re-zero out rowsCounter, since we're starting a new section.

	while ((row = mysqlx_row_fetch_one(res))) {
		rowsCount++;
		char nameVal[200];
		size_t name_array_size = sizeof(nameVal);
		mysqlx_get_bytes(row, 0, 0, nameVal, &name_array_size);
		cout << "Driver Name = " << nameVal << endl;
	}
	cout << rowsCount << " driver names were retrieved." << endl << endl;

	cout << "Query 2:  Find the name of the drivers whose driver license expire by 12/31/2022" << endl;
	sql = "SELECT D.driver_name\
			FROM driver D NATURAL JOIN license L\
			WHERE L.license_expiry <= '2022-12-31'";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	rowsCount = 0; // Re-zero out rowsCounter, since we're starting a new section.

	while ((row = mysqlx_row_fetch_one(res))) {
		rowsCount++;
		char nameVal[200];
		size_t name_array_size = sizeof(nameVal);
		mysqlx_get_bytes(row, 0, 0, nameVal, &name_array_size);
		cout << "Driver Name = " << nameVal << endl;
	}
	cout << rowsCount << " driver names were retrieved." << endl << endl;
	cout << "Query 3: Find the name of the drivers who took at least 2 exams for the same driver license type at the same branch." << endl;
	sql = "SELECT D.driver_name\
			FROM driver D\
			WHERE D.driver_ssn IN (SELECT E.driver_ssn\
								FROM exam E\
								GROUP BY E.branch_id, E.driver_ssn\
								HAVING COUNT(*) > 1)";
	stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
	res = mysqlx_execute(stmt);
	RESULT_CHECK(res, stmt);

	rowsCount = 0; // Re-zero out rowsCounter, since we're starting a new section.

	while ((row = mysqlx_row_fetch_one(res))) {
		rowsCount++;

//		int64_t idVal = 0;
		char nameVal[200];
		size_t name_array_size = sizeof(nameVal);

//		mysqlx_get_sint(row, 0, &idVal);
		mysqlx_get_bytes(row, 0, 0, nameVal, &name_array_size);
		cout << "Driver Name = " << nameVal << endl;
	}
	cout << rowsCount << " driver names were retrieved." << endl << endl;

	cout << "Query 4: Find the name of the drivers whose exam scores get consecutively lower when he/she took more exams." << endl;
	sql = "SELECT DISTINCT D.driver_name\
					FROM driver D\
					WHERE D.driver_ssn IN (SELECT E.driver_ssn\
										FROM (SELECT E1.driver_ssn, E1.exam_date, E1.exam_score\
												FROM exam E1\
												GROUP BY BY E1.driver_ssn, E1.exam_date\
												ORDER BY E1.driver_ssn, E1.exam_date) AS E INNER JOIN\
											(SELECT E2.driver_ssn, E2.exam_date, E2.exam_score\
												FROM exam E2\
												GROUP BY E2.driver_ssn, E2.exam_score\
												ORDER BY E2.driver_ssn, E2.exam_score) AS EE\
											ON E.exam_score = EE.exam_score\
											AND E.exam_date = EE.exam_date\
											AND E.exam_score = EE.exam_score)";

		stmt = mysqlx_sql_new(conn, sql.c_str(), sql.length());
		res = mysqlx_execute(stmt);
		RESULT_CHECK(res, stmt);

		rowsCount = 0; // Re-zero out rowsCounter, since we're starting a new section.

		while ((row = mysqlx_row_fetch_one(res))) {
			rowsCount++;
			char nameVal[200];
			size_t name_array_size = sizeof(nameVal);
			mysqlx_get_bytes(row, 0, 0, nameVal, &name_array_size);
			cout << "Driver Name = " << nameVal << endl;
		}
		cout << rowsCount << " driver names were retrieved." << endl << endl;
	mysqlx_session_close(conn); // Close the connection.
	cout << "Goodbye!" << endl;
	return 0;
}
