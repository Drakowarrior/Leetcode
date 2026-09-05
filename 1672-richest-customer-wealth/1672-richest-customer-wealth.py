class Solution(object):
    def maximumWealth(self, accounts):
        rich = 0
        for i in accounts:
            rich = max(rich, sum(i))
        return rich
        