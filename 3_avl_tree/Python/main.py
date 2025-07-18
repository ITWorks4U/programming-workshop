#	AVL tree example by using python
#
#	author:		ITWorks4U
#	created:	July 16th, 2025
#

from avl_tree import AVLTree

def main() -> None:
	avl_tree = AVLTree()

	avl_tree.print_separator("inserting elements into the AVL tree")
	for c in "ITWorks4U":
		avl_tree.insert_into_tree(c)
	#end for

	avl_tree.print_separator("PRE ORDER")
	avl_tree.pre_order_tree(node=avl_tree.root)

	avl_tree.print_separator("IN ORDER")
	avl_tree.in_order_tree(node=avl_tree.root)

	avl_tree.print_separator("POST ORDER")
	avl_tree.post_order_tree(node=avl_tree.root)

	avl_tree.print_separator("get the minimal value")
	print("Minimal node:", avl_tree.get_minimal_node(avl_tree.root))

	avl_tree.print_separator("delete node")

	head = f"""
delete a node, if existing
enter a single character only
	"""
	print(head)
	data = input(f"node to delete: ")

	if not isinstance(data, str) or len(data) != 1:
		print(f'your input "{data}" is invalid')
	else:
		summary = f"""
node "{data}" exists in binary tree: {"yes" if avl_tree.on_node_exists(node_id=data) else "no"}
node "{data}" has been deleted: {"yes" if avl_tree.delete_node(node_id=data) else "no"}
"""
		print(summary)

	avl_tree.print_separator("print again...")
	avl_tree.pre_order_tree(node=avl_tree.root)

	avl_tree.print_separator("count nodes")
	print("node count:", avl_tree.count_nodes(node=avl_tree.root))

	avl_tree.print_separator("remove AVL tree")
	avl_tree.remove_full_avl_tree()
#end main

if __name__ == '__main__':
	main()
#end entry point