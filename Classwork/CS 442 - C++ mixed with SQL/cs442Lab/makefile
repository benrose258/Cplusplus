CXX      = g++
CXX_FILE = $(wildcard *.cpp)
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))

MYSQL_CONCPP_DIR = C:/Program\ Files/MySQL/Connector\ C++\ 8.0#Windows #~/C:/Program\ Files/MySQL/Connector\ C++\ 8.0#Linux #Connector/C++ installation location
MYSQL_CONCPP_DIR_MACOS = /usr/local/mysql-connector-c++-8.0.18
CXXFLAGS = -O2 -g -std=c++11 -fPIC -I $(MYSQL_CONCPP_DIR)/include -L $(MYSQL_CONCPP_DIR)/lib64/vs14

CXXFLAGS_MACOS = -O2 -g -std=c++11 -Wall -fPIC -I $(MYSQL_CONCPP_DIR_MACOS)/include -L $(MYSQL_CONCPP_DIR_MACOS)/lib64

LDLIBS = -lmysqlcppconn8

#-i is the same as --ignore-errors, which is needed because either macOS or Windows won't compile depending on the platform
all:
	$(MAKE) clean && $(MAKE) scarr -i && $(MAKE) mac -i
	$(MAKE) clean && $(MAKE) scarr -i && $(MAKE) mac -i
#For the Windows, make sure that you start the SQL server in the MySQL Workbench app before you run the code, as that's how you start the SQL server on Windows
scarr:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) $(LDLIBS) -o $(TARGET)

#For the Mac program, make sure that you use "brew services mysql start" and "brew services mysql stop" to start and stop the SQL server, which is necessary for the code to work
mac:
	$(CXX) $(CXXFLAGS_MACOS) $(CXX_FILE) $(LDLIBS) -o $(TARGET)
clean:
	rm -rf *.exe  *.dSYM $(TARGET)
