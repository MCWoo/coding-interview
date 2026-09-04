# Starter bundle — Java

Java doesn't allow two classes with the same name in the same package, so
give the reference implementation its own class name and package, and keep
the three `.java` files compiled together. `PROBLEM.md` sits alongside them
as plain Markdown — not compiled, just saved for reference.

`PROBLEM.md`: the problem statement you wrote, saved verbatim (description,
constraints, examples).

`Solution.java`:
```java
public class Solution {
    // nums: int[] -- 2 <= nums.length <= 10^4, -10^9 <= nums[i] <= 10^9
    // target: int -- -10^9 <= target <= 10^9
    // Returns: int[] -- the two indices i, j (i != j) such that nums[i] + nums[j] == target
    public int[] solution(int[] nums, int target) {
        // TODO: implement your solution here
        return null;
    }
}
```
(The parameter/bounds comment is illustrative — replace it with the actual
signature and constraints for whatever problem you wrote.)

`interviewer_only/ReferenceSolution.java` (package `interviewer_only`):
```java
package interviewer_only;

public class ReferenceSolution {
    public int[] solution(int[] nums, int target) {
        java.util.Map<Integer, Integer> seen = new java.util.HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (seen.containsKey(complement)) return new int[]{seen.get(complement), i};
            seen.put(nums[i], i);
        }
        return new int[]{};
    }
}
```

`RunTests.java`:
```java
import interviewer_only.ReferenceSolution;
import java.util.Arrays;

public class RunTests {
    public static void main(String[] args) {
        Solution candidate = new Solution();
        ReferenceSolution reference = new ReferenceSolution();

        int[][] nums = { {2, 7, 11, 15}, {3, 2, 4} };
        int[] targets = { 9, 6 };

        int passed = 0;
        for (int i = 0; i < nums.length; i++) {
            int[] expected = reference.solution(nums[i], targets[i]);
            int[] actual = candidate.solution(nums[i], targets[i]);
            boolean ok = Arrays.equals(actual, expected); // adjust if order doesn't matter
            passed += ok ? 1 : 0;
            System.out.println("Test case " + (i + 1) + ": " + (ok ? "PASS" : "FAIL")
                + " | input=" + Arrays.toString(nums[i]) + ", target=" + targets[i]
                + " | your_output=" + Arrays.toString(actual)
                + " | expected=" + Arrays.toString(expected));
        }
        System.out.println("\n" + passed + "/" + nums.length + " passed");
    }
}
```

Compile with both files on the classpath:
`javac Solution.java interviewer_only/ReferenceSolution.java RunTests.java && java RunTests`
