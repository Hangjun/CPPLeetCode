# Statistics

## Weighted Random Sampling using Reservoir
In many applications sampling is required to be according to the weights that are assigned to each items available in set. For example, it might be required to sample queries in a search engine with weight as number of times they were performed so that the sample can be analyzed for overall impact on user experience. There are two ways to interpret weights assigned to each item in the set:[4]

Let the weight of each item be {\displaystyle w_{i}} w_{i} and sum of all weights be W. We can convert weight to probability of item getting selected in sample as {\displaystyle P_{i}=w_{i}/W} P_{i}=w_{i}/W.
Let the weight of two items i and j be {\displaystyle w_{i}} w_{i} and {\displaystyle w_{j}} w_{j}. Let the probability of item i getting selected in sample be {\displaystyle p_{i}} p_{i}, then we give {\displaystyle p_{j}=p_{i}\max(1,w_{j}/w_{i})} p_{j}=p_{i}\max(1,w_{j}/w_{i}).
Algorithm A-Res[edit]
The following algorithm was given by Efraimidis and Spirakis that uses interpretation 1:[4]

```c++
(*
  S is a stream of items to sample, R will contain the result
  S.Current returns current item in stream
  S.Weight  returns weight of current item in stream
  S.Next advances stream to next position
  The power operator is represented by ^
  min-priority-queue supports:
    Count -> number of items in priority queue
    Minimum() -> returns minimum key value of all items
    Extract-Min() -> Remove the item with minimum key
    Insert(key, Item) -> Adds item with specified key
 *)
ReservoirSample(S[1..?], R[1..k])
  H = new min-priority-queue
  while S has data
    r = Random(0,1) ^ (1/S.Weight)  // important: inclusive range
    if H.Count < k
      H.Insert(r, S.Current)
    else
      if H.Minimum < r
        H.Extract-Min()
        H.Insert(r, S.Current)
    S.Next
```

This algorithm is identical to the algorithm given in Reservoir Sampling with Random Sort except for the line how we generate the key using random number generator. The algorithm is equivalent to assigning each item a key {\displaystyle r^{1/w_{i}}} r^{1/w_{i}} where r is the random number and then sort items using these keys and finally select top k items for the sample.


