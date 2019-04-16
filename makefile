all:
	g++ worker.cpp StringTokenizer.cpp -o worker
	g++ load_balancer.cpp -o lb
	g++ judge.cpp StringTokenizer.cpp -o judge
