import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

class CompletionTimes {
  /** Function to read the jobs from a file in the format (weight, length). */
  static Job[] getJobs(String fileName) {

    // Open file for reading and check for errors.
    Scanner reader = null;
    try {
      reader = new Scanner(new File(fileName));
    } catch (FileNotFoundException e) {
      System.err.println("FileNotFoundException thrown!");
      e.printStackTrace();
      return null;
    }

    // Get the total number of jobs.
    int numberOfJobs = reader.hasNextInt() ? reader.nextInt() : 0;

    Job[] jobs = new Job[numberOfJobs];

    // Read the jobs' data into the array.
    for (int i = 0; reader.hasNextInt() && i < jobs.length; i++) {
      int weight = reader.nextInt();
      int length = reader.hasNextInt() ? reader.nextInt() : 0;

      jobs[i] = new Job(weight, length);
    }

    // Housekeeping.
    reader.close();

    return jobs;
  }

  /** Calculates the completion time for each job. */
  static long[] getCompletionTimes(Job[] jobs) {
    // Create an array to hold the completion time of each job.
    long[] completionTimes = new long[jobs.length];

    // Keep track of the current time passed.
    long time = 0;

    // Calculate completion time of each job.
    for (int i = 0; i < jobs.length; i++) {
      time += jobs[i].getLength();
      completionTimes[i] = jobs[i].getWeight() * time;
    }

    return completionTimes;
  }

  public static void main(String[] args) {
    // Ensure proper usage.
    if (args.length != 1) {
      System.err.println("Usage: java CompletionTimes <fileName>");
      System.exit(1);
    }

    // Get the input.
    String fileName = args[0];

    // Read jobs from file.
    Job[] jobs = getJobs(fileName);
    if (jobs == null) {
      System.err.println("Error occurred in reading from file");
      System.exit(2);
    }

    // Sort the jobs.
    Arrays.sort(jobs, new SortByDifference());

    // Get the completion times.
    long[] completionTimes = getCompletionTimes(jobs);

    // Calculate the sum of the completion times.
    long sum = Arrays.stream(completionTimes).sum();

    System.out.println("Sum of weighted completion times: " + sum);
  }
}

class SortByDifference implements Comparator<Job> {
  public int compare(Job a, Job b) {
    int difference1 = a.getWeight() - a.getLength();
    int difference2 = b.getWeight() - b.getLength();

    if (difference1 == difference2) return b.getWeight() - a.getWeight();

    return difference2 - difference1;
  }
}

class Job {
  private int weight;
  private int length;

  Job() {
    this.weight = 0;
    this.weight = length;
  }

  Job(int weight, int length) {
    this.weight = weight;
    this.length = length;
  }

  int getWeight() {
    return this.weight;
  }

  int getLength() {
    return this.length;
  }
}
