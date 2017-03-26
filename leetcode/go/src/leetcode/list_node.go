package leetcode

import (
	"strconv"
	"strings"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func NewList(li []int) *ListNode {
	if len(li) == 0 {
		return nil
	}
	head := &ListNode{li[0], nil}
	node := head
	for i := 1; i < len(li); i++ {
		node.Next = &ListNode{li[i], nil}
		node = node.Next
	}

	return head
}

func (n *ListNode) equals(node *ListNode) bool {
	l1 := n
	l2 := node
	for l1 != nil && l2 != nil {
		if l1.Val != l2.Val {
			return false
		}
		l1 = l1.Next
		l2 = l2.Next
	}

	return l1 == l2
}

func (n *ListNode) String() string {
	ls := []string{}
	for node := n; node != nil; node = node.Next {
		ls = append(ls, strconv.Itoa(node.Val))
	}
	return strings.Join(ls, " -> ")
}
