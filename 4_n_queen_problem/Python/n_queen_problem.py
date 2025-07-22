#	n queen problem in Python
#
#	author:		ITWorks4U
#	created:	July 17th, 2025
#	updated:	July 22nd, 2025
#

from queen_constants import QUEEN, EMPTY

class QueenProblem:
	def solve_queen_problem(self, number_of_fields: int) -> list[list[str]] | None:
		"""
		Solving the n queen problem by using recursive backtracking.
		It starts with the creation of the chess board, followed by
		the algorithm to figure out, if on the certain coordinate a
		queen is able to place without threating an another queen or
		being threatened by another queen in horizontal, vertical or
		diagonal way.

		This method comes with two nested functions to check, if the
		current field is a safe field for a queen to take place.
		This function returns True, if on the current coordinate the
		next queen has been successfully placed or false, if this queen
		is threatened by another queen from any direction.

		The second function place_queen starts with the first field
		on position [0,0] to try to store the first and the next queen
		on the next possible field. Thus function returns true, if on
		this coordinate a queen has successfully placed otherwise false.
		Furthermore on the certain coordinate a queen, marked with "Q" is
		now being placed, otherwise "-" will be placed there.

		number_of_fields:
		-	the number of fields to use

		returns:
		-	the created board of number_of_fields * number_of_fields
			including the solution of the current n queen problem or
			None, if the n queen problem has been failed
		"""

		#	initialize an empty board
		chess_board = [[EMPTY for _ in range(number_of_fields)] for _ in range(number_of_fields)]

		def on_safe_field(row: str, col: str) -> bool:
			#	check the current row, if there's already a queen placed
			for i in range(col):
				if chess_board[row][i] == QUEEN:
					return False
				#end if
			#end for

			#	check diagonal (top left to bottom right)
			for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
				if chess_board[i][j] == QUEEN:
					return False
				#end if
			#end for

			#	check diagonal (bottom left to top right)
			for i, j in zip(range(row, number_of_fields), range(col, -1, -1)):
				if chess_board[i][j] == QUEEN:
					return False
				#end if
			#end for

			#	at this moment the queen has been placed on a safe field,
			#	however, this does not means, that this queen will truly be
			#	safe here; it depends on the backtracking step, if required,
			#	if the queen is on the correct coordinate
			return True
		#end function

		def try_to_place_queen(current_coordinate: int) -> bool:
			#	if every coordinate has been marked, then there's
			#	no more action to do and True returns
			if current_coordinate >= number_of_fields:
				return True
			#end if

			#	check each coordinate out to try to place a queen anywhere 
			for row in range(number_of_fields):
				if on_safe_field(row, current_coordinate):
					#	on this coordinate a queen was able to place
					chess_board[row][current_coordinate] = QUEEN
					if try_to_place_queen(current_coordinate + 1):
						return True
					#end if
				#end if

				#	on this coordinate can't be a queen placed
				chess_board[row][current_coordinate] = EMPTY
			#end for
		
			return False
		#end function

		return chess_board if try_to_place_queen(0) else None
	#end function

	def print_board(self, chess_board: list[list[str]]) -> None:
		"""
		Print the current board to stdout.

		board:
		-	the n*n dimensional board of 1x1 - 20x20
		"""
		for row in chess_board:
			everything = f"""
{" ".join(row)}"""
			print(everything, end="")
		#end for
	#end method
#end class
