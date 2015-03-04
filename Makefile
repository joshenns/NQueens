all: bfs ids

parta: bfs.cc
	g++ -I -o bfs bfs.cc -Wall

partb: ids.cc
	g++ -I -o ids ids.cc -Wall

clean:
	rm -f *~

clean-all: clean
	rm -f bfs ids
