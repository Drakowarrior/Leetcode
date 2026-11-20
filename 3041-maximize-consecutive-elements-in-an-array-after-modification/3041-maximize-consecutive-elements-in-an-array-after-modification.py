class Solution:
    def maxSelectedElements(self, nums: list[int]) -> int:
        best = keep = bump = 1
        last = -10
        for x in sorted(nums):
            match x - last:
                case 0: bump = keep + 1  # x repeat: bump it on top of keep
                case 1: keep, bump = keep + 1, bump + 1  # x extends keep, x + 1 extends bump
                case 2: keep, bump = bump + 1, 1  # x extends bump, x + 1 starts over
                case _: keep = bump = 1
            best, last = max(best, keep, bump), x
        return best