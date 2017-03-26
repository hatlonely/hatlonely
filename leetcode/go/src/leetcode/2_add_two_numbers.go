//
// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order and each of their nodes contain a single digit.
// Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
//

package leetcode

import "fmt"

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	prev := &ListNode{0, nil}
	node := prev
	carry := 0

	for l1 != nil && l2 != nil {
		val := l1.Val + l2.Val + carry
		carry = val / 10
		node.Next = &ListNode{val % 10, nil}
		node = node.Next
		l1 = l1.Next
		l2 = l2.Next
	}
	for l1 != nil {
		val := l1.Val + carry
		carry = val / 10
		node.Next = &ListNode{val % 10, nil}
		node = node.Next
		l1 = l1.Next
	}
	for l2 != nil {
		val := l2.Val + carry
		carry = val / 10
		node.Next = &ListNode{val % 10, nil}
		node = node.Next
		l2 = l2.Next
	}
	if carry != 0 {
		node.Next = &ListNode{carry, nil}
		node = node.Next
	}

	return prev.Next
}

func AddTwoNumbersTest() {
	l1 := NewList([]int{2, 4, 3})
	l2 := NewList([]int{5, 6, 4})
	l3 := NewList([]int{7, 0, 8})
	fmt.Println(addTwoNumbers(l1, l2))
	fmt.Println(addTwoNumbers(l1, l2).equals(l3))
}
