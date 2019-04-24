
#ifndef NODE_H
#define NODE_H

class TwoThreeNode {
public:

	TwoThreeNode(char lVal, char rVal) { 
		leftVal = lVal; 
		rightVal = rVal;
	}

	~TwoThreeNode() {
		if (left != nullptr)
			delete left;
		if (middle != nullptr)
			delete middle;
		if (right != nullptr)
			delete right;
	}

	void setLeftVal(char val) { leftVal = val; }
	void setRightVal(char val) { rightVal = val; }

	void setParent(TwoThreeNode * p) { parent = p; }
	void setLeft(TwoThreeNode * l) { left = l; }
	void setMiddle(TwoThreeNode * m) { middle = m; }
	void setRight(TwoThreeNode * r) { right = r; }

	char getLeftVal() { return leftVal; }
	char getRightVal() { return rightVal; }

	bool isTwoNode() { return rightVal == 0 && middle == nullptr; }

	bool isTerminalNode() { return left == nullptr && middle == nullptr && right == nullptr; }

	bool isHole() { return leftVal == 0 && rightVal == 0; }

	TwoThreeNode * getParent() { return parent; }
	TwoThreeNode * getLeft() { return left; }
	TwoThreeNode * getMiddle() { return middle; }
	TwoThreeNode * getRight() { return right; }
private:
	char leftVal;
	char rightVal;

	TwoThreeNode * parent = nullptr;
	TwoThreeNode * left = nullptr;
	TwoThreeNode * middle = nullptr;
	TwoThreeNode * right = nullptr;
};

#endif
