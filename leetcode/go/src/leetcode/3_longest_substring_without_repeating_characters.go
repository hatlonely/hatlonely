//
// Given a string, find the length of the longest substring without repeating characters.
// Examples:
// Given "abcabcbb", the answer is "abc", which the length is 3.
// Given "bbbbb", the answer is "b", with the length of 1.
// Given "pwwkew", the answer is "wke", with the length of 3.
// Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
// Subscribe to see which companies asked this question.
//

package leetcode

import (
	"fmt"
)

func lengthOfLongestSubstring(str string) int {
	maxLen := 0
	idx1 := 0
	idx2 := 0
	flag := [256]bool{}
	for idx2 < len(str) {
		for ; idx2 < len(str) && !flag[str[idx2]]; idx2++ {
			flag[str[idx2]] = true
		}
		if maxLen < idx2-idx1 {
			maxLen = idx2 - idx1
		}
		if idx2 == len(str) {
			return maxLen
		}
		for ; str[idx1] != str[idx2]; idx1++ {
			flag[str[idx1]] = false
		}
		idx1++
		idx2++
	}

	return maxLen
}

func LengthOfLongestSubstringTest() {
	fmt.Println(lengthOfLongestSubstring("") == 0)
	fmt.Println(lengthOfLongestSubstring("a") == 1)
	fmt.Println(lengthOfLongestSubstring("au") == 2)
	fmt.Println(lengthOfLongestSubstring("dvdf") == 3)
	fmt.Println(lengthOfLongestSubstring("abcabcbb") == 3)
	fmt.Println(lengthOfLongestSubstring("bbbbb") == 1)
	fmt.Println(lengthOfLongestSubstring("pwwkew") == 3)
}
