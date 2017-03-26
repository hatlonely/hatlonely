//
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// Example:
//   Given nums = [2, 7, 11, 15], target = 9,
//
// Because nums[0] + nums[1] = 2 + 7 = 9,
//   return [0, 1].
//

package leetcode

import (
	"fmt"
)

func twoSum(nums []int, target int) []int {
	numIdxMap := map[int]int{}

	for i := 0; i < len(nums); i++ {
		num := nums[i]
		if idx, ok := numIdxMap[target-num]; ok {
			return []int{idx, i}
		}
		numIdxMap[num] = i
	}

	return nil
}

func TwoSumTest() {
	{
		nums := []int{2, 7, 11, 15}
		fmt.Println(twoSum(nums, 9)) // [0, 1]
	}
	{
		nums := []int{3, 2, 4}
		fmt.Println(twoSum(nums, 6)) // [1, 2]
	}
}
