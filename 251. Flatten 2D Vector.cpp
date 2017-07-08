/*
Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.
*/

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        curRow = vec2d.begin();
        lastRow = vec2d.end();
        
        // adjust curRow so that it is pointing at the first non-empty row of vec2d
        if (!vec2d.empty()) {
            while ((*curRow).empty() && curRow < lastRow) curRow++;
            curElem = (*curRow).begin();
        }
    }

    int next() {
        int res;
        if (curElem == (*curRow).end()) {
            // find the next non-empty row
            vector<vector<int>>::iterator i = curRow+1;
            while ((*i).empty() && i < lastRow) i++;
            curRow = i;
            // we are safe to dereference curRow since we only call next() if hasNext() returns true
            curElem = (*curRow).begin(); 
        }
        res = *curElem++;
        return res;
    }

    bool hasNext() {
        if (curRow == lastRow) return false;
        if (curElem != (*curRow).end()) return true;
        // test if there is another non-empty row
        vector<vector<int>>::iterator i = curRow+1;
        while ((*i).empty() && i < lastRow) i++;
        return i != lastRow;
    }
    
private:
    vector<int>::iterator curElem; // traversing the current element
    vector<vector<int>>::iterator curRow; // traversing the rows
    vector<vector<int>>::iterator lastRow; // last row
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
 
/*
Remark: Notice in the above implementation, we are finding the next non-empty row in both next() and hasNext(). We can use that logic in hasNext() and directly call hasNext() first in next() to get the curRow in place. We can do this because we are using this class as while (i.hasNext()) cout << i.next(). Therefore it is safe to modify the curRow pointer in hasNext().
*/

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        curRow = vec2d.begin();
        lastRow = vec2d.end();
        
        pos = 0;
    }

    int next() {
        hasNext();
        return (*curRow)[pos++];
    }

    bool hasNext() {
        while (curRow < lastRow && pos == (*curRow).size()) {
            curRow++;
            pos = 0; // reset pos
        }
        return curRow != lastRow;
    }
  
    /* Removes from the underlying collection the last element returned 
     * by this iterator (optional operation). This method can be called 
     * only once per call to next(). The behavior of an iterator is unspecified 
     * if the underlying collection is modified while the iteration is 
     * in progress in any way other than by calling this method.
     * So the remove() method actually removes the element returned from the next(). 
     * Whether remove the inner vector or not depends on the specific situation.
     */
    int remove() {
        int res = (*curRow)[--pos]; // remove() is called after next(), so pos will not be 0
        curRow->erase(curRow->begin() + pos); // now pos automatically points to the next element
        if (curRow->empty()) curRow++;
        return res;
    }
  
private:
    int pos = 0; // traversing the current element
    vector<vector<int>>::iterator curRow; // traversing the rows
    vector<vector<int>>::iterator lastRow; // last row
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
