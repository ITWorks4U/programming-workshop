#	binary tree example by using python
#
#	author:		ITWorks4U
#	created:	July 15th, 2025
#

from binary_tree import BinaryTree

def main() -> None:
	bst = BinaryTree()

	bst.print_separator("inserting elements into the binary tree")
	for c in "ITWorks4U":
		bst.insert_into_tree(c)
	#end for

	bst.print_separator("PRE ORDER")
	bst.pre_order_tree(node=bst.root)

	bst.print_separator("IN ORDER")
	bst.in_order_tree(node=bst.root)

	bst.print_separator("POST ORDER")
	bst.post_order_tree(node=bst.root)

	bst.print_separator("get the minimal value")
	print("Minimal node:", bst.get_minimal_node(bst.root))

	bst.print_separator("delete node")

	head = f"""
delete a node, if existing
enter a single character only
	"""
	print(head)
	data = input(f"node to delete: ")

	if not isinstance(data, str) and len(data) != 1:
		print(f'your input "{data}" is invalid')
	else:
		summary = f"""
node "{data}" exists in binary tree: {"yes" if bst.on_node_exists(node_id=data) else "no"}
node "{data}" has been deleted: {"yes" if bst.delete_node(node_id=data) else "no"}
"""
		print(summary)

	bst.print_separator("print again...")
	bst.pre_order_tree(node=bst.root)

	bst.print_separator("count nodes")
	print("node count:", bst.count_nodes(node=bst.root))

	bst.print_separator("remove binary tree")
	bst.remove_full_binary_tree()
#end main

if __name__ == '__main__':
	main()
#end entry point