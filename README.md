## RANGES

### Usage

usage: ranges <min> <max> <number_of_ranges> <file>

min: lower limit of total
max: upper limit of total
number_of_ranges: number of ranges generated from total
file: template file

### Template file

```sql
UPDATE table1
SET field1 = 1
WHERE field2 BETWEEN %d AND %d;
```
