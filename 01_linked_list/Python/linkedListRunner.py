#!/usr/bin/python3

from linkedList import LinkedList

def main():
	linkedList = LinkedList()

	linkedList.addToList("Monday")
	linkedList.addToList("Tuesday")
	linkedList.addToList("Wednesday")
	linkedList.addToList("Thursday")
	linkedList.addToList("Friday")
	linkedList.addToList("Saturday")
	linkedList.addToList("Sunday")
	linkedList.printList()

	print("removing an element from the list....")
	linkedList.removeFromList("Monday")
	linkedList.printList()

	linkedList.addToList("Monday")

	print("reversing linked list....")
	linkedList.reverseList()
	linkedList.printList()

	linkedList.clearList()
#end main

if __name__ == '__main__':
	main()
# end if