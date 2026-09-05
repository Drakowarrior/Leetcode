class Solution:
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        (x0, y0), (x1, y1) = coordinates[0], coordinates[1]
        if x1 - x0 == 0:
            return all(c[0] == x0 for c in coordinates)
        v = (y1 - y0) / (x1 - x0)
        for i in range(2, len(coordinates)):
            x, y = coordinates[i]
            if x - x0 == 0 or (y - y0) / (x - x0) != v:
                return False
        return True