#	AVL tree example by using python
#
#	author:		ITWorks4U
#	created:	July 16th, 2025
#	updated:	July 17th, 2025
#

from node import Node

class AVLTree:
	_PLACEHOLDER_FOR_NODE = '-'

	def __init__(self) -> None:
		"""Initializing a new empty node."""
		self.root: Node = None
	#end constructor

	# #end method
	def insert_into_tree(self, node_id: str) -> bool:
		"""
		Inserting a new node into the tree. *This is handled
		by using the nested method _insert_into_tree() only.*

		At the beginning root is going to create first.

		node_id:
		-	ID to insert

		returns:
		-	inserted state for root and the next nodes itself
		"""
		self.root, inserted = self._insert_into_tree(self.root, node_id)
		return inserted
	#end method

	def _insert_into_tree(self, current: Node, node_id: str) -> tuple[Node, bool]:
		"""
		Inserting a new node into the tree by using the **recursive** way only.
		This method returns a tuple of the node and a boolean value, because in contrast
		to C there's no call by reference available.

		This AVL tree does not support multiple elements.

		current:
		-	current node to handle

		node_id:
		-	ID for the new node to insert

		returns:
		-	a tuple of the current node and a boolean expression as a flag
		"""
		if current is None:
			#	new node to insert
			return (Node(node_id), True)
		#end if

		if node_id < current.node_id:
			#	go into the left side
			current.left_side, inserted = self._insert_into_tree(current.left_side, node_id)
		elif node_id > current.node_id:
			#	go into the right side
			current.right_side, inserted = self._insert_into_tree(current.right_side, node_id)
		else:
			#	any douplicate has been found here
			return (current, False)
		#end if

		current.height = max(self.get_tree_height(current.left_side), self.get_tree_height(current.right_side)) + 1
		balance_factor = self.get_balance_factor(current)

		if balance_factor > 1 and node_id < current.left_side.node_id:
			return (self.rotate_right(current), inserted)
		# end if

		if balance_factor < -1 and node_id > current.right_side.node_id:
			return (self.rotate_left(current), inserted)
		# end if

		if balance_factor > 1 and node_id > current.left_side.node_id:
			current.left_side = self.rotate_left(current.left_side)
			return (self.rotate_right(current), inserted)
		# end if

		if balance_factor < -1 and node_id < current.right_side.node_id:
			current.right_side = self.rotate_right(current.right_side)
			return (self.rotate_left(current), inserted)
		# end if

		return (current, inserted)
	#end method

	def get_minimal_node(self, node: Node) -> Node:
		"""
		Get the minimal node of the tree.

		node:
		-	the node to start

		returns:
		-	None, if the node does not exist
		-	otherwise the minimal node
		"""
		if node is None:
			return None
		#end if

		while node.left_side is not None:
			node = node.left_side
		#end while

		return node
	#end method

	def delete_node(self, node_id: str) -> bool:
		"""
		Remove a node from the tree. *This is handled by nested method _delete_node() only.*

		node_id:
		-	ID to remove from the tree, if existing

		returns:
		-	the deleted boolean state, depending on, if the ID has been found in the tree or not
		"""
		self.root, deleted = self._delete_node(self.root, node_id)
		return deleted
	#end method

	def _delete_node(self, current: Node, node_id: str) -> tuple[Node, bool]:
		"""
		Remove a node from the AVL tree. *This method handles the removal procedure by recursion only.*
		It returns a tuple of the handled node and a boolean expression.

		current:
		-	current node

		node_id:
		-	ID to look for

		returns:
		-	a tuple of the handled node and a boolean expression
		"""
		if current is None:
			return (None, False)
		#end if

		if node_id < current.node_id:
			current.left_side, deleted = self._delete_node(current.left_side, node_id)
		elif node_id > current.node_id:
			current.right_side, deleted = self._delete_node(current.right_side, node_id)
		else:
			# node found
			if current.left_side is None:
				return (current.right_side, True)
			elif current.right_side is None:
				return (current.left_side, True)
			#end if

			# for two children only
			successor = self.get_minimal_node(current.right_side)
			current.node_id = successor.node_id
			current.right_side, _ = self._delete_node(current.right_side, successor.node_id)
			return (current, True)
		#end if

		if current is None:
			return None
		#end if

		current.height = max(self.get_tree_height(current.left_side), self.get_tree_height(current.right_side)) + 1
		balance_factor = self.get_balance_factor(current)

		if balance_factor > 1 and self.get_balance_factor(current.left_side) >= 0:
			return (self.rotate_right(current), deleted)
		# end if

		if balance_factor < -1 and self.get_balance_factor(current.right_side) <= 0:
			return (self.rotate_left(current), deleted)
		# end if 

		if balance_factor > 1 and self.get_balance_factor(current.left_side) < 0:
			current.left_side = self.rotate_left(current.left_side)
			return (self.rotate_right(current), deleted)
		# end if

		if balance_factor < -1 and self.get_balance_factor(current.left_side) > 0:
			current.right_side = self.rotate_right(current.right_side)
			return (self.rotate_left(current), deleted)
		# end if

		#	only in case if the node to delete hasn't been found anywhere
		return (current, deleted)
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

	def in_order_tree(self, node) -> None:
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

	def post_order_tree(self, node) -> None:
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

	def count_nodes(self, node) -> int:
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

	def remove_full_avl_tree(self) -> None:
		"""
		Removing the full AVL tree from memory.
		*This is handled by the nested method _remove_full_avl_tree().*

		When the full AVL tree has been removed, root itself is going to set to None.
		"""
		self._remove_full_avl_tree(self.root)
		self.root = None
	#end method

	def _remove_full_avl_tree(self, node: Node) -> None:
		"""
		Removing the full AVL tree from memory. *This is handled by recursion only.*

		node:
		-	current node to remove
		"""
		if node is not None:
			self._remove_full_avl_tree(node.left_side)
			self._remove_full_avl_tree(node.right_side)

			node.left_side = None
			node.right_side = None
			node = None
		#end if
	#end method

	def print_separator(self, message: str) -> None:
		"""
		Print a separator to the console in the format:
		----------------
		[head message]
		----------------
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

	#	AVL methods
	def get_tree_height(self, node: Node) -> int:
		"""
		Returning the height of the current node.

		node:
		-	node to check

		returns:
		-	-1, if the node is None
		-	otherwise, the node height
		"""
		return node.height if node is not None else -1
	#end method

	def get_balance_factor(self, node: Node) -> int:
		"""
		Returning the balance factor of an AVL tree. If the balance factor of an AVL tree
		exceeds 0, then this AVL tree needs to be rotated to the left or right, depending on
		where the current height dominates.

		node:
		-	node to use

		returns:
		-	0, if the node is None
		-	otherwise, the node height
		"""
		if node is None:
			return 0
		#end if

		return self.get_tree_height(node.left_side) - self.get_tree_height(node.right_side)
	#end method

	def rotate_right(self, node: Node) -> Node:
		"""
		Rotate the current node to the right side, when the left side dominates.

		node:
		-	current affected node

		returns:
		-	the left side of the node
		"""
		left_hand: Node = node.left_side
		temp: Node = left_hand.right_side

		left_hand.right_side = node
		node.left_side = temp

		node.height = max(self.get_tree_height(node.left_side), self.get_tree_height(node.right_side)) + 1
		left_hand.height = max(self.get_tree_height(left_hand.left_side), self.get_tree_height(left_hand.right_side)) + 1

		return left_hand
	#end method

	def rotate_left(self, node: Node) -> Node:
		"""
		Rotate to the left side, when the right side dominates.

		node:
		-	current affected node

		returns:
		-	the right side of the node
		"""
		right_hand: Node = node.right_side
		temp: Node = right_hand.left_side
		right_hand.left_side = node
		node.right_side = temp

		node.height = max(self.get_tree_height(node.left_side), self.get_tree_height(node.right_side)) + 1
		right_hand.height = max(self.get_tree_height(right_hand.left_side), self.get_tree_height(right_hand.right_side)) + 1

		return right_hand
	#end method
#end class