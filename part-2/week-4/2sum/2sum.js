const fs = require('fs')
const { performance } = require('perf_hooks')

// Function to load the numbers from a file into a set.
const loadNumbers = fileName => {
  const lines = fs.readFileSync(fileName, 'utf8').split('\n')
  const numbers = new Set()

  lines.forEach(line => {
    if (line.length > 0) numbers.add(parseInt(line))
  })

  return numbers
}

/* Function to count the number of achievable targets within the range
 * [start, end] that can be achieved by adding x and y, where x and y are
 * two distinct numbers in `numbers`.
 */
const countAchievableTargets = (numbers, start, end) => {
  let count = 0
  for (let target = start; target <= end; target += 1) {
    /* eslint-disable-next-line */
    for (const number of numbers.keys()) {
      const x = target - number
      if (x !== number) {
        if (numbers.has(x)) {
          count += 1
          break
        }
      }
    }
  }

  return count
}

// Ensure proper usage.
if (process.argv.length !== 5) {
  console.log('Usage: node 2sum.js <file_name> <start> <end>')
  process.exit(1)
}

// Get the required inputs.
const fileName = process.argv[2]
const start = parseInt(process.argv[3])
const end = parseInt(process.argv[4])

// Load the numbers from the file into the hash table, and benchmark the time
// taken.
const loadStartTime = performance.now()
const numbers = loadNumbers(fileName)
const loadEndTime = performance.now()
const timeLoading = (loadEndTime - loadStartTime) / 1000
console.log(`No. of distinct numbers: ${numbers.size}`)

// Count the number of achievable targets within the range [start, end], and
// benchmark the time taken.
const countingStartTime = performance.now()
const count = countAchievableTargets(numbers, start, end)
const countingEndTime = performance.now()
const countingTime = (countingEndTime - countingStartTime) / 1000
console.log(`Count of achievable targets: ${count}\n`)

// Display the benchmark results.
console.log(`TIME IN loading the numbers into the hash table:     \
  ${timeLoading.toPrecision(3)}s`)
console.log(`TIME IN counting achievable targets:              \
  ${countingTime.toPrecision(7)}s`)
console.log(`TIME IN total:                                    \
  ${(timeLoading + countingTime).toPrecision(7)}s`)
