linkfile := ./lib/stropt.cpp ./lib/configfile.cpp ./lib/configitem_base.cpp  ./lib/mysqlopt.cpp ./lib/slide_window.cpp
server: server.cpp
	g++ -g -o server server.cpp -lmysqlclient -I./lib  ./lib/*.cpp  -std=gnu++0x
exec:
	./server config/config.conf
client: client.cpp
	g++ -g -o client client.cpp -I./lib ./lib/slide_window.cpp
clean:
	rm  server client
connect: connect.cpp
	g++ -g -o connect connect.cpp -lmysqlclient -I./lib -I./libunp ./lib/*.cpp ./binunp/libunp.a  -std=gnu++0x
test: test.cpp
	g++ -g -o test test.cpp -I./lib/ ./lib/socketopt.cpp
