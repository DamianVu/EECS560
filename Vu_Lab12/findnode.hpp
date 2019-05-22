
#ifndef FN_H
#define FN_H

class FindNode {
public:
	FindNode(int node) { 
		val = node;
		parent = nullptr;
		rank = 0;
	}

	void setParent(FindNode * node) { parent = node; }
	void setVal(int iVal) { val = iVal; }
	void setRank(int r) { rank = r; }

	int getVal() { return val; }
	int getRank() { return rank; }
	FindNode * getParent() { return parent; }

	bool operator != (const FindNode & f) {
		return val != f.val;
	}

private:
	int val;
	int rank;
	FindNode * parent;
};

#endif
