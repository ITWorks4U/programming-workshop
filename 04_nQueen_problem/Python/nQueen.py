#!/usr/bin/python3

class NQueenProblem:
	def printSolution(self, board, numberOfFields):
		for i in range(numberOfFields):
			for j in range(numberOfFields):
				print(board[i][j], end=' ')
			# end for

			print()
		# end for
	# end method

	def onSafeField(self, board, row, column, numberOfFields):
		for i in range(column):
			if board[row][i] == 'Q':
				return False
			# end if
		# end for

		for i,j in zip(range(row, -1, -1), range(column, -1, -1)):
			if board[i][j] == 'Q':
				return False
			# end if
		# end for

		for i,j in zip(range(row, numberOfFields, 1), range(column, -1, -1)):
			if board[i][j] == 'Q':
				return False
			# end if
		# end for

		return True
	# end method

	def solveQueenProblem(self, board, column, numberOfFields):
		if column >= numberOfFields:
			return True
		# end if

		for i in range(numberOfFields):
			if self.onSafeField(board, i, column, numberOfFields):
				board[i][column] = 'Q'
				
				if self.solveQueenProblem(board, column + 1, numberOfFields):
					return True
				# end if

				board[i][column] = '-'
			# end if
		# end for

		return False
	# end method

	def initQueenProblem(self, numberOfFields):
		board = self.createBoard(numberOfFields)

		if self.solveQueenProblem(board, 0, numberOfFields):
			self.printSolution(board, numberOfFields)
			return True
		# end if

		print("using %d fields: no solution found" % numberOfFields)
		return False
	# end method

	def createBoard(self, numberOfFields):
		field = list()

		for _ in range(numberOfFields):
			innerList = list()

			for __ in range(numberOfFields):
				innerList.append('-')
			# end for

			field.append(innerList)
		# end for

		return field
	# end method
# end class