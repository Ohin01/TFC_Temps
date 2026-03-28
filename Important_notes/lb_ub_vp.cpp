// lower_bound():
//  It returns an iterator pointing to the first element in the range [first, last) which has a value greater than or equal to the given value "val". 
//  But in Vector of Pairs lower_bound() for pair(x, y) will return an iterator pointing to the position of pair whose  

//  -> first value is greater than x 
//  -> first value is equal to  x and second value is greater than equals to y.
//  -> If the above-mentioned criteria are not met, then it returns an iterator to the index which is out of the vectors of pairs. 


// upper_bound():
// It returns an iterator pointing to the first element in the range [first, last) which has a value greater than the given value "val". 
// But in Vector of Pairs upper_bound() for pair(x, y) will return an iterator pointing to the position of the pair whose

// -> First value is equal to x and the second value is greater than y, or
// -> Whose first value is greater than x.