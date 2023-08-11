#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct range {
  int lo;
  int hi;
};

char *read_file(char *filePath) {
  FILE *ptr;
  char ch;
  char chToStr[2];
  chToStr[1] = '\0';

  ptr = fopen(filePath, "r");

  if (NULL == ptr)
    return NULL;

  fseek(ptr, 0L, SEEK_END);
  int sz = ftell(ptr);
  rewind(ptr);

  char *result = calloc(sz, sizeof(char));

  strcat(result, "%s");
  while (!feof(ptr)) {
    ch = fgetc(ptr);
    if ('\0' != ch) {
      chToStr[0] = ch;
      strcat(result, chToStr);
    }
  }
  result[sz + 1] = '\0';
  fclose(ptr);
  return result;
}

int generate_ranges(int min, int max, int number_of_ranges,
                    struct range ranges[]) {
  int i;
  int bucket_sizes[number_of_ranges];

  int even_length = (max - min + 1) / number_of_ranges;
  for (i = 0; i < number_of_ranges; ++i)
    bucket_sizes[i] = even_length;

  /* distribute surplus as evenly as possible across buckets */
  int surplus = (max - min + 1) % number_of_ranges;
  for (i = 0; surplus > 0; --surplus, i = (i + 1) % number_of_ranges)
    bucket_sizes[i] += 1;

  int n = 0, k = min;
  for (i = 0; i < number_of_ranges && k <= max; ++i, ++n) {
    ranges[i].lo = k;
    ranges[i].hi = k + bucket_sizes[i] - 1;
    k += bucket_sizes[i];
  }
  return n;
}

#define MAX_RANGES 300

int main(int argc, char *argv[]) {
  int i;
  struct range ranges[MAX_RANGES];

  if (argc != 5) {
    printf("usage: %s <min> <max> <number_of_ranges> <file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int min = atoi(argv[1]);
  int max = atoi(argv[2]);
  int number_of_ranges = atoi(argv[3]);
  char *filePath = argv[4];
  char *fileContent = read_file(filePath);

  assert(max > min);
  assert(number_of_ranges > 0);
  assert(number_of_ranges <= MAX_RANGES);
  assert(NULL != fileContent);

  printf("-- min=%d max=%d number_of_ranges=%d \n\n", min, max,
         number_of_ranges);

  int n = generate_ranges(min, max, number_of_ranges, ranges);
  for (i = 0; i < number_of_ranges; i++) {
    if (i < n) {
      printf(fileContent, i > 0 ? "\n\n" : "", ranges[i].lo, ranges[i].hi);
    } else
      printf("%s", i > 0 ? "\n" : "");
  }
  printf("\n");

  return EXIT_SUCCESS;
}
