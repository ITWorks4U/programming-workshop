#	linked list example by using python
#
#	author:		ITWorks4U
#	created:	July 14th, 2025
#

import re
from node import Node

class LinkedList:
	def __init__(self) -> None:
		"""
		Initialize a new linked list without any node.
		"""
		self.root = None
		self.next_id = 0
	#end constructor

	def get_node_content(self, id_to_use: int) -> str:
		"""
		Receiving the content of the current node by given ID to look for.
		This method is called only, if the ID has been found earlier.

		id_to_use:

		-	ID to use

		returns:

		-	The node's content based on it's ID.
		"""
		if self.root.node_id == id_to_use:
			return self.root.content
		else:
			current = self.root

			while current is not None:
				if current.node_id == id_to_use:
					return current.content
				#end if

				current = current.next
			#end while
		#end if
	#end method

	def add_to_list(self, content: str) -> None:
		"""
		Add a new element to the linked list.

		content:

		-	the content for the new added node
		"""
		new_node = Node(self.next_id, content)
		self.next_id += 1

		if self.root is None:
			self.root = new_node
		else:
			current = self.root
			while current.next:
				current = current.next
			#end while
			
			current.next = new_node
		#end if
	#end method

	def print_list(self) -> None:
		"""
		Print each node to the console in the format: [ID: {id}] content: {content}.
		"""
		current = self.root
		while current:
			print(f"[ID: {current.node_id}] content: {current.content}")
			current = current.next
		#end while
	#end method

	def remove_from_list(self, node_id: int) -> None:
		"""
		Remove a node from the list by given ID. If the linked list
		does not contain any data or the ID has not been found, an
		error message is going to print to the console.

		node_id:

		-	ID to remove from list
		"""
		if not self.root:
			print("List is empty.")
			return
		#end if

		# check, if the first element needs to be removed
		if self.root.node_id == node_id:
			self.root = self.root.next
			return
		#end if

		# otherwise walk trough the list to find the certain ID
		previous = self.root
		current = self.root.next

		while current is not None:
			if current.node_id == node_id:
				previous.next = current.next
				print(f"Node with ID {node_id} has been removed.")
				return
			#end if
			previous = current
			current = current.next
		#end while

		print(f"Node with ID {node_id} not found.")
	#end method

	def reverse_list(self):
		"""
		Reversing the linked list.
		"""
		prev = None
		current = self.root

		while current is not None:
			next_node = current.next
			current.next = prev
			prev = current
			current = next_node
		#end while

		self.root = prev
	#end method

	def clean_up(self) -> None:
		"""
		Remove the full list. In Python only root needs to be set to None,
		whereas the garbage collector also removes the other nodes.
		"""
		self.root = None
		self.next_id = 0
		print("List cleared.")
	#end method

	def on_existing_node(self, id_to_look_for: int) -> bool:
		"""
		Check, if a node may exist.

		id_to_look_for:

		-	The ID to look for

		returns:

		-	True, if the node has been found

		-	False, otherwise
		"""
		current = self.root

		while current is not None:
			if current.node_id == id_to_look_for:
				return True
			#end if

			current = current.next
		#end while

		return False
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

	def on_valid_input(self, input: str) -> bool:
		"""
		Checks, if the input is valid. Only in use for user input to convert
		the real detected number into an integer type.

		input:

		-	The input data from keyboard

		returns:

		-	True, if the input data passes trough the regular expression filter

		-	False, otherwise
		"""
		pattern = r"^[0-9]+$"
		re.compile(pattern=pattern)

		return re.match(pattern, input)
	#end method
#end class