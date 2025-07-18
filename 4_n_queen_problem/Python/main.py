#	n queen problem in Python
#
#	author:		ITWorks4U
#	created:	July 17th, 2025
#

from time import perf_counter
from queen_constants import UPPER_BOUNDARY
from n_queen_problem import QueenProblem

#	dictionary, which holds the number of queens as a key
#	and a result of solved or unsolved including the time
#	amount in seconds as its value
summaries: dict[str, str] = {}

def print_summary() -> None:
	"""
	Display the summary dictionary to stdout.
	"""
	print(end="\n\n")
	for summary in summaries.items():
		print(summary)
	#end for
#end function

def main() -> None:
	total_time: float = 0.0
	qp: QueenProblem = QueenProblem()

	for nbr_of_queens in range(1, UPPER_BOUNDARY + 1):
		head = f"""
>>
>> Try to insert {nbr_of_queens} queen(s) into the chess board...
>>
"""
		print(head)

		start = perf_counter()
		board = qp.solve_queen_problem(nbr_of_queens)
		end = perf_counter()

		duration = end - start
		total_time += duration

		if board is not None:
			qp.print_board(board)

			summaries[f"with {nbr_of_queens:02d} queens"] = f"found solution; duration: {duration:.4f} seconds"
		else:
			summaries[f"with {nbr_of_queens:02d} queens"] = f"unable to found a solution; duration: {duration:.4f} seconds"
		#end if
	#end for

	print_summary()
	print(f"\nTotal time: {total_time:.4f} seconds")
#end main

if __name__ == '__main__':
	main()
#end entry point
