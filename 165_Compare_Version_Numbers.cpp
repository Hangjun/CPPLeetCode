/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0, j = 0;
        int start1, start2;
        while (i < version1.size() && j < version2.size()) {
            start1 = i;
            start2 = j;
            while (i < version1.size() && version1[i] != '.') i++;
            while (j < version2.size() && version2[j] != '.') j++;
            int v1 = stoi(version1.substr(start1, i - start1));
            int v2 = stoi(version2.substr(start2, j - start2));
            if (v1 < v2) {
                return -1;
            } else if (v1 > v2) {
                return 1;
            } else {
                if (i == version1.size() || j == version2.size()) {
                    break;
                }
                i++;
                j++;
            }
        }
        // check if one version is still not fully traversed
        if (i < version1.size()) {
            // version1 is not done: i is at a '.'
            i++;
            while (i < version1.size()) {
                start1 = i;
                while (i < version1.size() && version1[i] != '.') i++;
                if (stoi(version1.substr(start1, i-start1)) != 0) {
                    return 1;
                }
                i++;
            }
        }
        if (j < version2.size()) {
            // version2 is not done: j is at a '.'
            j++;
            while (j < version2.size()) {
                start2 = j;
                while (j < version2.size() && version2[j] != '.') j++;
                if (stoi(version2.substr(start2, j-start2)) != 0) {
                    return -1;
                }
                j++;
            }
        }
        // same version
        return 0;
    }
};
