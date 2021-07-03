#!/usr/bin/python3

from AvlTree import AvlTree

def main():
	root = AvlTree('I')
	elements = ('T' ,'W' ,'o' ,'r' ,'k' ,'s' ,'4' ,'U')
	print(" inserting element I...")

	for key in elements:
		print(" inserting element %c..." % key)
		root = root.insert(root, key)
	# end for

	#	---	output	---
	print("\n pre order:")
	root.preOrder(root)

	print("\n in order:")
	root.inOrder(root)

	print("\n post order:")
	root.postOrder(root)
	print()

	#	---	searching	---
	searchKeys = ('r', '9')
	for key in searchKeys:
		hasElement = root.containsNode(root, key)

		if hasElement:
			print(" key %c found" % key)
		else:
			print(" key %c not found" % key)
		# end if
	# end for
	print()

	#	---	deletion	---
	removeKeys = ('r', '4', 'W')
	for key in removeKeys:
		print(" removing key %c..." % key)
		root = root.delete(root, key)
		root.preOrder(root)
		print()
	# end for

	root.clearTree(root)
# end function

if __name__ == "__main__":
	main()
# end if