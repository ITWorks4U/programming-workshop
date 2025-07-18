#	binary tree example by using python
#
#	author:		ITWorks4U
#	created:	July 15th, 2025
#

from node import Node

class BinaryTree:
	_PLACEHOLDER_FOR_NODE = '-'

	def __init__(self) -> None:
		"""Initializing a new empty node."""
		self.root: Node = None
	#end constructor

	def insert_into_tree(self, node_id: str) -> bool:
		"""
		Inserting a new node into the tree. *This is handled
		by using iteration only.*

		If the root does not exist yet, this will be created first.
		Otherwise the tree is going to traverse until the new node
		is able to insert, whereas this binary tree does not support
		multiple nodes.

		If this node already exists, nothing happens.

		node-id:
		- the ID for the new node to insert

		returns:
		- True, if root was None before or if the new node has successfully been inserted
		- False, if the new node already exists
		"""
		if self.root is None:
			self.root = Node(node_id)
			return True
		#end if

		current: Node = self.root
		parent: Node = None
		on_left_side: bool = False

		while current is not None:
			parent = current

			if current.node_id < node_id:
				current = current.right_side
				on_left_side = False
			elif current.node_id > node_id:
				current = current.left_side
				on_left_side = True
			else:
				return False
			#end if
		#end while

		if on_left_side:
			parent.left_side = Node(node_id)
		else:
			parent.right_side = Node(node_id)
		#end if

		return True
	#end method

	def get_minimal_node_value(self, node: Node) -> str | None:
		"""
		Returning the minimal value of the binary tree, which is
		located on the most left side of the binary tree.

		node:
		-	current node to start

		returns:
		-	the minimal node value or None for no match
		"""
		if node is not None:
			current = node
			while current.left_side:
				current = current.left_side
			#end while

			return current.node_id
		#end if

		return None
	#end method

	def delete_node(self, node_id: str) -> bool:
		"""
		Remove a node from the binary tree. *This method handles the
		iterative way only.*

		The node can one of three cases to handle:

		(1) node is a leaf (does not comes with any child)

		(2) node has at least one child (no matter, which side)

		(3) node has both childs

		For case 2 and 3 the sub tree(s) must be saved to ensure to still
		have the full tree without the removed node after completition.

		node_id:
		- ID to look for

		returns:
		- True, if the node has been found and removed
		- False, otherwise
		"""
		current: Node = self.root
		parent: Node = None

		while current is not None and current.node_id != node_id:
			parent = current

			if node_id < current.node_id:
				current = current.left
			else:
				current = current.right
			#end if
		#end while

		if current is None:
			# node was not found
			return False
		#end if

		# case 1: Node has two children
		if current.left_side is not None and current.right_side is not None:
			successor_parent: Node = current
			successor: Node = current.right_side

			while successor.left_side:
				successor_parent = successor
				successor = successor.left_side
			#end while

			# copy the successor's value
			current.node_id = successor.node_id

			# the successor can now be deleted (overwritten)
			current = successor
			parent = successor_parent

			# cases 2 and 3: Node has at most one child
			child = current.left_side if current.left_side else current.right_side

			if parent is None:
				# deleting the root node
				self.root = child
			elif parent.left_side == current:
				parent.left_side = child
			else:
				parent.right_side = child
			#end if

		return True
	#end method

	def pre_order_tree(self, node: Node) -> None:
		"""
		Display the tree in PRE-ORDER.
		Start with the node, followed by the left side and finally the right side.

		The IDs on the left and right are set by the current node's left and right side,
		if existing, otherwise a placeholder "-" is set instead.

		node:
		- current node to handle
		"""
		if node is not None:
			left_id = node.left_side.node_id if node.left_side else self._PLACEHOLDER_FOR_NODE
			right_id = node.right_side.node_id if node.right_side else self._PLACEHOLDER_FOR_NODE

			print(f"current: {node.node_id}\nleft: {left_id}\nright: {right_id}\n")
			self.pre_order_tree(node.left_side)
			self.pre_order_tree(node.right_side)
		#end if
	#end method

	def in_order_tree(self, node: Node) -> None:
		"""
		Display the tree in IN-ORDER.
		Start with the left side, followed by the node and finally the right side.

		The IDs on the left and right are set by the current node's left and right side,
		if existing, otherwise a placeholder "-" is set instead.

		node:
		- current node to handle
		"""
		if node is not None:
			left_id = node.left_side.node_id if node.left_side else self._PLACEHOLDER_FOR_NODE
			right_id = node.right_side.node_id if node.right_side else self._PLACEHOLDER_FOR_NODE

			self.in_order_tree(node.left_side)
			print(f"current: {node.node_id}\nleft: {left_id}\nright: {right_id}\n")
			self.in_order_tree(node.right_side)
		#end if
	#end method

	def post_order_tree(self, node: Node) -> None:
		"""
		Display the tree in POST-ORDER.
		Start with the left side, followed by the right side and finally the node itself.

		The IDs on the left and right are set by the current node's left and right side,
		if existing, otherwise a placeholder "-" is set instead.

		node:
		- current node to handle
		"""
		if node is not None:
			left_id = node.left_side.node_id if node.left_side else self._PLACEHOLDER_FOR_NODE
			right_id = node.right_side.node_id if node.right_side else self._PLACEHOLDER_FOR_NODE

			self.post_order_tree(node.left_side)
			self.post_order_tree(node.right_side)
			print(f"current: {node.node_id}\nleft: {left_id}\nright: {right_id}\n")
		#end if
	#end method

	def count_nodes(self, node: Node) -> int:
		"""
		Count the number of nodes for the current binary tree.

		node:
		-	current node to analyze

		returns:
		-	0, if the sub node does not exists
		-	the determined amount of nodes before
		"""
		if node is None:
			return 0
		#end if

		return 1 + self.count_nodes(node.left_side) + self.count_nodes(node.right_side)
	#end method

	def remove_full_binary_tree(self, node: Node) -> None:
		"""
		Remove the full binary tree. *This is handled by iteration only.*

		node:
		-	the current node (usually, the full binary tree by root)

		returns:
		-	None for the node does not exist or if the current binary tree has been removed from the system.
		"""
		from collections import deque

		if node is None:
			return None
		#end method

		queue = deque([node])

		while queue:
			current = queue.popleft()
			if current.left_side:
				queue.append(current.left_side)
			#end if

			if current.right_side:
				queue.append(current.right_side)
			#end if
			
			current.left_side = None
			current.right_side = None
		#end while

		#	the full tree has now been removed
		#	this return statement below is in use to mark the full binary
		#	tree as "vanished" from outside
		return None
	#end method

	def print_separator(self, message: str) -> None:
		"""
		Print a separator to the console in the format:
		"----------------"
		"[head message]"
		"----------------"

		message:
		-	the message to print
		"""
		head = f"""
----------------
[{message}]
----------------"""
		print(head)
	#end method

	def on_node_exists(self, node_id: str) -> bool:
		"""
		Checks, if the node with the ID exists in the binary tree.

		node_id:
		-	ID to look for

		returns:
		-	True, if the node has been found
		-	False, otherwise
		"""
		current: Node = self.root

		while current is not None:
			if current.node_id == node_id:
				return True
			#end if

			if current.node_id < node_id:
				current = current.right_side
			else:
				current = current.left_side
			#end if
		#end while

		return False
	#end method
#end class