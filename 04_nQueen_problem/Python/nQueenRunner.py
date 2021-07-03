#!/usr/bin/python3

from nQueen import NQueenProblem

def main():
	q = NQueenProblem()

	for i in range(20):
		print(" using %d fields:" % (i+1))
		q.initQueenProblem(i+1)
		print()
	# end for

# end main

if __name__ == "__main__":
	main()
# end if