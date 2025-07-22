#	linked list example by using python
#
#	author:		ITWorks4U
#	created:	July 14th, 2025
#	updated:	July 22nd, 2025
#

class Node:
	#NOTE:
	#	usually, there's no need to check for a length
	#	of content, however, similar to C programming
	#	a limitation of 128 characters shall be used here as well
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

		if len(content) >= self._MAX_INPUT_LENGTH:
			self.content = self._INVALID_INPUT
		else:
			self.content = content
		#end if

		self.next = None
	#end constructor
#end class