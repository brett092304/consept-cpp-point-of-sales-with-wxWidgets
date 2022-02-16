wx = `wx-config --cxxflags --libs`
sql = -L/usr/lib -lmysqlcppconn
conn = -I/usr/include/cppconn
#cxx11 = -DCMAKE_CXX_FLAGS=-D__GLIBCXX_USE_CXX11_ABI=0
#disable-abi = --disable-libstdcxx-dual-abi

output: main.o program.o login.o ButtonSwitch.o connection.o lkupitemDialog.o sale.o SetUp.o
	g++ -Wall $(conn) *.o $(wx) $(sql) -o output

main.o: main.cpp main.h
	g++ -Wall $(conn) -c main.cpp $(wx) $(sql)

program.o: program.cpp program.h
	g++ -Wall $(conn) -c program.cpp $(wx) $(sql)

login.o: login.cpp login.h
	g++ -Wall $(conn) -c login.cpp $(wx) $(sql)

ButtonSwitch.o: ButtonSwitch.cpp
	g++ -Wall $(conn) -c ButtonSwitch.cpp $(wx) $(sql)

connection.o: connection.cpp connection.h
	g++ -Wall $(conn) -c connection.cpp $(wx) $(sql)

lkupitemDialog.o: lkupitemDialog.cpp lkupitemDialog.h
	g++ -Wall $(conn) -c lkupitemDialog.cpp $(wx) $(sql)

sale.o: sale.cpp sale.h
	g++ -Wall $(conn) -c sale.cpp $(wx) $(sql)

SetUp.o: SetUp.cpp SetUp.h
	g++ -Wall $(conn) -c SetUp.cpp $(wx) $(sql)

clean:
	rm *.o output