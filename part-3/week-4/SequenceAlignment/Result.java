class Result {
  String firstOutputString;
  String secondOutputString;
  int penalty;

  Result(String firstOutputString, String secondOutputString, int penalty) {
    this.firstOutputString = firstOutputString;
    this.secondOutputString = secondOutputString;
    this.penalty = penalty;
  }

  String getFirstOutputString() {
    return this.firstOutputString;
  }

  String getSecondOutputString() {
    return this.secondOutputString;
  }

  int getPenalty() {
    return this.penalty;
  }
}
