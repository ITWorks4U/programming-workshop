#!/usr/bin/python3
from BinaryTree import Tree

def main():
	root = Tree('I')
	elements = ('T', 'W', 'o', 'r', 'k', 's', '4', 'U')

	print("inserting element I")
	for element in elements:
		print("inserting element " + element)
		root.addNodeToTree(root, element)
	# end for

	#	---	output	---
	print("\npre order:")
	root.printPreOrder(root)

	print("\nin order:")
	root.printInOrder(root)

	print("\npost order:")
	root.printPostOrder(root)

	#	---	searching	---
	print("\nContains key?")
	searchKeys = ('k', 'Z')

	for key in searchKeys:
		foundNode = root.containsNode(root, key)

		if foundNode:
			print("Node %c found" % key)
		else:
			print("Node %c not exists" % key)
		# end if
	# end for

	#	---	removing	---
	print("\n-----\n")
	removeKeys = ('r', '4', 'W')

	for key in removeKeys:
		print("\nremoving element %c:" % key)
		root.removeNode(root, key)

		root.printPreOrder(root)
		print("\n-----\n")
	#end for

	root.cleanUp(root)
# end main

if __name__ == '__main__':
	main()
# end if