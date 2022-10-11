wx = `wx-config --cxxflags --libs`
sql = -L/usr/lib -lmysqlcppconn
conn = -I/usr/include/cppconn

output: main.o program.o login.o ButtonSwitch.o connection.o lkupitemDialog.o sale.o SetUp.o ManualCreditCard.o ResumeTranx.o
	g++ -Wall $(conn) *.o $(wx) $(sql) -lstdc++fs -o output.exe

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

ManualCreditCard.o: ManualCreditCard.h ManualCreditCard.cpp
	g++ -Wall $(conn) -c ManualCreditCard.cpp $(wx) $(sql)

ResumeTranx.o: ResumeTranx.h ResumeTranx.cpp
	g++ -Wall $(conn) -c ResumeTranx.cpp $(wx) $(sql)

clean:
	rm *.o *.exe output
