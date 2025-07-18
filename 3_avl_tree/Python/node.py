#	AVL tree example by using python
#
#	author:		ITWorks4U
#	created:	July 16th, 2025
#

class Node:
	def __init__(self, node_id: str) -> None:
		self.node_id: str = node_id
		self.height: int = 0
		self.left_side: Node = None
		self.right_side: Node = None
	#end constructor

	def __repr__(self):
		return f"Node: {self.node_id}"
	#end method
#end class
