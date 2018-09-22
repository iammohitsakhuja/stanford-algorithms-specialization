class SequenceAlignmentTest {
  static void test() {
    // Define constants.
    final String a = "AACAGTTACC";
    final String b = "TAAGGTCA";
    final String c = "CG";
    final String d = "CA";
    final String e = "AGGGCT";
    final String f = "AGGCA";

    // Test 1.
    Result result = SequenceAlignment.getOptimalSequenceAlignmentFor(a, b, 2, 1);
    assert result.getFirstOutputString().equals("AACAGTTACC");
    assert result.getSecondOutputString().equals("TA-AGGT-CA");
    assert result.getPenalty() == 7;

    // Test 2.
    result = SequenceAlignment.getOptimalSequenceAlignmentFor(c, d, 3, 7);
    assert result.getFirstOutputString().equals("CG-");
    assert result.getSecondOutputString().equals("C-A");
    assert result.getPenalty() == 6;

    // Test 3.
    result = SequenceAlignment.getOptimalSequenceAlignmentFor(c, d, 3, 5);
    assert result.getFirstOutputString().equals("CG");
    assert result.getSecondOutputString().equals("CA");
    assert result.getPenalty() == 5;

    // Test 4.
    result = SequenceAlignment.getOptimalSequenceAlignmentFor(e, f, 3, 2);
    assert result.getFirstOutputString().equals("AGGGCT");
    assert result.getSecondOutputString().equals("A-GGCA");
    assert result.getPenalty() == 5;
  }

  public static void main(String[] args) {
    test();
    System.out.println("All tests passed!");
  }
}
