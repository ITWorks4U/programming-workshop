#!/usr/bin/python3

class Tree:
	leftSide = None
	rightSide = None
	data = None

	def __init__(self, data):
		self.data = data
		self.leftSide = None
		self.rightSide = None
	# end constructor

	def addNodeToTree(self, tree, newData):
		if tree is None:
			tree = Tree(newData)
		else:
			leftSide = False
			alreadyExists = False
			current = tree
			tmp = None

			while current is not None:
				tmp = current

				if current.data > newData:
					leftSide = True
					current = current.leftSide
				elif current.data < newData:
					leftSide = False
					current = current.rightSide
				else:
					alreadyExists = True
					break
				# end if
			# end while

			if leftSide and not alreadyExists:
				tmp.leftSide = Tree(newData)
			elif not leftSide and not alreadyExists:
				tmp.rightSide = Tree(newData)
			# end if
		# end if
	# end method

	def containsNode(self, tree, searchKey):
		if tree is not None:
			tmp = tree

			while tmp is not None:
				if searchKey > tmp.data:
					tmp = tmp.rightSide
				elif searchKey < tmp.data:
					tmp = tmp.leftSide
				else:
					break
				# end if
			# end while

			if tmp is not None:
				return True
			# end if
		# end if

		return False
	# end function

	def removeNode(self, tree, removeKey):
		if tree is None:
			return tree
		# end if

		if removeKey < tree.data:
			tree.leftSide = self.removeNode(tree.leftSide, removeKey)
		elif removeKey > tree.data:
			tree.rightSide = self.removeNode(tree.rightSide, removeKey)
		else:
			if tree.leftSide is None:
				backup = tree.rightSide
				tree = None
				return backup
			elif tree.rightSide is None:
				backup = tree.leftSide
				tree = None
				return backup
			# end if

			backup = self.getMinimalNode(tree.rightSide)
			tree.data = backup.data

			tree.rightSide = self.removeNode(tree.rightSide, backup.data)
		# end if

		return tree
	# end method

	def getMinimalNode(self, subTree):
		current = subTree

		while current.leftSide is not None:
			current = current.leftSide
		# end if

		return current
	# end method

	def printPreOrder(self, root):
		if root is not None:
			contentLeft = None
			contentRight = None

			if (root.leftSide is not None):
				contentLeft = root.leftSide.data
			# end if

			if (root.rightSide is not None):
				contentRight = root.rightSide.data
			# end if

			print("data: {0} (left: {1}, right: {2})".format(root.data, contentLeft, contentRight))

			self.printPreOrder(root.leftSide)
			self.printPreOrder(root.rightSide)
		# end if
	# end method

	def printInOrder(self, root):
		if root is not None:
			self.printInOrder(root.leftSide)

			contentLeft = None
			contentRight = None

			if (root.leftSide is not None):
				contentLeft = root.leftSide.data
			# end if

			if (root.rightSide is not None):
				contentRight = root.rightSide.data
			# end if

			print("data: {0} (left: {1}, right: {2})".format(root.data, contentLeft, contentRight))

			self.printInOrder(root.rightSide)
		# end if
	# end method

	def printPostOrder(self, root):
		if root is not None:
			self.printPostOrder(root.leftSide)
			self.printPostOrder(root.rightSide)

			contentLeft = None
			contentRight = None

			if (root.leftSide is not None):
				contentLeft = root.leftSide.data
			# end if

			if (root.rightSide is not None):
				contentRight = root.rightSide.data
			# end if

			print("data: {0} (left: {1}, right: {2})".format(root.data, contentLeft, contentRight))
		# end if
	# end method

	def cleanUp(self, root):
		if root is not None:
			self.cleanUp(root.leftSide)
			self.cleanUp(root.rightSide)

			del root
		# end if
	# end method
# end class