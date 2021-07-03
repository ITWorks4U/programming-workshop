#!/usr/bin/python3

class AvlTree(object):
	data = None
	left = None
	right = None
	height = 0

	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None
		self.height = 1
	# end constructor

	def insert(self, root, key):
		if root is None:
			return AvlTree(key) 
		elif key < root.data: 
			root.left = self.insert(root.left, key)
		else: 
			root.right = self.insert(root.right, key)
		# end if

		root.height = 1 + self.getMaxValue(self.getHeight(root.left), self.getHeight(root.right))
		bf = self.getBalance(root)

		if bf > 1 and key < root.left.data:
			return self.rightRotate(root)
		# end if

		if bf < -1 and key > root.right.data:
			return self.leftRotate(root)
		# end if

		if bf > 1 and key > root.left.data:
			root.left = self.leftRotate(root.left)
			return self.rightRotate(root)
		# end if

		if bf < -1 and key < root.right.data:
			root.right = self.rightRotate(root.right)
			return self.leftRotate(root)
		# end if

		return root
	# end method

	def delete(self, root, key):
		if root is None: 
			return  None
		# end if

		if key < root.data:
			root.left = self.delete(root.left, key)
		elif key > root.data:
			root.right = self.delete(root.right, key)
		else:
			if root.left is None:
				temp = root.right
				root = None
				return temp
			elif root.right is None:
				temp = root.left
				root = None
				return temp
			# end if

			temp = self.getMinValueNode(root.right)
			root.data = temp.data
			root.right = self.delete(root.right, temp.data)
		# end if

		if root is None:
			return None
		# end if

		root.height = 1 + self.getMaxValue(self.getHeight(root.left), self.getHeight(root.right))
		bf = self.getBalance(root)

		if bf > 1 and self.getBalance(root.left) >= 0:
			return self.rightRotate(root)
		# end if

		if bf < -1 and self.getBalance(root.right) <= 0:
			return self.leftRotate(root)
		# end if 

		if bf > 1 and self.getBalance(root.left) < 0:
			root.left = self.leftRotate(root.left)
			return self.rightRotate(root)
		# end if

		if bf < -1 and self.getBalance(root.right) > 0:
			root.right = self.rightRotate(root.right)
			return self.leftRotate(root)
		# end if

		return root
	# end method

	def leftRotate(self, node):
		rightHand = node.right
		tmp = rightHand.left

		rightHand.left = node
		node.right = tmp

		node.height = 1 + self.getMaxValue(self.getHeight(node.left), self.getHeight(node.right))
		rightHand.height = 1 + self.getMaxValue(self.getHeight(rightHand.left), self.getHeight(rightHand.right))

		return rightHand
	# end method

	def rightRotate(self, node):
		leftHand = node.left
		tmp = leftHand.right

		leftHand.right = node
		node.left = tmp

		node.height = 1 + self.getMaxValue(self.getHeight(node.left), self.getHeight(node.right))
		leftHand.height = 1 + self.getMaxValue(self.getHeight(leftHand.left), self.getHeight(leftHand.right))

		return leftHand
	# end method

	def getHeight(self, root):
		if root is None:
			return 0
		# end if

		return root.height
	# end method

	def getBalance(self, root):
		if root is None:
			return 0
		# end if

		return (self.getHeight(root.left) - self.getHeight(root.right))
	# end method

	def getMinValueNode(self, root):
		current = root

		while current.left is not None:
			current = current.left
		# end while

		return current
	# end method

	def preOrder(self, node):
		if node is not None:
			leftSide = None
			rightSide = None

			if node.left is not None:
				leftSide = node.left.data
			# end if

			if node.right is not None:
				rightSide = node.right.data
			# end if

			print(" data: {0} (height: {1}, left: {2}, right: {3})".format(node.data, node.height, leftSide, rightSide)) 
			self.preOrder(node.left)
			self.preOrder(node.right)
		# end if
	# end method

	def inOrder(self, node):
		if node is not None:
			self.inOrder(node.left)

			leftSide = None
			rightSide = None

			if node.left is not None:
				leftSide = node.left.data
			# end if

			if node.right is not None:
				rightSide = node.right.data
			# end if

			print(" data: {0} (height: {1}, left: {2}, right: {3})".format(node.data, node.height, leftSide, rightSide)) 
			self.inOrder(node.right)
		# end if
	# end method

	def postOrder(self, node):
		if node is not None:
			self.postOrder(node.left)
			self.postOrder(node.right)

			leftSide = None
			rightSide = None

			if node.left is not None:
				leftSide = node.left.data
			# end if

			if node.right is not None:
				rightSide = node.right.data
			# end if

			print(" data: {0} (height: {1}, left: {2}, right: {3})".format(node.data, node.height, leftSide, rightSide))
		# end if
	# end method

	def getMaxValue(self, a, b):
		if a > b:
			return a
		# end if

		return b
	#end method

	def containsNode(self, node, key):
		if node is not None:
			current = node

			while current is not None:
				if current.data > key:
					current = current.left
				elif current.data < key:
					current = current.right
				else:
					break
				# end if
			# end while

			if current is not None:
				return True
			# end if
		# end if

		return False
	# end method

	def clearTree(self, node):
		if node is not None:
			self.clearTree(node.left)
			self.clearTree(node.right)
			del node
		# end if
	# end method
# end class