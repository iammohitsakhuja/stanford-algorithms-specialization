class SequenceAlignment {
  /** Get the lookup table for sequencing two strings. */
  private static int[][] getLookupTable(String a, String b, int gapPenalty, int mismatchPenalty) {
    // Get the length of strings.
    int lengthA = a.length();
    int lengthB = b.length();

    // Initialize the first row and column of the lookup table.
    int[][] lookupTable = new int[lengthA + 1][lengthB + 1];
    for (int i = 0; i <= lengthA; i++) lookupTable[i][0] = i * gapPenalty;
    for (int i = 0; i <= lengthB; i++) lookupTable[0][i] = i * gapPenalty;

    // Create the lookup table.
    for (int i = 1; i <= lengthA; i++)
      for (int j = 1; j <= lengthB; j++) {
        int costIncludingAi = lookupTable[i - 1][j] + gapPenalty; /* Ai and gap */
        int costIncludingBj = lookupTable[i][j - 1] + gapPenalty; /* Bj and gap */
        int costMatchingAiBj =
            a.charAt(i - 1) == b.charAt(j - 1)
                ? lookupTable[i - 1][j - 1] /* Ai == Bj */
                : lookupTable[i - 1][j - 1] + mismatchPenalty; /* Ai != Bj but match */

        lookupTable[i][j] =
            Integer.min(Integer.min(costIncludingAi, costIncludingBj), costMatchingAiBj);
      }

    return lookupTable;
  }

  /** Reconstructs the result from a lookupTable. */
  private static Result reconstructResult(
      String a, String b, int gapPenalty, int mismatchPenalty, int[][] lookupTable) {
    // To hold the resulting strings.
    StringBuilder resultA = new StringBuilder();
    StringBuilder resultB = new StringBuilder();

    int penalty = 0; /* Resulting penalty. */
    int i = lookupTable.length - 1;
    int j = lookupTable[0].length - 1;
    while (i > 0 && j > 0) {
      int costIncludingAi = lookupTable[i - 1][j] + gapPenalty; /* Ai and gap */
      int costIncludingBj = lookupTable[i][j - 1] + gapPenalty; /* Bj and gap */
      int costMatchingAiBj =
          a.charAt(i - 1) == b.charAt(j - 1)
              ? lookupTable[i - 1][j - 1] /* Ai == Bj */
              : lookupTable[i - 1][j - 1] + mismatchPenalty; /* Ai != Bj but match */

      if (lookupTable[i][j] == costMatchingAiBj) {
        // Include both Ai and Bj.
        resultA.append(a.charAt(i-- - 1));
        resultB.append(b.charAt(j-- - 1));
        if (a.charAt(i) != b.charAt(j)) penalty += mismatchPenalty;
      } else {
        if (lookupTable[i][j] == costIncludingBj) {
          // Include Bj and a gap.
          resultA.append('-');
          resultB.append(b.charAt(j-- - 1));
        } else {
          // Include Ai and a gap.
          resultA.append(a.charAt(i-- - 1));
          resultB.append('-');
        }
        penalty += gapPenalty;
      }
    }

    if (i != 0) {
      // Append any remaining characters from the beginning of A in reverse.
      resultA.append(new StringBuilder(a.substring(0, i)).reverse());

      // Append resulting B with same number of gaps.
      for (int padIndex = resultB.length(), len = resultA.length(); padIndex < len; padIndex++)
        resultB.append('-');
      penalty += a.substring(0, i).length() * gapPenalty;
    }

    if (j != 0) {
      // Append any remaining characters from the beginning of B in reverse.
      resultB.append(new StringBuilder(b.substring(0, j)).reverse());

      // Append resulting A with same number of gaps.
      for (int padIndex = resultA.length(), len = resultB.length(); padIndex < len; padIndex++)
        resultA.append('-');
      penalty += b.substring(0, j).length() * gapPenalty;
    }

    return new Result(resultA.reverse().toString(), resultB.reverse().toString(), penalty);
  }

  /**
   * Get the optimal sequence alignment for the given strings with given gap and mismatch penalties.
   */
  static Result getOptimalSequenceAlignmentFor(
      String a, String b, int gapPenalty, int mismatchPenalty) {

    int[][] lookupTable = getLookupTable(a, b, gapPenalty, mismatchPenalty);

    return reconstructResult(a, b, gapPenalty, mismatchPenalty, lookupTable);
  }
}
