#	double linked list example by using python
#
#	author:		ITWorks4U
#	created:	July 14th, 2025
#

class Node:
	_MAX_INPUT_LENGTH = 128
	_INVALID_INPUT = "*** content length was too long"

	def __init__(self, node_id: int, content: str) -> None:
		"""
		Initializing a new node for the linked list.
		The next node is set to None to mark, that this node
		is the last inserted node.

		node_id:

		-	certain ID for the current node

		content:
		
		-	data content for node
		"""
		self.node_id = node_id

		if not self._on_valid_content_length(content_to_insert=content):
			self.content = self._INVALID_INPUT
		else:
			self.content = content
		#end if

		self.prev = None
		self.next = None
	#end constructor

	def _on_valid_content_length(self, content_to_insert: str) -> bool:
		"""
		Checks, if the content length is valid. The length of 127 characters
		must not exceed.

		content_to_insert:

		-	the content for the new node

		returns:

		-	True, if the length of the new node's content does not exceed 127 characters
		-	False, otherwise
		"""
		return len(content_to_insert) < self._MAX_INPUT_LENGTH
	#end method
#end class node